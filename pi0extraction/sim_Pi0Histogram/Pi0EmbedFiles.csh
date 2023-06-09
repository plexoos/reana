#!/bin/tcsh
source ./setup_env.csh

foreach i (`seq 0 1 $1`)
    ln -s gpfs/mnt/gpfs02/phenix/data_preservation/phnxreco/emcal/Pi0/middle/simPi0_$i.root pi0_dAuMB.root
    echo File: $i
    ls -l pi0_dAuMB.root
    cat pi0run.script | root -b
    mv EmbedPi0dAu.root EmbedPi0dAu_$i.root
    rm pi0_dAuMB.root
end
tar -cf embedPi0dAu.tar EmbedPi0dAu_*
