#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root >> output.txt

root -l -b <<EOF
.L Pi0EmbedFiles.C
Pi0EmbedFiles t
t.Loop()
EOF
