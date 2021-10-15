#!/bin/tcsh
source ./setup_env.csh
env >> output.txt
echo '----------------------' >> output.txt
which root >> output.txt
root -l -b -q 'condor_Pi0Extraction.cc("MB", "PbSc", 4,5)'
echo '------ the end -------' >> output.txt