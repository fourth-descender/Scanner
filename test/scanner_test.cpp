#include "gtest/gtest.h"
#include "scanner.hpp"
#include <fstream>
#include <sstream>

#define NUM_TEST_CASES 5

TEST(scanner_test, tokenization) {
    // Iterate over test cases in the test_cases folder
    for (int i = 1; i <= NUM_TEST_CASES; ++i) {
        std::string input_file_path = "test_cases/test" + std::to_string(i) + ".c1";
        std::string expected_output_file_path = "test_cases/output" + std::to_string(i) + ".txt";

        // Create a scanner with the input file
        scanner my_scanner(input_file_path, "dummy_output.txt");
        my_scanner.scan();

        // Get actual tokens from the scanner
        const std::vector<token>& actual_tokens = my_scanner.get_tokens();

        // Read expected output file
        std::ifstream expected_output_file(expected_output_file_path);
        ASSERT_TRUE(expected_output_file.is_open()) << "Failed to open expected output file: " << expected_output_file_path;

        // Convert expected output text to tokens
        std::vector<token> expected_tokens;
        std::string token_type, token_value;
        while (expected_output_file >> token_type >> token_value) {
            expected_tokens.emplace_back(token_type, token_value);
        }

        // Assert the actual tokens match the expected tokens
        ASSERT_EQ(actual_tokens, expected_tokens) << "Test Case " << i << " failed.";
    }
}
