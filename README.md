[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/zacharyselk/Trundle.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/zacharyselk/Trundle/context:cpp)

# Trundle
This is a simple game engine built with c++17, created to learn about different aspects of games engines, because what better way to learn than by doing.

## Dependancies
This project attempts to keep the dependancies down to a minimum and creating submodules whenever possible to automate dependancy building. Currently the only dependancies are:
* CMake 3.17 or higher
* A c++17 supported compiler (gcc >= 8.0, clang >= 5.0)
* OpenGL
* Python 2.7 or higher

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
$ cmake ../Engine
$ cmake --build .
```
This will build the sample `Driver` in `build/bin/` by default. To change the build location use `$ cmake .. --DCMAKE_INSTALL_PREFIX=<path>`

## Running
Once built an exacutable named `bin/driver` (or `bin\driver.exe`) will be created and simply needs to be executed to run.

## Builds
| Service                                                   | System                | Compiler             | Status                                                                                                                                                                    |
| --------------------------------------------------------- | --------------------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Travis CI](https://travis-ci.org/g-truc/glm)             | MacOSX, Linux 64 bits | Clang                | [![Build Status](https://travis-ci.com/zacharyselk/Trundle.svg?branch=master)](https://travis-ci.com/zacharyselk/Trundle)                                                 |
| [AppVeyor](https://ci.appveyor.com/project/Groovounet/glm)| Windows 32 and 64     | Visual Studio 2019   | [![Build status](https://ci.appveyor.com/api/projects/status/tfs7wtb5ugy58bn5/branch/master?svg=true)](https://ci.appveyor.com/project/zacharyselk/trundle/branch/master)
