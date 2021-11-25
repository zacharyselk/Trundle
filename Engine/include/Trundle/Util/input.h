//===-- input.h -----------------------------------------------------------===//
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
/// Tools used to handle input.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/keyCode.h>
#include <Trundle/Core/log.h>
#include <Trundle/Core/util.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle {

/// @brief Converts Trundles key codes to GLFWs key codes.
inline int TrundleToGL(KeyCode key) {
  switch (key) {
  case KeyCode::None:
    return GLFW_KEY_UNKNOWN;

  case KeyCode::Backspace:
  case KeyCode::Delete:
  case KeyCode::Tab:
  case KeyCode::Clear:
  case KeyCode::Return:
  case KeyCode::Pause:
    assert(0 && "Error: Unhandled keycode.");
    return 0;

  case KeyCode::Escape:
    return GLFW_KEY_ESCAPE;
  case KeyCode::Space:
    return GLFW_KEY_SPACE;

  case KeyCode::Keypad0:
  case KeyCode::Keypad1:
  case KeyCode::Keypad2:
  case KeyCode::Keypad3:
  case KeyCode::Keypad4:
  case KeyCode::Keypad5:
  case KeyCode::Keypad6:
  case KeyCode::Keypad7:
  case KeyCode::Keypad8:
  case KeyCode::Keypad9:
  case KeyCode::KeypadPeriod:
  case KeyCode::KeypadSlash:
  case KeyCode::KeypadAsterisk:
  case KeyCode::KeypadMinus:
  case KeyCode::KeypadPlus:
  case KeyCode::KeypadEnter:
  case KeyCode::KeypadEqual:
    assert(0 && "Error: Unhandled keycode.");
    return 0;

  case KeyCode::Up:
    return GLFW_KEY_UP;
  case KeyCode::Down:
    return GLFW_KEY_DOWN;
  case KeyCode::Left:
    return GLFW_KEY_LEFT;
  case KeyCode::Right:
    return GLFW_KEY_RIGHT;

  case KeyCode::Insert:
  case KeyCode::Home:
  case KeyCode::End:
  case KeyCode::PageUp:
  case KeyCode::PageDown:
  case KeyCode::F1:
  case KeyCode::F2:
  case KeyCode::F3:
  case KeyCode::F4:
  case KeyCode::F5:
  case KeyCode::F6:
  case KeyCode::F7:
  case KeyCode::F8:
  case KeyCode::F9:
  case KeyCode::F10:
  case KeyCode::F11:
  case KeyCode::F12:
  case KeyCode::F13:
  case KeyCode::F14:
  case KeyCode::F15:
    assert(0 && "Error: Unhandled keycode.");
    return 0;

  case KeyCode::Alpha0:
    return GLFW_KEY_0;
  case KeyCode::Alpha1:
    return GLFW_KEY_1;
  case KeyCode::Alpha2:
    return GLFW_KEY_2;
  case KeyCode::Alpha3:
    return GLFW_KEY_3;
  case KeyCode::Alpha4:
    return GLFW_KEY_4;
  case KeyCode::Alpha5:
    return GLFW_KEY_5;
  case KeyCode::Alpha6:
    return GLFW_KEY_6;
  case KeyCode::Alpha7:
    return GLFW_KEY_7;
  case KeyCode::Alpha8:
    return GLFW_KEY_8;
  case KeyCode::Alpha9:
    return GLFW_KEY_9;

  case KeyCode::Exclaim:
  case KeyCode::DoubleQuote:
  case KeyCode::Pound:
  case KeyCode::Dollar:
  case KeyCode::Percent:
  case KeyCode::Ampersand:
  case KeyCode::Quote:
  case KeyCode::LeftParen:
  case KeyCode::RightParen:
  case KeyCode::Asterisk:
  case KeyCode::Plus:
  case KeyCode::Comma:
  case KeyCode::Minus:
  case KeyCode::Period:
  case KeyCode::Slash:
  case KeyCode::Colon:
  case KeyCode::Semicolon:
  case KeyCode::Less:
  case KeyCode::Equal:
  case KeyCode::Greater:
  case KeyCode::Question:
  case KeyCode::At:
  case KeyCode::LeftBracket:
  case KeyCode::Backslash:
  case KeyCode::RightBracket:
  case KeyCode::Caret:
  case KeyCode::Underscore:
  case KeyCode::BackQuote:
    assert(0 && "Error: Unhandled keycode.");
    return 0;

  case KeyCode::A:
    return GLFW_KEY_A;
  case KeyCode::B:
    return GLFW_KEY_B;
  case KeyCode::C:
    return GLFW_KEY_C;
  case KeyCode::D:
    return GLFW_KEY_D;
  case KeyCode::E:
    return GLFW_KEY_E;
  case KeyCode::F:
    return GLFW_KEY_F;
  case KeyCode::G:
    return GLFW_KEY_G;
  case KeyCode::H:
    return GLFW_KEY_H;
  case KeyCode::I:
    return GLFW_KEY_I;
  case KeyCode::J:
    return GLFW_KEY_J;
  case KeyCode::K:
    return GLFW_KEY_K;
  case KeyCode::L:
    return GLFW_KEY_L;
  case KeyCode::M:
    return GLFW_KEY_M;
  case KeyCode::N:
    return GLFW_KEY_N;
  case KeyCode::O:
    return GLFW_KEY_O;
  case KeyCode::P:
    return GLFW_KEY_P;
  case KeyCode::Q:
    return GLFW_KEY_Q;
  case KeyCode::R:
    return GLFW_KEY_R;
  case KeyCode::S:
    return GLFW_KEY_S;
  case KeyCode::T:
    return GLFW_KEY_T;
  case KeyCode::U:
    return GLFW_KEY_U;
  case KeyCode::V:
    return GLFW_KEY_V;
  case KeyCode::W:
    return GLFW_KEY_W;
  case KeyCode::X:
    return GLFW_KEY_X;
  case KeyCode::Y:
    return GLFW_KEY_Y;
  case KeyCode::Z:
    return GLFW_KEY_Z;

  case KeyCode::LeftCurlyBracket:
  case KeyCode::Pipe:
  case KeyCode::RightCurlyBracket:
  case KeyCode::Tilde:
  case KeyCode::Numlock:
  case KeyCode::CapsLock:
  case KeyCode::ScrollLock:
  case KeyCode::RightShift:
  case KeyCode::LeftShift:
  case KeyCode::RightControl:
  case KeyCode::LeftControl:
  case KeyCode::RightAlt:
  case KeyCode::LeftAlt:
  case KeyCode::LeftCommand:
  case KeyCode::LeftApple:
  case KeyCode::LeftWindows:
  case KeyCode::RightCommand:
  case KeyCode::RightApple:
  case KeyCode::RightWindows:
  case KeyCode::AltGr:
  case KeyCode::Help:
  case KeyCode::Print:
  case KeyCode::SysReq:
  case KeyCode::Break:
  case KeyCode::Menu:
  case KeyCode::Mouse0:
  case KeyCode::Mouse1:
  case KeyCode::Mouse2:
  case KeyCode::Mouse3:
  case KeyCode::Mouse4:
  case KeyCode::Mouse5:
  case KeyCode::Mouse6:
  case KeyCode::JoystickButton0:
  case KeyCode::JoystickButton1:
  case KeyCode::JoystickButton2:
  case KeyCode::JoystickButton3:
  case KeyCode::JoystickButton4:
  case KeyCode::JoystickButton5:
  case KeyCode::JoystickButton6:
  case KeyCode::JoystickButton7:
  case KeyCode::JoystickButton8:
  case KeyCode::JoystickButton9:
  case KeyCode::JoystickButton10:
  case KeyCode::JoystickButton11:
  case KeyCode::JoystickButton12:
  case KeyCode::JoystickButton13:
  case KeyCode::JoystickButton14:
  case KeyCode::JoystickButton15:
  case KeyCode::JoystickButton16:
  case KeyCode::JoystickButton17:
  case KeyCode::JoystickButton18:
  case KeyCode::JoystickButton19:
  case KeyCode::Joystick1Button0:
  case KeyCode::Joystick1Button1:
  case KeyCode::Joystick1Button2:
  case KeyCode::Joystick1Button3:
  case KeyCode::Joystick1Button4:
  case KeyCode::Joystick1Button5:
  case KeyCode::Joystick1Button6:
  case KeyCode::Joystick1Button7:
  case KeyCode::Joystick1Button8:
  case KeyCode::Joystick1Button9:
  case KeyCode::Joystick1Button10:
  case KeyCode::Joystick1Button11:
  case KeyCode::Joystick1Button12:
  case KeyCode::Joystick1Button13:
  case KeyCode::Joystick1Button14:
  case KeyCode::Joystick1Button15:
  case KeyCode::Joystick1Button16:
  case KeyCode::Joystick1Button17:
  case KeyCode::Joystick1Button18:
  case KeyCode::Joystick1Button19:
  case KeyCode::Joystick2Button0:
  case KeyCode::Joystick2Button1:
  case KeyCode::Joystick2Button2:
  case KeyCode::Joystick2Button3:
  case KeyCode::Joystick2Button4:
  case KeyCode::Joystick2Button5:
  case KeyCode::Joystick2Button6:
  case KeyCode::Joystick2Button7:
  case KeyCode::Joystick2Button8:
  case KeyCode::Joystick2Button9:
  case KeyCode::Joystick2Button10:
  case KeyCode::Joystick2Button11:
  case KeyCode::Joystick2Button12:
  case KeyCode::Joystick2Button13:
  case KeyCode::Joystick2Button14:
  case KeyCode::Joystick2Button15:
  case KeyCode::Joystick2Button16:
  case KeyCode::Joystick2Button17:
  case KeyCode::Joystick2Button18:
  case KeyCode::Joystick2Button19:
  case KeyCode::Joystick3Button0:
  case KeyCode::Joystick3Button1:
  case KeyCode::Joystick3Button2:
  case KeyCode::Joystick3Button3:
  case KeyCode::Joystick3Button4:
  case KeyCode::Joystick3Button5:
  case KeyCode::Joystick3Button6:
  case KeyCode::Joystick3Button7:
  case KeyCode::Joystick3Button8:
  case KeyCode::Joystick3Button9:
  case KeyCode::Joystick3Button10:
  case KeyCode::Joystick3Button11:
  case KeyCode::Joystick3Button12:
  case KeyCode::Joystick3Button13:
  case KeyCode::Joystick3Button14:
  case KeyCode::Joystick3Button15:
  case KeyCode::Joystick3Button16:
  case KeyCode::Joystick3Button17:
  case KeyCode::Joystick3Button18:
  case KeyCode::Joystick3Button19:
  case KeyCode::Joystick4Button0:
  case KeyCode::Joystick4Button1:
  case KeyCode::Joystick4Button2:
  case KeyCode::Joystick4Button3:
  case KeyCode::Joystick4Button4:
  case KeyCode::Joystick4Button5:
  case KeyCode::Joystick4Button6:
  case KeyCode::Joystick4Button7:
  case KeyCode::Joystick4Button8:
  case KeyCode::Joystick4Button9:
  case KeyCode::Joystick4Button10:
  case KeyCode::Joystick4Button11:
  case KeyCode::Joystick4Button12:
  case KeyCode::Joystick4Button13:
  case KeyCode::Joystick4Button14:
  case KeyCode::Joystick4Button15:
  case KeyCode::Joystick4Button16:
  case KeyCode::Joystick4Button17:
  case KeyCode::Joystick4Button18:
  case KeyCode::Joystick4Button19:
  case KeyCode::Joystick5Button0:
  case KeyCode::Joystick5Button1:
  case KeyCode::Joystick5Button2:
  case KeyCode::Joystick5Button3:
  case KeyCode::Joystick5Button4:
  case KeyCode::Joystick5Button5:
  case KeyCode::Joystick5Button6:
  case KeyCode::Joystick5Button7:
  case KeyCode::Joystick5Button8:
  case KeyCode::Joystick5Button9:
  case KeyCode::Joystick5Button10:
  case KeyCode::Joystick5Button11:
  case KeyCode::Joystick5Button12:
  case KeyCode::Joystick5Button13:
  case KeyCode::Joystick5Button14:
  case KeyCode::Joystick5Button15:
  case KeyCode::Joystick5Button16:
  case KeyCode::Joystick5Button17:
  case KeyCode::Joystick5Button18:
  case KeyCode::Joystick5Button19:
  case KeyCode::Joystick6Button0:
  case KeyCode::Joystick6Button1:
  case KeyCode::Joystick6Button2:
  case KeyCode::Joystick6Button3:
  case KeyCode::Joystick6Button4:
  case KeyCode::Joystick6Button5:
  case KeyCode::Joystick6Button6:
  case KeyCode::Joystick6Button7:
  case KeyCode::Joystick6Button8:
  case KeyCode::Joystick6Button9:
  case KeyCode::Joystick6Button10:
  case KeyCode::Joystick6Button11:
  case KeyCode::Joystick6Button12:
  case KeyCode::Joystick6Button13:
  case KeyCode::Joystick6Button14:
  case KeyCode::Joystick6Button15:
  case KeyCode::Joystick6Button16:
  case KeyCode::Joystick6Button17:
  case KeyCode::Joystick6Button18:
  case KeyCode::Joystick6Button19:
  case KeyCode::Joystick7Button0:
  case KeyCode::Joystick7Button1:
  case KeyCode::Joystick7Button2:
  case KeyCode::Joystick7Button3:
  case KeyCode::Joystick7Button4:
  case KeyCode::Joystick7Button5:
  case KeyCode::Joystick7Button6:
  case KeyCode::Joystick7Button7:
  case KeyCode::Joystick7Button8:
  case KeyCode::Joystick7Button9:
  case KeyCode::Joystick7Button10:
  case KeyCode::Joystick7Button11:
  case KeyCode::Joystick7Button12:
  case KeyCode::Joystick7Button13:
  case KeyCode::Joystick7Button14:
  case KeyCode::Joystick7Button15:
  case KeyCode::Joystick7Button16:
  case KeyCode::Joystick7Button17:
  case KeyCode::Joystick7Button18:
  case KeyCode::Joystick7Button19:
  case KeyCode::Joystick8Button0:
  case KeyCode::Joystick8Button1:
  case KeyCode::Joystick8Button2:
  case KeyCode::Joystick8Button3:
  case KeyCode::Joystick8Button4:
  case KeyCode::Joystick8Button5:
  case KeyCode::Joystick8Button6:
  case KeyCode::Joystick8Button7:
  case KeyCode::Joystick8Button8:
  case KeyCode::Joystick8Button9:
  case KeyCode::Joystick8Button10:
  case KeyCode::Joystick8Button11:
  case KeyCode::Joystick8Button12:
  case KeyCode::Joystick8Button13:
  case KeyCode::Joystick8Button14:
  case KeyCode::Joystick8Button15:
  case KeyCode::Joystick8Button16:
  case KeyCode::Joystick8Button17:
  case KeyCode::Joystick8Button18:
  case KeyCode::Joystick8Button19:
    assert(0 && "Error: Unhandled keycode.");
    return 0;
  }

  assert(0 && "Error: Unknown Key Code.");
  return 0;
}

/// @brief Converts Trundles key codes to GLFWs key codes.
inline KeyCode GLToTrundle(int keycode) {
  switch (keycode) {
  case GLFW_KEY_SPACE:
    return KeyCode::Space;
  case GLFW_KEY_ESCAPE:
    return KeyCode::Escape;
  case GLFW_KEY_0:
    return KeyCode::Alpha0;
  case GLFW_KEY_1:
    return KeyCode::Alpha1;
  case GLFW_KEY_2:
    return KeyCode::Alpha2;
  case GLFW_KEY_3:
    return KeyCode::Alpha3;
  case GLFW_KEY_4:
    return KeyCode::Alpha4;
  case GLFW_KEY_5:
    return KeyCode::Alpha5;
  case GLFW_KEY_6:
    return KeyCode::Alpha6;
  case GLFW_KEY_7:
    return KeyCode::Alpha7;
  case GLFW_KEY_8:
    return KeyCode::Alpha8;
  case GLFW_KEY_9:
    return KeyCode::Alpha9;
  case GLFW_KEY_A:
    return KeyCode::A;
  case GLFW_KEY_B:
    return KeyCode::B;
  case GLFW_KEY_C:
    return KeyCode::C;
  case GLFW_KEY_D:
    return KeyCode::D;
  case GLFW_KEY_E:
    return KeyCode::E;
  case GLFW_KEY_F:
    return KeyCode::F;
  case GLFW_KEY_G:
    return KeyCode::G;
  case GLFW_KEY_H:
    return KeyCode::H;
  case GLFW_KEY_I:
    return KeyCode::I;
  case GLFW_KEY_J:
    return KeyCode::J;
  case GLFW_KEY_K:
    return KeyCode::K;
  case GLFW_KEY_L:
    return KeyCode::L;
  case GLFW_KEY_M:
    return KeyCode::M;
  case GLFW_KEY_N:
    return KeyCode::N;
  case GLFW_KEY_O:
    return KeyCode::O;
  case GLFW_KEY_P:
    return KeyCode::P;
  case GLFW_KEY_Q:
    return KeyCode::Q;
  case GLFW_KEY_R:
    return KeyCode::R;
  case GLFW_KEY_S:
    return KeyCode::S;
  case GLFW_KEY_T:
    return KeyCode::T;
  case GLFW_KEY_U:
    return KeyCode::U;
  case GLFW_KEY_V:
    return KeyCode::V;
  case GLFW_KEY_W:
    return KeyCode::W;
  case GLFW_KEY_X:
    return KeyCode::X;
  case GLFW_KEY_Y:
    return KeyCode::Y;
  case GLFW_KEY_Z:
    return KeyCode::Z;
  case GLFW_KEY_UP:
    return KeyCode::Up;
  case GLFW_KEY_DOWN:
    return KeyCode::Down;
  case GLFW_KEY_LEFT:
    return KeyCode::Left;
  case GLFW_KEY_RIGHT:
    return KeyCode::Right;
  default:
    Log::Critical("Unhandled key id: " + std::to_string(keycode));
    assert(0 && "Error: Unhandled GLFW case");
  }

  return KeyCode::None;
}

} // namespace Trundle