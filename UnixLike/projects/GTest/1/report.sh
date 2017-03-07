#!/bin/sh
if [ "$1" = "clean" ] ; then
   rm -rf cov_report.zip cov_report
else
    lcov -c -d . -t unit_test -o unit_test.info --rc lcov_branch_coverage=1
    rm -rf cov_report
    genhtml unit_test.info -o cov_report -t "unit_test" -s --legend --rc lcov_branch_coverage=1
    rm -f unit_test.info cov_report.zip
    zip -r cov_report.zip cov_report
    echo "else"
fi
