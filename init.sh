#!/bin/sh -u
if [ -z "$BUILDTYPE" ] || [[ "$BUILDTYPE" == "Release" ]]; then
    export BINARY_TAG=x86_64-slc6-gcc49-opt
    export BUILDTYPE="Release"
else
    export BINARY_TAG=x86_64-slc6-gcc49-dbg
    export BUILDTYPE="Debug"
fi
source /afs/cern.ch/exp/fcc/sw/0.7/init_fcc_stack.sh afs

export GAUSSINO=/build/jlingema/gaussino_integration/Gauss/InstallArea/x86_64-slc6-gcc49-opt
export CMAKE_PREFIX_PATH=$GAUSSINO:$CMAKE_PREFIX_PATH
export PYTHONPATH=$GAUSSINO/python:$PYTHONPATH
