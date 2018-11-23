#!/usr/bin/env bash
set -e

CXXFLAGS="-std=c++14 -O3 -march=native -mtune=native -DNDEBUG -fopenmp"

if [ "$#" -ne 5 ]
then
    >&2 echo "Usage: $0 PROBLEM IMPLEMENTATION D N M"
    >&2 echo "Output: C++ PROBLEM IMPLEMENTATION D N M MEMORY_USAGE WALL_TIME CHECKSUM"
    exit 1
fi

if [ -z ${CXX+x} ]
then
    CXX=c++
fi

#LDDFLAGS="-lmkl_rt"
#LDDFLAGS="-lopenblas"
# Write a real Makefile...
if [ "$2" = "Armadillo" ]
then
    LDDFLAGS="$LDDFLAGS -larmadillo"
fi

$CXX $CXXFLAGS -I. -DPROBLEM=$1 -DKERNEL=$2 main.cpp -o bench_cpp $LDDFLAGS
/usr/bin/time -v ./bench_cpp $3 $4 $5 >timing.tmp 2>memory.tmp
echo C++ $1 $2 $3 $4 $5 $(grep "Maximum resident set size" memory.tmp | grep -o "[0-9]*") $(cat timing.tmp)

rm bench_cpp timing.tmp memory.tmp
