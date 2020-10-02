#!/bin/bash
TM=36000

echo ----------------- ESBMC -----------------
echo --------------------01-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC01_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------02-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC02_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------03-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC03_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------04-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC04_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------05-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC05_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------06-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC06_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------07-------------------
date
timeout $TM ./esbmc/v6.4.0/bin/esbmc ./ESBMCPVS/Benchmark/ESBMC/TC07_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo 