#pragma once

#include <JobPool.h>


namespace test {

// A test class that keeps track of the work done to verify that threads are finishing
class TestThread {
  public:
    TestThread(int n) : index(n) { }

    // Calculate the fibonacci sequence as proof of work
    void run() {
        int a = 0;
        int b = 1;

        for (int i = 0; i < index; ++i) {
            result = a + b;
            b = a;
            a = result;
        }
    }

    int getResult() { return result; }
    
    std::function<void(void)> getFunc() {
        return std::bind(&TestThread::run, this);
    }

  private:
    int index;
    int result{0};
};

// Run a test to verify that the thread pool is working properly
bool verifyThreads() {
    printf("Running thread verification\n");
    static const int N = 10000;
    std::vector<TestThread> tests;
    std::array<std::function<void(void)>, N> functions;

    {
    JobPool jobs;
    for (int i = 0; i < N; ++i) {
        if (i % 1000 == 0) {
            printf("Queuing tests %i-%i...\n", i, i+999);
        }
        tests.emplace_back(TestThread(i));
        jobs.async(tests[i].getFunc());
    }
    } // Let jobs deallocate and finish running

    int a = 0;
    int b = 1;
    int result = 0;
    for (int i = 0; i < N; ++i) {
        if (tests[i].getResult() != result) {
            printf("Error: incorrect result, thread calcualted fib(%i) = %i and not %i\n", i, tests[i].getResult(), result);
            return false;
        }

        result = a + b;
        b = a;
        a = result;
    }

    printf("Finished with no problems\n");
    return true;
}

};  /* namespace test */