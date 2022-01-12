#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root >> output.txt
root -l -b << ./pi0run.script
