for i in {0..60}
    do
	if [ -d Niv_$i ]; then rm -Rf Niv_$i; fi
	mkdir -p Niv_$i
	cd Niv_$i
	ln -s ../secondaryNTuples.* .
        cp ../Pi0EmbedFiles.C .
	cp ../Pi0EmbedFiles.h .
	cp ../DeadWarnRun16.txt .
	cp ../timingDeadMap_sig1p47.txt timingDeadWarnRun16.txt 
	ln -s /phenix/scratch/nivram/Pi0/middle/simPi0_$i.root pi0_dAuMB.root
	mkdir out/
	mkdir log/
	mkdir error/
	condor_submit secondaryNTuples.job
    
	cd ../
done
