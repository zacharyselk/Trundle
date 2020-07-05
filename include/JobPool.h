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

  bool pop(std::function<void()>& func) {
    std::unique_lock<std::mutex> lock{mutex};
    while (queue.empty() && !_done) {
      ready.wait(lock);
    }
    if (queue.empty()) {
      return false;
    }
    func = std::move(queue.front());
    queue.pop_front();
    return true;
  }

  template<typename T>
  void push(T&& func) {
    {
      std::unique_lock<std::mutex>{mutex};
      queue.emplace_back(std::forward<T>(func));
    }
    ready.notify_one();
  }

  void done() {
    {
      std::unique_lock lock{mutex};
      _done = true;
    } // Unlock mutex

    ready.notify_all();
  }

 private:
  std::deque<std::function<void()>> queue;
  bool _done{false};
  std::mutex mutex;
  std::condition_variable ready;
};


// Simple multi-queued structure that runs threads to complete the tasked jobs
class JobPool {
 public:
  JobPool() {
    for (unsigned int i = 0; i < threadCount; ++i) {
      threads.emplace_back([&, i]{
        run(i);
      });
    }
  }

  ~JobPool() {
    for (auto& queue : jobQueues) {
      queue.done();
    }

    for (auto& thread : threads) {
      thread.join();
    }
  }

  template<typename T>
  void async(T&& func) {
    jobQueues[index++ % threadCount].push(std::forward<T>(func));
  }

  bool done() { return finishedThreads == threadCount; }

 private:
  void run(unsigned int i) {
    while (true) {
      std::function<void()> func;
      if (!jobQueues[i].pop(func)) {
        break;
      }
      func();
    }

    ++finishedThreads;
  }

  const unsigned int threadCount{std::thread::hardware_concurrency()};
  std::vector<std::thread> threads;
  std::vector<JobQueue> jobQueues{threadCount};
  std::mutex mutex;
  std::atomic<unsigned int> index{0};
  std::atomic<unsigned int> finishedThreads{0};
};
