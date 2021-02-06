echo "Test Case 05 - Reduced"
date
rm -r TC05_Reduced.zip
../../../CPAchecker/scripts/cpa.sh -heap 64000m -config ../../../CPAchecker/config/bmc-incremental.properties -spec ../../../CPAchecker/config/specification/sv-comp-reachability.spc TC05_opt_PVcode.c
date
zip -r TC05.zip output
mv output outputTC05

