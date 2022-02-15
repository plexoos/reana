#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
echo Adding contents of embedding files
addPhenix EmbedPi0dAu.root EmbedPi0dAu_*
echo '********************************************************************'

#echo root -l -b -q 'generationRM_Pi0.C'
#root -l -b -q 'generationRM_Pi0.C'

echo '********************************************************************'

