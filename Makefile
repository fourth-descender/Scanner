CMAKE := cmake
CMAKE_BUILD_DIR := build
TEST_EXECUTABLE := test/bin/scanner_test

all: cmake
	@$(CMAKE) --build $(CMAKE_BUILD_DIR)

cmake:
	@mkdir -p $(CMAKE_BUILD_DIR)
	@cd $(CMAKE_BUILD_DIR) && $(CMAKE) ..

test:
	@[ -x $(TEST_EXECUTABLE) ] && ./$(TEST_EXECUTABLE) || echo "test executable not found."

clean:
	@rm -rf $(CMAKE_BUILD_DIR) lib bin test/bin

.PHONY: all cmake test clean
