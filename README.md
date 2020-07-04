# Trundle
This is a simple 2D game engine built with c++17 and SDL2, created to learn about different aspects of games engines, because what better way to learn than by doing.

## Dependancies
This project has, and will only ever have, four dependancies:
* A c++17 capable compiler (g++, clang++, MSVC, etc)
* CMake
* SDL2
* SDL2_Image

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
