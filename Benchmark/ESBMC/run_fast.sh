#!/bin/bash
TM=36000

echo ----------------- ESBMC FAST -----------------
echo --------------------01-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC01_opt_PVcode.c --incremental-bmc --boolector --no-pointer-check --no-bounds-check --no-align-check --no-div-by-zero-check > Fast_case01.txt
date
echo
