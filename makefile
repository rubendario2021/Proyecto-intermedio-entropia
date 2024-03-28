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

OUT_P1 := $(OUT_DIR)/P1
OUT_P1_MOL := $(OUT_P1)/molecules

PLT_P1 := $(PLT_DIR)/P1
PLT_P1_MOL := $(PLT_P1)/molecules

OUT_MOL := $(shell find $(OUT_P1_MOL) -name '*.txt')
OUT_PARAMS := $(shell find $(OUT_P1) -name '*.txt')

all: run_P1 plot_molecules_P1

run_P1: $(TARGET)
	./$^

.ONESHELL:
plot_molecules_P1: $(PLT_DIR)/script_molecules.gp $(OUT_MOL)
	@for F in $(OUT_MOL)
	do
		gnuplot -c $< $$F $(PLT_P1_MOL)/$$(basename $$F .txt).pdf
	done

.ONESHELL:
plot_entropy_P1: $(PLT_DIR)/script_entropy.gp $(OUT_P1)/entropy_gs_8.txt
	@for F in $(OUT_P1)/entropy_gs_8.txt
	do
		gnuplot -c $< $$F $(PLT_P1)/$$(basename $$F .txt).pdf
	done 


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(INCS) $(CXXFLAGS) -c $^ -o $@

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

clean:
	rm -f $(BIN_DIR)/*.out $(BUILD_DIR)/*.o
	rm -f $(OUT_DIR)/P1/*.txt $(OUT_P1_MOL)/*.txt
	rm -f $(PLT_DIR)/P1/*.pdf $(PLT_P1_MOL)/*.pdf