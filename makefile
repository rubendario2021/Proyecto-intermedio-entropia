CXX := g++
BIN_DIR := bin
BUILD_DIR := build
OUT_DIR := output
PLT_DIR := plot
SRC_DIR := src
INC_DIR := include

TARGET := $(BIN_DIR)/P1.out
CXXFLAGS := -Wall -g

SRCS := $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'P2.cpp' ! -name 'P3.cpp' ! -name 'P4.cpp')
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.cpp=%.o))
INCS := $(foreach d, $(INC_DIR), -I$d)

# ---------------------------------------------------------------

OUT_P1_MOL := output/P1/molecules

OUT_MOL := $(shell find $(OUT_P1_MOL) -name '*.txt')
PDF_MOL := $(subst $(OUT_DIR), $(PLT_DIR), $(OUT_MOL:%.txt=%.pdf))

all: run_P1

run_P1: $(TARGET)
	./$^

plot_P1: 
	$(foreach d, $(OUT_MOL), gnuplot -e "input_file=$d" -e "output_file=" plot/script_molecules.gp)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(INCS) $(CXXFLAGS) -c $^ -o $@

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

clean:
	rm -f $(BIN_DIR)/*.out $(BUILD_DIR)/*.o