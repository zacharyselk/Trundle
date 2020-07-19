# Trundle
This is a simple 2D game engine built with c++17 and SDL2, created to learn about different aspects of games engines, because what better way to learn than by doing.

## Dependancies
This project is going to be created around a series of submodules that will be created as the core components of the engine. Each of these components will be designed under a modular approach so that they may be used seperately from the engine but will also be designed around the engine.
There will however be some third party dependancies that will be used, and those are:
* CMake
* The c++17 or higher STL (generally from g++, clang++, MSVC, etc)
* One of Vulkan, DirectX12, and Metal
* One of OpenCL and Cuda
* TODO: Find something that can handle networking and something that can handle audio

## Building
This project uses CMake as its build software, so ideally you would simply need to run the following commands to build the project
```
$ mkdir build && cd build
$ cmake ..
$ make
```
However if that does not work then it is probably the fault of SDL2 not being found. Adding the SDL2 libraries and headers files to the system path _should_ resolve that issue.

## Running
Once built an exacutable named Trundle (or Trundle.exe) will be created and simply needs to be executed to run.

## Progress
### Done
* Nothing

### Working on
* Reflection system
* Thread pool

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
* and much more...
