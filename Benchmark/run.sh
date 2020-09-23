#!/bin/bash
TM=36000
echo ----------------- Z3 -----------------
echo --------------------------------------
timeout $TM dotnet run --project ./Benchmark/vZ/ 1
#timeout $TM dotnet run --project ./Benchmark/vZ/ 2
#timeout $TM dotnet run --project ./Benchmark/vZ/ 3
#timeout $TM dotnet run --project ./Benchmark/vZ/ 4
#timeout $TM dotnet run --project ./Benchmark/vZ/ 5
#timeout $TM dotnet run --project ./Benchmark/vZ/ 6
#timeout $TM dotnet run --project ./Benchmark/vZ/ 7
echo
echo 