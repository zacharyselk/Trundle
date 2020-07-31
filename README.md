# Trundle
This is a simple 2D game engine built with c++17, created to learn about different aspects of games engines, because what better way to learn than by doing.

## Dependancies
This project is going to be created around a series of submodules that will be created as the core components of the engine. Each of these components will be designed under a modular approach so that they may be used seperately from the engine but will also be designed around the engine.
There will however be some third party dependancies that will be used, and those are:
* CMake 3.18 or higher
* The c++17 STL (gcc >= 8.0, clang >= 5.0)
* OpenGL
<!--* One of Vulkan, DirectX12, and Metal
* One of OpenCL and Cuda
* TODO: Find something that can handle networking and something that can handle audio-->

## Building
This project uses CMake as its build software, so simply need to run the following commands to build the project
```
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

Note: On Windows some generators do not work properly, the one that is tested and currently supported is MinGW Makefiles. To use this generator generate the cmake files with `$ cmake .. -G "MinGW Makefiles"`

## Running
Once built an exacutable named bin/driver (or bin\driver.exe) will be created and simply needs to be executed to run.

## Status
| Platform | Build |
| --- | --- |
| Windows | TODO |
| MacOS | TODO |
| Linux | [![Build Status](https://cloud.drone.io/api/badges/zacharyselk/Trundle/status.svg)](https://cloud.drone.io/zacharyselk/Trundle) |

## Progress
### Done
* Thread pool
* Events

### Working on
* Event handling

### Backlog
* Serializer/Deserializer
* Physics libraries
* Math libraries
* Sprite handlers
* Audio engine
* Coliders
* Character objects
* Animation objects
* UI/UX
* Reflection system
* and much more...
