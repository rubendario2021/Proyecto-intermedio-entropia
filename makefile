# Directories

CODE_DIR := code

# --------------------------------------------------------------------------------------------

.PHONY: optimized no_optimized test gprof cachegrind memcheck clean

# Target by default
all: optimized

# Target that execute and plot the data
# OPT=1 activates the use of optimizers
optimized:
	$(MAKE) -C $(CODE_DIR) run_P1 OPT=1
#	$(MAKE) -C $(CODE_DIR) run_P2 OPT=1
#	$(MAKE) -C $(CODE_DIR) run_P3 OPT=1
#	$(MAKE) -C $(CODE_DIR) run_P4 OPT=1
	$(MAKE) -C $(CODE_DIR) plot_molecules plot_entropy
	$(MAKE) -C $(CODE_DIR) clean

# Target that execute with optimizers
no_optimized:
	$(MAKE) -C $(CODE_DIR) run_P1
#	$(MAKE) -C $(CODE_DIR) run_P2
#	$(MAKE) -C $(CODE_DIR) run_P3
#	$(MAKE) -C $(CODE_DIR) run_P4
	$(MAKE) -C $(CODE_DIR) clean

# Target that execute the test for certain functions
test:
	$(MAKE) -C $(CODE_DIR) test TEST=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that perform profiling using gprof
# PROF=1 activates the use of gprof
gprof:
#	$(MAKE) -C $(CODE_DIR) gprof_P1 PROF=1
#	$(MAKE) -C $(CODE_DIR) gprof_P2 PROF=1
#	$(MAKE) -C $(CODE_DIR) gprof_P3 PROF=1
	$(MAKE) -C $(CODE_DIR) gprof_P4 PROF=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that perform profiling using valgrind-cachegrind
# PROF=1 activates the use of valgrind
cachegrind:
#	$(MAKE) -C $(CODE_DIR) cachegrind_P1 VAL=1
#	$(MAKE) -C $(CODE_DIR) cachegrind_P2 VAL=1
#	$(MAKE) -C $(CODE_DIR) cachegrind_P3 VAL=1
	$(MAKE) -C $(CODE_DIR) cachegrind_P4 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that perform memory usage using valgrind-memcheck
# PROF=1 activates the use of valgrind
memcheck:
#	$(MAKE) -C $(CODE_DIR) memcheck_P1 VAL=1
#	$(MAKE) -C $(CODE_DIR) memcheck_P2 VAL=1
#	$(MAKE) -C $(CODE_DIR) memcheck_P3 VAL=1
	$(MAKE) -C $(CODE_DIR) memcheck_P4 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that clean the output
clean:
	$(MAKE) -C $(CODE_DIR) clean