CXX := g++
BIN_DIR := bin
BUILD_DIR := build
OUTPUT_DIR := output
SRC_DIR := src
INC_DIR := include

TARGET := $(BIN_DIR)/P1.out
CXXFLAGS := -Wall -g

SRCS := $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'P2.cpp' ! -name 'P3.cpp' ! -name 'P4.cpp')
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.cpp=%.o))
INCS := $(foreach d, $(INC_DIR), -I$d)

run_P1: $(TARGET)
	./$^
	# ./$^ > $(OUTPUT_DIR)/output.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(INCS) $(CXXFLAGS) -c $^ -o $@

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

clean:
	rm -f $(BIN_DIR)/*.out $(BUILD_DIR)/*.o
	rm -f $(OUTPUT_DIR)/data.txt $(OUTPUT_DIR)/output.txt $(OUTPUT_DIR)/Posicion_salida.png