# Listing 4-1. The CMakeLists.txt that builds the tool

cmake_minimum_required(VERSION 3.10)
project(CustomClangTool)
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
set(CMAKE_CXX_STANDARD 17)
# Enable the generation of the compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(inc)
add_definitions(${LLVM_DEFINITIONS})
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes target targetparser option)
target_link_libraries(${PROJECT_NAME} ${LLVM_LIBS} clangAST clangASTMatchers clangBasic clangFrontend clangFrontendTool clangLex clangParse clangSema clangSerialization clangTooling clangToolingCore)
