ECHO OFF

@REM SETTINGS START
SET hostTriplet=x64-mingw-static
SET triplet=x64-mingw-static
@REM LIBRARIES LIST
SET LIBRARIES=matplotplusplus matio spdlog nana

@REM SETTINGS END
ECHO *************************************************************
ECHO You need to have git installed and in your PATH!
ECHO *************************************************************
ECHO This script is only for MSYS2!
ECHO *************************************************************
ECHO Before running this script you need to install the following
ECHO  packages in Msys2:
ECHO *************************************************************
ECHO $ pacman -S mingw-w64-x86_64-gnuplot
ECHO $ pacman -S mingw-w64-x86_64-cmake
ECHO $ pacman -S mingw-w64-x86_64-make
ECHO $ pacman -S mingw-w64-x86_64-ninja
ECHO $ pacman -S mingw-w64-x86_64-toolchain
ECHO $ pacman -S mingw-w64-x86_64-gcc
ECHO $ pacman -S mingw-w64-x86_64-gdb
ECHO $ pacman -S mingw-w64-x86_64-boost
ECHO *************************************************************
ECHO Remember to add Msys2 to your PATH!
ECHO *************************************************************
ECHO LIBRARIES LIST: %LIBRARIES% 
ECHO *************************************************************
ECHO Are you ready to continue? This will take a long time. (y/n)
ECHO *************************************************************
SET /P ready=
IF %ready%==n (
    ECHO Exiting...
    EXIT
)
IF %ready% NEQ y (
    ECHO Invalid input!
    ECHO Exiting...
    EXIT
)
ECHO Cloning vcpkg...
git clone https://github.com/Microsoft/vcpkg.git 
ECHO Building vcpkg...
cd vcpkg
@REM  Run in new shell and wait for it to finish
@REM .\bootstrap-vcpkg.bat
cmd /c .\bootstrap-vcpkg.bat
ECHO Installing packages...
.\vcpkg.exe install %LIBRARIES% --triplet %hostTriplet% --host-triplet %triplet%






