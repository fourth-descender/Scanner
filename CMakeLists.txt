cmake_minimum_required(VERSION 3.15)

project(CompilerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include scanner subdirectory
add_subdirectory(scanner)

# Include test subdirectory
add_subdirectory(test)

# Create the main executable and link with the scanner library
add_executable(compiler main.cpp)
target_link_libraries(compiler PRIVATE scanner_lib)

set_target_properties(compiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
