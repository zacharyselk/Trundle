FROM ubuntu:18.04

RUN apt update
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt update
RUN apt upgrade -y
RUN apt install -y libxrandr-dev
RUN apt update
RUN apt upgrade 
RUN apt install -y libxinerama-dev 
RUN apt install -y libxcursor-dev 
RUN apt install -y libxi-dev
RUN apt install -y wget
RUN apt install -y git
RUN apt install -y make
RUN apt install -y libgl1-mesa-dev
RUN apt install -y freeglut3-dev
RUN apt install -y gcc-9 g++-9

#VOLUME /root/trundle
ADD . /root/trundle
WORKDIR /root/trundle

RUN mkdir -p /root/cmake
RUN mkdir -p /root/clang
RUN wget -qO- https://github.com/Kitware/CMake/releases/download/v3.18.1/cmake-3.18.1-Linux-x86_64.tar.gz | tar xpoz -C /root/cmake --strip-components 1
RUN wget -qO- https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz | tar xpoJ -C /root/clang --strip-components 1
ENV PATH="/root/cmake/bin:/root/clang/bin:/root/clang/include:/root/clang/lib:${PATH}"
#RUN git clone https://github.com/zacharyselk/Trundle.git
#RUN cd Trundle
RUN mkdir -p /root/trundle-build
RUN cd /root/trundle-build
RUN /root/cmake/bin/cmake /root/trundle/Engine -DTEST_HEADLESS=On 
#-DCMAKE_C_COMPILER=/clang/bin/clang -DCMAKE_CXX_COMPILER=/root/clang/bin/clang++
RUN /root/cmake/bin/cmake --build .
RUN ctest -CDebug