# Directories:
# List of all the directories in the directory
INC_DIR := include
IN_DIR := input
OUT_DIR := output
REP_DIR := report
PLT_DIR := plot

# Conditional variables:
# These values are used to change some commands
VAL := 0
OPT := 0
PROF := 0
TEST := 0

# Compiler and its compilations flags:
# Flags used in the instructions
CXX := g++
INCS := -I$(INC_DIR)
CXXFLAGS := --std=c++17 -Wall -g -c
CXXOPTIMIZED := -O3
CXXSANITIZERS := -fsanitize=leak,address,undefined
CXXPROFILER := -pg
CXXTEST := -l Catch2Main -l Catch2
VALXXMEMCHECK := --tool=memcheck --track-origins=yes --leak-check=full
VALXXCACHEGRIND := --tool=cachegrind

# Path to the input files:
# Relative path that indicates the program where to find the input files
IFILE := $(IN_DIR)/input.txt
IFILE_PROF := $(IN_DIR)/input-profiling.txt

# Executable files used in the program:
# List of all the expected executable that can be made within this project
TARGET_P1 := P1.out
TARGET_P2 := P2.out
TARGET_P3 := P3.out
TARGET_P4 := P4.out
TARGET_T := func_test.out

# Lookup of auxiliar source files:
# List of all the files and its object that are used in this project
SRCS := $(filter-out P1.cpp P2.cpp P3.cpp P4.cpp func_test.cpp, $(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)

# Report files:
# List of all the expected report files that can be made within this project
GPROF_RP1 := $(REP_DIR)/gprof-report-P1.txt
GPROF_RP2 := $(REP_DIR)/gprof-report-P2.txt
GPROF_RP3 := $(REP_DIR)/gprof-report-P3.txt
GPROF_RP4 := $(REP_DIR)/gprof-report-P4.txt

CACHEGRIND_RP1 := $(REP_DIR)/cachegrind-report-P1.txt
CACHEGRIND_RP2 := $(REP_DIR)/cachegrind-report-P2.txt
CACHEGRIND_RP3 := $(REP_DIR)/cachegrind-report-P3.txt
CACHEGRIND_RP4 := $(REP_DIR)/cachegrind-report-P4.txt

# gnuplot scripts:
# List of all the gnuplot used in this project
PLT_MOLECULES := $(PLT_DIR)/script_molecules.gp
PLT_ENTROPY := $(PLT_DIR)/script_entropy.gp
PLT_RMSD := $(PLT_DIR)/script_rmsd.gp
PLT_FIT_TS := $(PLT_DIR)/script_fit_ts.gp

# Plotting data:
# List of all the data that can be plotted in this project
MOL_DATA := $(OUT_DIR)/*/molecules*.txt
ENT_DATA := $(OUT_DIR)/*/entropy*.txt
RMSD_DATA := $(OUT_DIR)/*/rmsd*.txt
FIT_TS_DATA := $(OUT_DIR)/*/fit_ts*.txt

# --------------------------------------------------------------------------------------------

.PHONY: clean

# Test target:
# Evaluate the predefined test
test: $(TARGET_T)
	./$^

# Exec targets:
# One per point to solve. Execute and create its respective dependencies

# P1
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

# P2
run_P2: $(TARGET_P2)
	./$^ $(IFILE)

gprof_P2: $(TARGET_P2)
	./$^ $(IFILE_PROF)
	gprof $^ gmon.out > $(GPROF_RP2)

cachegrind_P2: $(TARGET_P2)
	valgrind $(VALXXCACHEGRIND) ./$^ $(IFILE_PROF)
	cg_annotate --auto=yes *.out.* > $(CACHEGRIND_RP2)

memcheck_P2: $(TARGET_P2)
	valgrind $(VALXXMEMCHECK) ./$^ $(IFILE_PROF)

# P3
run_P3: $(TARGET_P3)
	./$^ $(IFILE)

gprof_P3: $(TARGET_P3)
	./$^ $(IFILE_PROF)
	gprof $^ gmon.out > $(GPROF_RP3)

cachegrind_P3: $(TARGET_P3)
	valgrind $(VALXXCACHEGRIND) ./$^ $(IFILE_PROF)
	cg_annotate --auto=yes *.out.* > $(CACHEGRIND_RP3)

memcheck_P3: $(TARGET_P3)
	valgrind $(VALXXMEMCHECK) ./$^ $(IFILE_PROF)

# P4
run_P4: $(TARGET_P4)
	./$^ $(IFILE)

gprof_P4: $(TARGET_P4)
	./$^ $(IFILE_PROF)
	gprof $^ gmon.out > $(GPROF_RP4)

cachegrind_P4: $(TARGET_P4)
	valgrind $(VALXXCACHEGRIND) ./$^ $(IFILE_PROF)
	cg_annotate --auto=yes *.out.* > $(CACHEGRIND_RP4)

memcheck_P4: $(TARGET_P4)
	valgrind $(VALXXMEMCHECK) ./$^ $(IFILE_PROF)

# Makefile core targets:

# Compile all the .o files given its respective .cpp files
# Depending of the variables OPT, VAL and PROF change its instruction
%.o: %.cpp
ifeq ($(OPT), 1)
	$(CXX) $(INCS) $(CXXOPTIMIZED) $(CXXFLAGS) $^ -o $@
else ifeq ($(VAL), 1)
	$(CXX) $(INCS) $(CXXOPTIMIZED) $(CXXFLAGS) $^ -o $@
else ifeq ($(PROF), 1)
	$(CXX) $(INCS) $(CXXOPTIMIZED) $(CXXPROFILER) $(CXXFLAGS) $^ -o $@
else
	$(CXX) $(INCS) $(CXXFLAGS) $^ -o $@
endif

# Link all the .o files to generate the executable
# Depending of the variables VAL, PROF and TEST change its instruction
%.out: %.o $(OBJS)
ifeq ($(VAL), 1)
	$(CXX) $^ -o $@
else ifeq ($(PROF), 1)
	$(CXX) $(CXXPROFILER) $^ -o $@
else ifeq ($(TEST), 1)
	$(CXX) $^ -o $@ $(CXXTEST)
else
	$(CXX) $(CXXSANITIZERS) $^ -o $@
endif

# Plotting targets:

# Plot all the files that are related to molecules position
plot_molecules: $(PLT_MOLECULES) $(MOL_DATA)
	@for F in $(MOL_DATA); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

# Plot all the files that are related to system's entropy
plot_entropy: $(PLT_ENTROPY) $(ENT_DATA)
	@for F in $(ENT_DATA); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

# Plot all the files that are related to fit time vs size
plot_fit_ts: $(PLT_FIT_TS) $(FIT_TS_DATA)
	@for F in $(FIT_TS_DATA); do \
		gnuplot -c $< $$F $$(dirname $$F)/$$(basename $$F .txt).pdf; \
	done;

# Clean target:
# Delete all the output files
clean:
	rm -f *.out *.out.* *.o
	rm -f $(MOL_DATA) $(ENT_DATA) $(RSMD_DATA) $(FIT_TS_DATA)