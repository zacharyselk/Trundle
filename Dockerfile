FROM ubuntu:18.04

RUN apt update
RUN apt upgrade -y
RUN apt install -y libxrandr-dev 
RUN apt install -y libxinerama-dev 
RUN apt install -y libxcursor-dev 
RUN apt install -y libxi-dev
RUN apt install -y wget
RUN apt install -y clang
RUN apt install -y git
RUN apt install -y make
RUN apt install -y libgl1-mesa-dev
RUN apt install -y freeglut3-dev

VOLUME /root/trundle
WORKDIR /root/trundle

RUN mkdir -p /root/cmake
RUN wget -qO- https://github.com/Kitware/CMake/releases/download/v3.18.1/cmake-3.18.1-Linux-x86_64.tar.gz | tar xpoz -C /root/cmake --strip-components 1
RUN mkdir -p linux-build
#RUN cd linux-build
#RUN /root/cmake/bin/cmake ../Engine -DTEST_HEADLESS=On
#RUN /root/cmake/bin/cmake --build .
#RUN ctest -CDebug