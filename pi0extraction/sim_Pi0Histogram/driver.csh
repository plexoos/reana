#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root >> output.txt
cat ./pi0run.script | root -l -b
