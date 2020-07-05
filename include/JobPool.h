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
      std::unique_lock<std::mutex>{mutex};
      queue.emplace_back(std::forward<T>(func));
    } // Unlock the queue

    // Notify one of the threads that the queue is unlocked and has an item
    ready.notify_one();
  }

  // Mark the queue as closed so that threads can be released when the queue
  // is emptied
  void done() {
    {
      // Lock the queue
      std::unique_lock lock{mutex};
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

      // Grabs the next job in the queue. If the queue is empty it will wait
      // for an item to be add, putting the current thread to sleep in the
      // meantime. False will be returned when the queue is empty and the
      // JobPool is being destroyed
      if (!jobQueues[i].pop(func)) {
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
  std::vector<std::thread> threads;
  std::vector<JobQueue> jobQueues{threadCount};
  std::mutex mutex;
  std::atomic<unsigned int> index{0};
  std::atomic<unsigned int> finishedThreads{0}; // TODO: remove
};
