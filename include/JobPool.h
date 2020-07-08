#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <deque>
#include <array>
#include <vector>


// Primative queue that maintains jobs that can be accessed from multiple
// threads
class JobQueue {
 public:
  JobQueue() { }
  ~JobQueue() { }

  // Pop the next item off of the queue, if there are no items left and the
  // queue has been closed (with the done function) then false will be returned
  // otherwise the next function will be put into func and true will be returned
  bool pop(std::function<void()>& func) {
    // Lock the queue
    std::unique_lock<std::mutex> lock{mutex};

    // Hold the thread until either more jobs are queued or the pool is
    // destroyed
    while (queue.empty() && !_done) {
      ready.wait(lock);  // Wait until notified
    }

    // If it is still empty then we are done with this queue
    if (queue.empty()) {
      return false;
    }

    // Grab and remove the next job in the queue
    func = std::move(queue.front());
    queue.pop_front();
    return true;
  }

  // Push a job into the queue
  template<typename T>
  void push(T&& func) {
    {
      // Lock the queue then push an item onto it
      std::unique_lock<std::mutex> lock{mutex};
      queue.emplace_back(std::forward<T>(func));
    } // Unlock the queue

    // Notify one of the threads that the queue is unlocked and has an item
    ready.notify_one();
  }

  // Attempt to pop the next item off of the queue, returning false if the pop failed
  bool tryPop(std::function<void()> &func) {
    // Attempt to lock the queue
    std::unique_lock<std::mutex> lock{mutex, std::try_to_lock};
    if (!lock || queue.empty()) {
      return false;
    }

    // Grab and remove the next job in the queue
    func = std::move(queue.front());
    queue.pop_front();
    return true;

  }

  template<typename T>
  bool tryPush(T&& func) {
    {
      // Attempt to lock the queue
      std::unique_lock<std::mutex> lock{mutex, std::try_to_lock};
      if (!lock) {
        return false;
      }
      queue.emplace_back(std::forward<T>(func));
    } // Unlock the queue
    
    // Notify one of the threads waiting for the queue
    ready.notify_one();
    return true;
  }

  // Mark the queue as closed so that threads can be released when the queue
  // is emptied
  void done() {
    {
      // Lock the queue
      std::unique_lock<std::mutex> lock{mutex};
      _done = true;
    } // Unlock the queue

    // Let everyone know that the queue is closed
    ready.notify_all();
  }

 private:
  // TODO: rename these variables to something more appropiot
  std::deque<std::function<void()>> queue;
  bool _done{false};
  std::mutex mutex;
  std::condition_variable ready;
};


// Simple multi-queued structure that runs threads to complete the tasked jobs
class JobPool {
 public:
  JobPool() {
    // Spin up a number of threads equal to the amount of cores on the computer
    for (unsigned int i = 0; i < threadCount; ++i) {
      // Each thread is assigned to run the run() function
      threads.emplace_back([&, i]{
        run(i);
      });
    }
  }

  // Closes the queues and waits for the threads to finish before destroying
  ~JobPool() {
    // Close queues
    for (auto& queue : jobQueues) {
      queue.done();
    }

    // Wait for threads to finish
    for (auto& thread : threads) {
      thread.join();
    }
  }

  // Pushes a job onto one of the queues in a round-robin approach
  template<typename T>
  void async(T&& func) {
    auto n = index++;

    // Try to steal a job from someone else
    for (unsigned int i = 0; i != threadCount * K; ++i) {
      if (jobQueues[(i + n) % threadCount].tryPush(std::forward<T>(func))) {
        return;
      }
    }

    // Otherwise just wait for a job
    jobQueues[index++ % threadCount].push(std::forward<T>(func));
  }

  // TODO: remove
  bool done() { return finishedThreads == threadCount; }

 private:
  // Thread runner that continues to wait on jobs from queues until they are
  // emptied and the JobPool is destroyed
  void run(unsigned int i) {
    while (true) {
      std::function<void()> func;

      // Quickly try to take any available job from any queue
      for (unsigned int n = 0; n != threadCount; ++n) {
        if (jobQueues[(i + n) % threadCount].tryPop(func)) {
          break;
        }
      }

      // Grabs the next job in any queue. If the queue is empty and no other
      // job can be found it will wait for an item to be added, putting the 
      // current thread to sleep in the meantime. False will be returned when 
      // the queue is empty and the JobPool is being destroyed
      if (!func && !jobQueues[i].pop(func)) {
        break;
      }

      // Run the job
      func();
    }

    ++finishedThreads; // TODO: remove
  }

  // TODO: rename variables to something more descriptive

  // Checks for the number of threads on the system
  const unsigned int threadCount{std::thread::hardware_concurrency()};
  const unsigned int K = 5;
  std::vector<std::thread> threads;
  std::vector<JobQueue> jobQueues{threadCount};
  std::mutex mutex;
  std::atomic<unsigned int> index{0};
  std::atomic<unsigned int> finishedThreads{0}; // TODO: remove
};
