#!/bin/bash
TM=36000

echo ----------------- ESBMC -----------------
echo --------------------01-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC01_opt_PVcode.c --incremental-bmc --boolector> case01.txt
date
echo --------------------02-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC02_opt_PVcode.c --incremental-bmc --boolector> case02.txt
date
echo --------------------03-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC03_opt_PVcode.c --incremental-bmc --boolector> case03.txt
date
echo --------------------04-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC04_opt_PVcode.c --incremental-bmc --boolector> case04.txt
date
echo --------------------05-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC05_opt_PVcode.c --incremental-bmc --boolector> case05.txt
date
echo --------------------06-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC06_opt_PVcode.c --incremental-bmc --boolector> case06.txt
date
echo --------------------07-------------------
date
timeout $TM ../../../esbmc/v6.4.0/bin/esbmc TC07_opt_PVcode.c --incremental-bmc --boolector> case07.txt
date
echo 
