cmake_minimum_required(VERSION 3.25.0)
project(project)

# check if vcpkg is installed
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(FATAL_ERROR "vcpkg is not installed")
endif()
    
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(VCPKG_TARGET_TRIPLET x64-mingw-static)
set(VCPKG_HOST_TRIPLET x64-mingw-static)
set(CMAKE_FIND_DEBUG_MODE 1)
# include(./vcpkg/scripts/buildsystems/vcpkg.cmake)
#  add installation prefix path CMAKE_PREFIX_PATH of spdlog 
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-mingw-static/share")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
# use ninja
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lab1)
add_subdirectory(lab2)

#set(CMAKE_MODULE_PATH ./cmake-tools/CMakeChecksCache/cmake-checks-cache)