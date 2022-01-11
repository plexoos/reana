#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
root -l -b -q 'pi0extraction.cc("MB", "PbSc", 4,5)'

echo '********************************************************************'

echo root -l -b -q 'pi0extraction.cc("ERT", "PbSc", 4,5)'
root -l -b -q 'pi0extraction.cc("ERT", "PbSc", 4,5)'

echo '********************************************************************'

echo root -l -b -q 'WGRatio.cc'
root -l -b -q 'WGRatio.cc'

echo '********************************************************************'

echo root -l -b -q 'generationRM_Pi0.cc'
root -l -b -q 'generationRM_Pi0.cc'

echo '********************************************************************'
#echo root -l -b -q 'VConvolution_Pi0.cc'
#root -l -b -q 'VConvolution_Pi0.cc'

#echo '\n'
#echo '********************************************************************'
#echo '------ the end -------'
