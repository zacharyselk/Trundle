#pragma once

#include <thread>
#include <functional>
#include <deque>
#include <array>


// Primative queue that maintains jobs that can be accessed from multiple
// threads
class JobQueue {
 public:
  JobQueue() { }
  ~JobQueue() { }

  bool pop(std::function<void()>& func) {
    mutex.lock();
    if (queue.empty()) {
      return false;
    }
    func = std::move(queue.front());
    mutex.unlock();
    return true;
  }

  template<typename T>
  void push(T&& func) {
    mutex.lock();
    queue.emplace_back(std::forward<T>(func));
    mutex.unlock();
  }

  void done() {
    std::unique_lock<std::mutex> lock{mutex};
    _done = true;
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
  JobPool() { }
  ~JobPool() {
    for (auto& thread : threads) {
      thread.join();
    }
    for (auto& queue : jobQueues) {
      queue.done();
    }
  }

  template<typename T>
  void async(T&& func) {
    jobQueues[index++ % threadCount].push(std::forward<T>(func));
  }

 private:
  void run(unsigned int i) {
    while (true) {
      std::function<void()> func;
      if (!jobQueues[i].pop(func)) {
        break;
      }
      func();
    }
  }

  static constexpr unsigned int threadCount{4};
  std::array<std::thread, threadCount> threads;
  std::array<JobQueue, threadCount> jobQueues;
  std::mutex mutex;
  std::atomic<unsigned int> index{0};
};
