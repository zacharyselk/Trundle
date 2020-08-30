//===-- imGuiLayer.cpp ----------------------------------------------------===//
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
//===----------------------------------------------------------------------===//

#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Util/imGuiLayer.h>
#include <imgui.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h> // Important: Include glfw3.h after OpenGL definitions.

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Trundle {

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
  backgroundColor = new ImVec4(1.0, 1.0, 0.0, 1.0);
}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::onAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  // TODO: Figure out a better way to select the glsl version.
#if defined(TRUNDLE_OS_MACOS)
  const char* glsl_version = "#version 150";
#else
  const char* glsl_version = "#version 130";
#endif

  Application* app = Application::get();
  // Hack: Assumes that the window is a GLFW window.
  GLFWwindow* window =
      static_cast<GLFWwindow*>(app->getWindow().getNativeWindow());

  // Setup Platform/Renderer bindings.
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  initalized = true;
}

void ImGuiLayer::onDetach() {}

void ImGuiLayer::onUpdate() {
  Log::Trace("Running onUpdate from imGuiLayer");
  if (!initalized) {
    Log::Warn("Trying to run onUpade on unintalized ImGuiLayer");
    return;
  }
  // Start (or create?) a new ImGui frame.
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // // Show the demo window.
  static bool showDemoWindow = true;
  // //ImVec4 backgroundColor = ImVec4(0.54, 0.17, 0.89, 1.00);

  if (showDemoWindow) {
    ImGui::ShowDemoWindow(&showDemoWindow);
  }
  // static float f = 0.0f;
  // static int counter = 0;

  // // Create a window called "Hello, world!" and append into it.
  // ImGui::Begin("Hello, world!");

  // // Display some text (you can use a format strings too)
  // ImGui::Text("This is some useful text.");
  // // Edit bools storing our window open/close state
  // ImGui::Checkbox("Demo Window", &showDemoWindow);

  // // Edit 1 float using a slider from 0.0f to 1.0f
  // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
  // // Edit 3 floats representing a color
  // ImGui::ColorEdit3("clear color", (float*)backgroundColor);

  // // Buttons return true when clicked (most widgets return true when
  // edited/activated) if (ImGui::Button("Button"))
  //   counter++;
  // ImGui::SameLine();
  // ImGui::Text("counter = %d", counter);

  // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
  // ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  // ImGui::End();
}

void ImGuiLayer::onEvent(Event& event) {}

void ImGuiLayer::begin() {
  Log::Trace("Running begin from imGuiLayer");
  if (!initalized) {
    Log::Warn("Trying to run begin on unintalized ImGuiLayer");
    return;
  }

  ImGuiIO& io = ImGui::GetIO();
  Application* app = Application::get();
  int width = app->getWindow().getWidth();
  int height = app->getWindow().getHeight();
  io.DisplaySize =
      ImVec2(app->getWindow().getWidth(), app->getWindow().getHeight());

  float deltaTime = (float)glfwGetTime();
  io.DeltaTime = time > 0.f ? (deltaTime - time) : (1.f / 60.f);
  time = deltaTime;
}

void ImGuiLayer::end() {
  Log::Trace("Running end from imGuiLayer");
  if (!initalized) {
    Log::Warn("Trying to run end on unintalized ImGuiLayer");
    return;
  }

  Application* app = Application::get();
  int width = app->getWindow().getWidth();
  int height = app->getWindow().getHeight();
  GLFWwindow* nativeWindow =
      static_cast<GLFWwindow*>(app->getWindow().getNativeWindow());

  ImGui::Render();
  glfwGetFramebufferSize(nativeWindow, &width, &height);
  glViewport(0, 0, width, height);
  // glClearColor(backgroundColor->x, backgroundColor->y, backgroundColor->z,
  // backgroundColor->w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // glfwSwapBuffers(nativeWindow);
}

} // namespace Trundle
