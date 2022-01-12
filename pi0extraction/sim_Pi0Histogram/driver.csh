#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root
root -b <<EOF
1+1
.L Pi0EmbedFiles.C
Pi0EmbedFiles t
t
2+2
t.Loop()
3+3
EOF

