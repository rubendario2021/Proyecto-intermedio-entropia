# Directories

BIN_DIR := bin
BUILD_DIR := build
INP_DIR := input
OUT_DIR := output
SRC_DIR := src
INC_DIR := include
PLT_DIR := plot

# Compilation flags

CXX := g++
CXXFLAGS := -Wall -g
CXXSANITIZERS := -fsanitize=leak,address,undefined
CXXPROFILER := -pg
VALXXMEMCHECK := --tool=memcheck --track-origins=yes --leak-check=full
VALXXCACHEGRIND := --tool=cachegrind

# Input files

IFILE := $(INP_DIR)/input.txt
IFILE_PROF := $(INP_DIR)/input-profiling.txt

# Input paths

TARGET_P1 := $(BIN_DIR)/P1.out
TARGET_VP1 := $(BIN_DIR)/P1_valgrind.out

SRCS := $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'P2.cpp' ! -name 'P3.cpp' ! -name 'P4.cpp')
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.cpp=%.o))
INCS := -I$(INC_DIR)

# gnuplot scripts

PLT_MOLECULES := $(PLT_DIR)/script_molecules.gp
PLT_ENTROPY := $(PLT_DIR)/script_entropy.gp
PLT_RSMD := $(PLT_DIR)/script_rsmd.gp

# Output paths

OUT_P1 := $(OUT_DIR)/P1
OUT_P1_MOL := $(OUT_P1)/molecules

OUT_MOL := $(shell find $(OUT_P1_MOL) -name '*.txt')
OUT_ENTROPY := $(shell find $(OUT_P1) -name '*.txt' ! -name 'rmsd.txt' ! -wholename '*/molecules/*')
OUT_RSMD := $(shell find $(OUT_P1) -name '*.txt' ! -name 'entropy.txt' ! -wholename '*/molecules/*')

# General makefile instructions

# Target by default
all: run

# Target that execute and plot the data
run:
	$(MAKE) clean
	$(MAKE) run_P1
	$(MAKE) plot_molecules_P1 plot_entropy_P1

# Target that execute with optimizers
run_optimized:
	$(MAKE) clean
	$(MAKE) run_P1 CXXFLAGS="$(CXXFLAGS) -O3"

# Target that execute the test for certain functions
test:
	$(MAKE)

# Target that perform a profiling using gprof
gprof:
	$(MAKE)

cachegrind:
	$(MAKE) clean
	$(MAKE) cachegrind_P1

memcheck:
	$(MAKE) clean
	$(MAKE) memcheck_P1

# Makefile instructions for each point

run_P1: $(TARGET_P1)
	./$^

memcheck_P1: $(TARGET_VP1)
	valgrind $(VALXXMEMCHECK) ./$^

cachegrind_P1: $(TARGET_VP1)
	valgrind $(VALXXCACHEGRIND) ./$^; \
#	cg_annotate --auto=yes cachegrind_output.txt > cachegrind-report.txt

plot_molecules_P1: $(PLT_MOLECULES) $(OUT_MOL)
	@for F in $(OUT_MOL); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

plot_entropy_P1: $(PLT_ENTROPY) $(OUT_ENTROPY)
	@for F in $(OUT_ENTROPY); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

# Makefile core instructions

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(INCS) $(CXXFLAGS) -c $^ -o $@

$(TARGET_P1): $(OBJS)
	$(CXX) $(CXXSANITIZERS) $^ -o $@

$(TARGET_VP1): $(OBJS)
	$(CXX) $^ -o $@

# Clean target

clean:
	rm -f $(BIN_DIR)/*.out $(BUILD_DIR)/*.o
	rm -f $(OUT_P1)/*.pdf $(OUT_P1)/*.txt $(OUT_P1_MOL)/*.pdf $(OUT_P1_MOL)/*.txt