echo "Test Case 01 - Reduced"
date
SECONDS=0
../../../../esbmc TC01_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC01_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC01_opt_PVcode_reduced.txt
date

echo "Test Case 02 - Reduced"
date
SECONDS=0
../../../../esbmc TC02_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC02_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC02_opt_PVcode_reduced.txt
date

echo "Test Case 03 - Reduced"
date
SECONDS=0
../../../../esbmc TC03_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC03_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC03_opt_PVcode_reduced.txt
date

echo "Test Case 04 - Reduced"
date
SECONDS=0
../../../../esbmc TC04_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC04_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC04_opt_PVcode_reduced.txt
date

echo "Test Case 05 - Reduced"
date
SECONDS=0
../../../../esbmc TC05_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC05_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC05_opt_PVcode_reduced.txt
date

echo "Test Case 06 - Reduced"
date
SECONDS=0
../../../../esbmc TC06_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC06_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC06_opt_PVcode_reduced.txt
date

echo "Test Case 07 - Reduced"
date
SECONDS=0
../../../../esbmc TC07_opt_PVcode_reduced.c --incremental-bmc --boolector > Result_TC07_opt_PVcode_reduced.txt
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed." > ResultTime_TC07_opt_PVcode_reduced.txt
date
