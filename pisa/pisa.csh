#!/bin/tcsh


setenv OFFLINE_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/release/release_new/new
setenv ONLINE_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/release/release_new/new
setenv ROOTSYS /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/opt/phenix/core/root-5.34.36
setenv G4_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/opt/phenix/core/geant4.10.00.p02

#source /afs/rhic.bnl.gov/x8664_sl7/opt/phenix/core/stow/opt_phenix_scripts/bin/phenix_setup.csh
source /opt/phenix/core/stow/opt_phenix_scripts/bin/phenix_setup.csh
# /opt/phenix/core/bin/phenix_setup.csh

setenv  ODBCINI ${PWD}/afs/rhic.bnl.gov/phenix/etc/odbc.ini
# setenv  ODBCINI ${PWD}/afs/rhic.bnl.gov/phenix/etc/odbc.ini.phnxdbrcf2.orig
setenv PG_PHENIX_DBNAME Phenix_phnxdbrcf2_C
echo '---------------------------------------'

root -b -q Fun4Muons_Pisa.C
