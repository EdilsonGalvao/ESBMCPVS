echo "Test Case 01"
date
rm -r TC01.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC01_opt_PVcode.c
zip -r TC01.zip output
rm -r output

echo "Test Case 02"
date
rm -r TC02.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC02_opt_PVcode.c
zip -r TC02.zip output
rm -r output

echo "Test Case 03"
date
rm -r TC03.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC03_opt_PVcode.c
zip -r TC03.zip output
rm -r output

echo "Test Case 04"
date
rm -r TC04.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC04_opt_PVcode.c
zip -r TC04.zip output
rm -r output

echo "Test Case 05"
date
rm -r TC05.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC05_opt_PVcode.c
zip -r TC05.zip output
rm -r output

echo "Test Case 06"
date
rm -r TC06.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC06_opt_PVcode.c
zip -r TC06.zip output
rm -r output

echo "Test Case 07"
date
rm -r TC07.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC07_opt_PVcode.c
zip -r TC07.zip output
rm -r output
