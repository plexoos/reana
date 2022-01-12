#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root >> output.txt

root -b <<EOF >> output.txt
1+1
EOF
#.L Pi0EmbedFiles.C
##Pi0EmbedFiles t
t.Loop()
