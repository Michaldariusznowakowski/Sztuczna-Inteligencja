*This repository is used to store the code for the course "Sztuczna Inteligencja.*
If you want to build the project, you need to use windows.
The project is built using Msys2 and MinGW-w64.
To build the project, you need to install Msys2 and MinGW-w64.
You also need to have installed Git for installing vcpkg.
To install Msys2, go to https://www.msys2.org/ and follow the instructions.
If you want to install MinGW-w64, you need to open Msys2 and type:
```
pacman -S mingw-w64-x86_64-gnuplot
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-make
pacman -S mingw-w64-x86_64-ninja
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-gdb
pacman -S mingw-w64-x86_64-boost
```
*Note: remember to add MinGW-w64 to your PATH variable.*
To install vcpkg, you need to run ./setupLibs.bat script.

How to build the project:
```
mkdir build
cd build
cmake ..
make NAME_OF_TARGET
```
