setenv OFFLINE_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/release/release_new/new
setenv ONLINE_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/release/release_new/new
setenv ROOTSYS /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/opt/phenix/core/root-5.34.36
setenv G4_MAIN /cvmfs/phenix.sdcc.bnl.gov/x8664_sl7/opt/phenix/core/geant4.10.00.p02

source /opt/phenix/core/stow/opt_phenix_scripts/bin/phenix_setup.csh

setenv LD_LIBRARY_PATH .:$LD_LIBRARY_PATH

setenv  ODBCINI ${PWD}/afs/rhic.bnl.gov/phenix/etc/odbc.ini
setenv PG_PHENIX_DBNAME Phenix_phnxdbrcf2_C
