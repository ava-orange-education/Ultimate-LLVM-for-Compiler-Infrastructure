cmake_minimum_required(VERSION 3.10)

project(LoopSideEffect)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Clang REQUIRED CONFIG)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
# Include directories specified by LLVM in the project's include path
include_directories(${LLVM_INCLUDE_DIRS} LoopSideEffectAnalysis)
# Include definitions specified by LLVM in the project's options
add_definitions(${LLVM_DEFINITIONS})
link_directories(${LLVM_LIBRARY_DIR})

# Adds a target named Hello to the project. It is created as a shared library from the source file HelloWorld.cpp
add_library(LoopSideEffect SHARED LoopSideEffectAnalysis/LoopSideEffectAnalysis.cpp LoopSideEffectMarkerPass/LoopSideEffectMarkerPass.cpp)

# Link against LLVM libraries
target_link_libraries(LoopSideEffect ${llvm_libs})