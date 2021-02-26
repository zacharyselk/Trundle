//===-- application.cpp ---------------------------------------------------===//
//
// Copyright 2021 Zachary Selk
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
//===----------------------------------------------------------------------===//
//
// A simple example of a user-end driver, used to test the code.
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

class TestApplication : public Trundle::Application {
public:
  TestApplication()
   : Trundle::Application(HEADLESS) 
  { 
      printf("Engine Start\n"); 
  }

  ~TestApplication() { printf("Engine Closing\n"); }

  void SetUp() { }
  void TearDown() { }
};

Trundle::Application* Trundle::CreateApplication(int *argc, char** argv, 
                                                 char** envp) {
  return new TestApplication();
}

TEST(Application, initialization) {
  Trundle::Application* app = new TestApplication();
  ASSERT_TRUE(app->get() != nullptr);
}