#!/bin/bash

mkdir -p build >/dev/null 2>&1
cd build

rm kernel.elf

export CC=/opt/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
export CXX=/opt/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-g++

cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE="../misc/cmake/toolchain-arm-none-eabi-rpi0.cmake" ..

cmake --build . --parallel

mv kernel kernel.elf

cp -r "/mnt/c/users/rosaj/source/repos/ZeroMate/build/ninja/clang/release/src" src/src

#make
#make VERBOSE=1
