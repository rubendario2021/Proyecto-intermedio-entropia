# Directories

CODE_DIR := code

# General makefile instructions

# Target by default
all: run

# Target that execute and plot the data
run:
	$(MAKE) -C $(CODE_DIR) run_P1
	$(MAKE) -C $(CODE_DIR) plot_molecules plot_entropy
	$(MAKE) -C $(CODE_DIR) clean

# Target that execute with optimizers
# OPT=1 activates the use of optimizers
run_optimized:
	$(MAKE) -C $(CODE_DIR) run_P1 OPT=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that execute the test for certain functions
test:
	$(MAKE) -C $(CODE_DIR)

# Target that perform profiling using gprof
# PROF=1 activates the use of gprof
gprof:
	$(MAKE) -C $(CODE_DIR) gprof_P1 PROF=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that perform profiling using valgrind-cachegrind
# PROF=1 activates the use of valgrind
cachegrind:
	$(MAKE) -C $(CODE_DIR) cachegrind_P1 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that perform memory usage using valgrind-memcheck
# PROF=1 activates the use of valgrind
memcheck:
	$(MAKE) -C $(CODE_DIR) memcheck_P1 VAL=1
	$(MAKE) -C $(CODE_DIR) clean

# Target that clean the output
clean:
	$(MAKE) -C $(CODE_DIR) clean