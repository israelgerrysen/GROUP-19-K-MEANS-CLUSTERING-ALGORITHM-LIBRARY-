cmake_minimum_required(VERSION 3.10)

# Name your project and specify C++ as the language
project(KMeansLibrary VERSION 1.0 LANGUAGES CXX)

# Enforce modern C++ standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell the compiler where to look for your .hpp header files
include_directories(include)

# 1. Compile the Core Library
# This bundles your implementation files into a reusable library named "kmeans_lib"
add_library(kmeans_lib 
    src/DataLoader.cpp
    src/DataPreprocessor.cpp
)

# 2. Build the Example Executable
# This compiles your test file into a runnable program
add_executable(example_load examples/example_load.cpp)

# 3. Link the Library to the Executable
# This connects the "kmeans_lib" logic to your "example_load" program
target_link_libraries(example_load PRIVATE kmeans_lib)