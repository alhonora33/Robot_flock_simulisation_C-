# Variables
BUILD_DIR = build
TARGET = CMR_Optimisation_App_c++
TESTS_TARGET = Tests

# Default target
all: configure build

# Configure the project with CMake
configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# Build the project
build:
	cd $(BUILD_DIR) && cmake --build . --target $(TARGET) -- -j 6
	cp -r src/assets $(BUILD_DIR)/src


# Build the tests
build-test:
	cd $(BUILD_DIR) && cmake --build . --target $(TESTS_TARGET) -- -j 6

# Run the target
run: build
	cd $(BUILD_DIR)/src &&  ./$(TARGET)

# Run with valgrind
valgrind: build
	cd $(BUILD_DIR)/src && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Run the tests
test: build-test
	cd $(BUILD_DIR) && ctest -T test --output-on-failure -j 6 -V 

# Run the tests with valgrind
test-with-valgrind: build-test
	cd $(BUILD_DIR) && ctest -T memcheck -j 6

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR) install

# Reconfigure and build the project
rebuild: clean configure build


# Help target to display available options
help:
	@echo "Usage: make [TARGET] [OPTIONS]"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Configure and build the project"
	@echo "  configure  - Configure the project with CMake"
	@echo "  build      - Build the project"
	@echo "  run        - Run the application"
	@echo "  valgrind   - Run the application with valgrind"
	@echo "  test       - Run the tests"
	@echo "  test-with-valgrind - Run the tests with valgrind"
	@echo "  install    - Install the executable"
	@echo "  clean      - Clean the build directory"
	@echo "  rebuild    - Clean, configure, and build the project"
	@echo "  help       - Display this help message"
	@echo ""

.PHONY: all configure build build-test run valgrind test test-with-valgrind install clean rebuild release help
