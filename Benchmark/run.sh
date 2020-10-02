#!/bin/bash
TM=36000

echo ----------------- ESBMC -----------------
echo --------------------------------------
timeout $TM ./esbmc ./Benchmark/opt_PVcode_rev13_case5.c --incremental-bmc -dMycase=1 > case5.txt
echo
echo 