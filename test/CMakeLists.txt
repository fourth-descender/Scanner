set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Google Test
find_package(GTest REQUIRED)

# Add include directories for Google Test
include_directories(${GTEST_INCLUDE_DIRS})

# Create the test executable
add_executable(scanner_test scanner_test.cpp)

# Link with Google Test and the scanner library
target_link_libraries(scanner_test PRIVATE ${GTEST_MAIN_LIBRARIES} scanner_lib)

# Optionally, you can specify the output directory for the test executable
set_target_properties(scanner_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
