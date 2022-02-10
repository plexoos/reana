#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
foreach i ( $num )
    ln -s gpfs/mnt/gpfs02/phenix/data_preservation/phnxreco/emcal/Pi0/middle/simPi0_$i.root pi0_dAuMB_$i.root
    echo $i
    #cat pi0run.script | root -b
    #mv EmbedPi0dAu.root EmbedPi0dAu_$i.root
    #rm pi0_dAuMB.root
end


