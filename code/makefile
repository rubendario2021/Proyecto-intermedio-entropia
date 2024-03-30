# Directories

INC_DIR := include
IN_DIR := input
OUT_DIR := output
REP_DIR := report
PLT_DIR := plot

# Compilation flags

VAL := 0
OPT := 0
PROF := 0

CXX := g++
INCS := -I$(INC_DIR)
CXXFLAGS := -Wall -g
CXXOPTIMIZED := -O3
CXXSANITIZERS := -fsanitize=leak,address,undefined
CXXPROFILER := -pg
VALXXMEMCHECK := --tool=memcheck --track-origins=yes --leak-check=full
VALXXCACHEGRIND := --tool=cachegrind

# Input files

IFILE := $(INP_DIR)/input.txt
IFILE_PROF := $(INP_DIR)/input-profiling.txt

# General files

TARGET_P1 := P1.out
TARGET_P2 := P2.out
TARGET_P3 := P3.out
TARGET_P4 := P4.out

SRCS := $(filter-out P1.cpp P2.cpp P3.cpp P4.cpp, $(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)

# Report files

GPROF_RP1 := $(REP_DIR)/gprof-report-P1.txt
GPROF_RP2 := $(REP_DIR)/gprof-report-P2.txt
GPROF_RP3 := $(REP_DIR)/gprof-report-P3.txt
GPROF_RP4 := $(REP_DIR)/gprof-report-P4.txt

CACHEGRIND_RP1 := $(REP_DIR)/cachegrind-report-P1.txt
CACHEGRIND_RP2 := $(REP_DIR)/cachegrind-report-P2.txt
CACHEGRIND_RP3 := $(REP_DIR)/cachegrind-report-P3.txt
CACHEGRIND_RP4 := $(REP_DIR)/cachegrind-report-P4.txt

# gnuplot scripts

PLT_MOLECULES := $(PLT_DIR)/script_molecules.gp
PLT_ENTROPY := $(PLT_DIR)/script_entropy.gp
PLT_RSMD := $(PLT_DIR)/script_rsmd.gp

# Plotting data

MOL_DATA := $(OUT_DIR)/*/molecules*.txt
ENT_DATA := $(OUT_DIR)/*/entropy*.txt
RSMD_DATA := $(OUT_DIR)/*/rmsd*.txt

# --------------------------------------------------------------------------------------------

.PHONY: clean

# Makefile instructions for each point

run_P1: $(TARGET_P1)
	./$^ $(IFILE)

gprof_P1: $(TARGET_P1)
	./$^ $(IFILE_PROF)
	gprof $^ gmon.out > $(GPROF_RP1)

cachegrind_P1: $(TARGET_P1)
	valgrind $(VALXXCACHEGRIND) ./$^ $(IFILE_PROF)
	cg_annotate --auto=yes *.out.* > $(CACHEGRIND_RP1)

memcheck_P1: $(TARGET_P1)
	valgrind $(VALXXMEMCHECK) ./$^ $(IFILE_PROF)

# Makefile core instructions

%.o: %.cpp
ifeq ($(OPT), 1)
	$(CXX) $(INCS) $(CXXFLAGS) $(CXXOPTIMIZED) -c $^ -o $@
else ifeq ($(PROF), 1)
	$(CXX) $(INCS) $(CXXFLAGS) $(CXXPROFILER) -c $^ -o $@
else
	$(CXX) $(INCS) $(CXXFLAGS) -c $^ -o $@
endif

%.out: %.o $(OBJS)
ifeq ($(VAL), 1)
	$(CXX) $^ -o $@
else ifeq ($(PROF), 1)
	$(CXX) $(CXXPROFILER) $^ -o $@
else
	$(CXX) $(CXXSANITIZERS) $^ -o $@
endif

# PLotting targets

plot_molecules: $(PLT_MOLECULES) $(MOL_DATA)
	@for F in $(MOL_DATA); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

plot_entropy: $(PLT_ENTROPY) $(ENT_DATA)
	@for F in $(ENT_DATA); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

# Clean targets

clean:
	rm -f *.out *.out.* *.o
	rm -f $(MOL_DATA) $(ENT_DATA) $(RSMD_DATA)