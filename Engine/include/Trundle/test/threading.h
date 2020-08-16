//===-- threading.h --------------------------------------------------------===//
//
// Copyright 2020 Zachary Selk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===-----------------------------------------------------------------------===//

#pragma once

// A simple unit test to check and see if the thread pool can create and run
// tasks correctly.

#include <Trundle/common.h>
#include <Trundle/Core/threadPool.h>
#include <Trundle/Math/general.h>


namespace test {

// A test class that keeps track of the work done to verify that threads are finishing
class TestThread {
  public:
    TestThread(int n) : index(n) { }

    // Calculate the fibonacci sequence as proof of work
    void run() {
        result = Trundle::math::fibonacci_linear(index);
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
    ThreadPool jobs;
    for (int i = 0; i < N; ++i) {
        if (i % 1000 == 0) {
            printf("Queuing tests %i-%i...\n", i, i+999);
        }
        tests.emplace_back(TestThread(i));
    }

    for (int i = 0; i < N; ++i) {
        jobs.async(tests[i].getFunc());
    }
    } // Let jobs deallocate and finish running

    for (int i = 0; i < N; ++i) {
        int result = Trundle::math::fibonacci_linear(i);

        if (tests[i].getResult() != result) {
            printf("Error: incorrect result, thread calcualted fib(%i) = %i and not %i\n", i, tests[i].getResult(), result);
            return false;
        }
    }

    printf("Finished with no problems\n");


    for (int i = 0; i < 100; ++i) {
        if (Trundle::math::fibonacci_linear(i) != Trundle::math::fibonacci(i)) {
            int lin = Trundle::math::fibonacci_linear(i);
            int one = Trundle::math::fibonacci(i);
            printf("Filed at %i. %i vs %i\n", i, lin, one);
        }
    }
    printf("Done\n");
    return true;
}

};  /* namespace test */
