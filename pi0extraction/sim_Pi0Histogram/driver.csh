#!/bin/tcsh
source ./setup_env.csh

echo '********************************************************************'
which root
root -b <<EOF
1+1

.L Pi0EmbedFiles.C
Pi0EmbedFiles t
t
EOF

#t.Loop()
