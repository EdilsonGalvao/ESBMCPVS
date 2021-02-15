echo "Test Case 02 - Reduced"
date
rm -r TC02_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC02_opt_PVcode_reduced.c &
date
zip -r TC02_opt_PVcode_reduced.zip output
mv output TC02_opt_PVcode_reduced

echo "Test Case 03 - Reduced"
date
rm -r TC03_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC03_opt_PVcode_reduced.c &
date
zip -r TC03_opt_PVcode_reduced.zip output
mv output TC03_opt_PVcode_reduced

echo "Test Case 4 - Reduced"
date
rm -r TC04_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC04_opt_PVcode_reduced.c &
date
zip -r TC04_opt_PVcode_reduced.zip output
mv output TC04_opt_PVcode_reduced

echo "Test Case 5 - Reduced"
date
rm -r TC05_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC05_opt_PVcode_reduced.c &
date
zip -r TC05_opt_PVcode_reduced.zip output
mv output TC05_opt_PVcode_reduced

echo "Test Case 6 - Reduced"
date
rm -r TC06_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC06_opt_PVcode_reduced.c &
date
zip -r TC06_opt_PVcode_reduced.zip output
mv output TC06_opt_PVcode_reduced

echo "Test Case 7 - Reduced"
date
rm -r TC07_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC07_opt_PVcode_reduced.c &
date
zip -r TC07_opt_PVcode_reduced.zip output
mv output TC07_opt_PVcode_reduced

echo "Test Case 01 - Reduced"
date
rm -r TC01_opt_PVcode_reduced.zip
../../../../CPAchecker/scripts/cpa.sh -heap 64000M -config ../../../../CPAchecker/config/bmc-incremental.properties -spec ../../../../CPAchecker/config/specification/sv-comp-reachability.spc TC01_opt_PVcode_reduced.c &
date
zip -r TC01_opt_PVcode_reduced.zip output
mv output TC01_opt_PVcode_reduced