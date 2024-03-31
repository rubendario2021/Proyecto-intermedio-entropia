# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++11
# Make sure your include directories paths are correctly specified here
INCLUDES := -I/workspaces/Project-intermediate-entropy/code/include -I/workspaces/Project-intermediate-entropy/Catch2-2.13.5/Catch2-2.13.5/include

# Directories
CODE_DIR := /workspaces/Project-intermediate-entropy/code
TEST_DIR := $(CODE_DIR)/test
BUILD_DIR := $(CODE_DIR)/build
TEST_BUILD_DIR := $(BUILD_DIR)/test

# Create build directories
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(TEST_BUILD_DIR))

# Sources and targets
SRCS := $(wildcard $(CODE_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
# Generates the object file names
OBJS := $(SRCS:$(CODE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(TEST_BUILD_DIR)/%.o)
TEST_EXEC := $(TEST_BUILD_DIR)/test_exec

.PHONY: all run run_optimized test gprof cachegrind memcheck clean

# Default target
all: run

# Compilation and execution of unit tests
test: $(TEST_EXEC)
	@echo "Running tests..."
	./$(TEST_EXEC)

# Additional rules from the first Makefile
run:
	$(MAKE) -C $(CODE_DIR) run_P1
	$(MAKE) -C $(CODE_DIR) plot_molecules plot_entropy
	$(MAKE) -C $(CODE_DIR) clean

run_optimized:
	$(MAKE) -C $(CODE_DIR) run_P1 OPT=1
	$(MAKE) -C $(CODE_DIR) clean

gprof:
	$(MAKE) -C $(CODE_DIR) gprof_P1 PROF=1
	$(MAKE) -C $(CODE_DIR) clean

cachegrind:
	$(MAKE) -C $(CODE_DIR) cachegrind_P1 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

memcheck:
	$(MAKE) -C $(CODE_DIR) memcheck_P1 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

# Rule to compile source files to objects
$(BUILD_DIR)/%.o: $(CODE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile test files to objects
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to link objects and create the test executable
$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) -o $@ $(INCLUDES)

# Cleaning up generated files
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)/* $(TEST_BUILD_DIR)/*
