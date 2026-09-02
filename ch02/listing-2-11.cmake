# Listing 2-11. Its CMakeLists.txt

   cmake_minimum_required(VERSION 3.13.4)
   project(ext_project)

   # Locate LLVM package
   find_package(LLVM REQUIRED CONFIG)

   message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
   message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

   # Set LLVM include and library paths
   include_directories(${LLVM_INCLUDE_DIRS})
   link_directories(${LLVM_LIBRARY_DIRS})

   # Add LLVM definitions
   add_definitions(${LLVM_DEFINITIONS})

   # Add the source files
   add_executable(myproject main.cpp)

   # Link against LLVM libraries
   target_link_libraries(myproject ${LLVM_LIBRARIES})

   # If you are using specific LLVM components, link them explicitly
   llvm_map_components_to_libnames(llvm_libs support core irreader)
   target_link_libraries(myproject ${llvm_libs})
