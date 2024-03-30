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
run_optimized:
	$(MAKE) -C $(CODE_DIR) run_P1 OPT=1

# Target that execute the test for certain functions
test:
	$(MAKE) -C $(CODE_DIR)

# Target that perform profiling using gprof
gprof:
	$(MAKE) -C $(CODE_DIR) gprof_P1 PROF=1

# Target that perform profiling using valgrind-cachegrind
cachegrind:
	$(MAKE) -C $(CODE_DIR) cachegrind_P1 VAL=1

# Target that perform memory usage using valgrind-memcheck
memcheck:
	$(MAKE) -C $(CODE_DIR) memcheck_P1 VAL=1