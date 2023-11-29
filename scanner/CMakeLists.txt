# Create the scanner library
add_library(scanner_lib STATIC scanner.cpp scanner.hpp)

# Add include directories for the library
target_include_directories(scanner_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(scanner_lib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
