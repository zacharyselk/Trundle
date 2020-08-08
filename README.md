[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c1f4810974d4455680dd2a861df375d0)](https://app.codacy.com/manual/zacharyselk/Trundle?utm_source=github.com&utm_medium=referral&utm_content=zacharyselk/Trundle&utm_campaign=Badge_Grade_Dashboard)

# Trundle
This is a simple game engine built with c++17, created to learn about different aspects of games engines, because what better way to learn than by doing.

## Dependancies
This project attempts to keep the dependancies down to a minimum and creating submodules whenever possible to automate dependancy building. Currently the only dependancies are:
* CMake 3.18 or higher
* A c++17 supported compiler (gcc >= 8.0, clang >= 5.0)
* OpenGL

### Installing Dependancies
Go to [cmake](https://cmake.org/download/) to download and install the latest version of CMake.

For the rest of the dependancies.

On Ubuntu:
```sh
# apt-get install -y libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
```

## Building
This project uses CMake as its build software, so simply need to run the following commands to build the project.
Firstly clone the repository
```sh
$ git clone --recursive https://github.com/zacharyselk/Trundle.git
```
Then use CMake to compile the project
```sh
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```
This will build the sample `Driver` in `build/bin/` by default. To change the build location use `$ cmake .. --DCMAKE_INSTALL_PREFIX=<path>`

## Running
Once built an exacutable named `bin/driver` (or `bin\driver.exe`) will be created and simply needs to be executed to run.

## Builds
| Service                                                   | System                | Compiler             | Status                                                                                                                                                                    |
| --------------------------------------------------------- | --------------------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Travis CI](https://travis-ci.org/g-truc/glm)             | MacOSX, Linux 64 bits | Clang                | [![Build Status](https://travis-ci.com/zacharyselk/Trundle.svg?branch=master)](https://travis-ci.com/zacharyselk/Trundle)                                                 |
| [AppVeyor](https://ci.appveyor.com/project/Groovounet/glm)| Windows 32 and 64     | Visual Studio 2019   | [![Build status](https://ci.appveyor.com/api/projects/status/tfs7wtb5ugy58bn5/branch/master?svg=true)](https://ci.appveyor.com/project/zacharyselk/trundle/branch/master) |

## Progress
### Done (draft version)
* Thread pool
* Events
* Layer stack
* UI system (using ImGui)

### Working on
* Event handling

### TODO
#### Easy
* Add Windows and MacOs to Travis
* Add lit tests (using googletest)
* Add elements to the UI
* Add functionallity to the logger (formatting, coloring, etc.)
* Make CMake build `/Engine` normally and use ExternalProject_Add on `/Driver`

#### Medium
* Add profiling system
* Add a reflection system

#### Hard
* Add a Rendering system (Big job)
* Add a different graphics api (DirectX, Metal, Vulkan, etc)
