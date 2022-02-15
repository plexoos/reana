#!/bin/tcsh
source ./setup_env.csh

echo 'MB   ********************************************************************'
root -l -b -q 'pi0extraction.C("MB", "PbSc", 4,5)'

echo 'ERT  ********************************************************************'
root -l -b -q 'pi0extraction.C("ERT", "PbSc", 4,5)'

echo 'Done ********************************************************************'

#echo root -l -b -q 'WGRatio.cc'
#root -l -b -q 'WGRatio.cc'


# Migrated into a separate workflow
# echo '********************************************************************'
# echo root -l -b -q 'generationRM_Pi0.cc'
# root -l -b -q 'generationRM_Pi0.cc'

################################

# echo '********************************************************************'
#echo root -l -b -q 'VConvolution_Pi0.cc'
#root -l -b -q 'VConvolution_Pi0.cc'

#echo '\n'
#echo '********************************************************************'
#echo '------ the end -------'
