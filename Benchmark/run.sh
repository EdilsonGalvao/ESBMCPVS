#!/bin/bash
TM=36000

echo -----------------
echo TC05 Incremental Result
date
timeout $TM ./esbmc ./Benchmark/pvs_CodeBase_ESBMC_optmized.c --incremental-bmc --boolector > tc05_opt_inc.txt
date
echo -----------------
echo TC05 Optmized
date
timeout $TM ./esbmc ./Benchmark/pvs_CodeBase_ESBMC_optmized.c --no-slice --quiet > tc05_opt.txt
date
echo -----------------
echo TC05 ESBMC
date
timeout $TM ./esbmc ./Benchmark/pvs_CodeBase_ESBMC.c --no-slice --quiet > tc05_ESBMC.txt
date
echo -----------------