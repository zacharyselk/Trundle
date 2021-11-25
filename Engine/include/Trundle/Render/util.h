//===-- util.h ------------------------------------------------------------===//
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
//
// Rendering API helper functions.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>
#include <Trundle/common.h>

namespace Trundle::Rendering {

//===-- ShaderDataType ----------------------------------------------------===//
/// @brief Tags for each of the basic types used by GLSL.
//===----------------------------------------------------------------------===//
enum class ShaderDataType {
		None = 0, 
    Float, 
    Float2, 
    Float3, 
    Float4, 
    Mat3, 
    Mat4, 
    Int, 
    Int2, 
    Int3, 
    Int4, 
    Bool
	};

//===----------------------------------------------------------------------===//
/// @brief Check for the size of the given @ref ShaderDataType.
///
/// A utillity function to determine how large a given data type is, similar to
/// the sizeof macro in c++.
/// @param type The shader data type to check.
/// @return The size in bytes of @p type
//===----------------------------------------------------------------------===//
static uint32_t getSizeOf(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

    Log::Error("Unknown SaderDataType found");
		return 0;
	}


// TODO: Remove
enum GraphicsType { None = 0, Float, Float2, Float3, Float4 };

// Retruns the size of a GraphicsType similar to sizeof().
static uint32_t getSizeOf(const GraphicsType& type) {
  switch (type) {
  case Float:
    return 4;
  case Float2:
    return 4 * 2;
  case Float3:
    return 4 * 3;
  case Float4:
    return 4 * 4;
  }

  Log::Error("Unknown GraphicsType");
  exit(1);
  return -1;
}

// Returns the comonent size of a GraphicsType.
static uint32_t getComponentSizeOf(const GraphicsType& type) {
  switch (type) {
  case Float:
  case Float2:
  case Float3:
  case Float4:
    return 4;
  }

  Log::Error("Unknown GraphicsType");
  exit(1);
  return -1;
}

} // namespace Trundle::Rendering