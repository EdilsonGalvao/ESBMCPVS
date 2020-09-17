#!/bin/bash
TM=7200

echo TC01 Optmized
date
timeout $TM ./esbmc ./Benchmark/pvs_CodeBase_ESBMC_optmized.c --no-slice --quiet > tc01_opt.txt
date
echo -----------------
echo TC01 ESBMC
date
timeout $TM ./esbmc ./Benchmark/pvs_CodeBase_ESBMC.c --no-slice --quiet > tc01_ESBMC.txt
date
echo -----------------