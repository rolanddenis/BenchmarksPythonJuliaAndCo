#!/usr/bin/env bash
set -e

if [ "$#" -ne 5 ]
then
    >&2 echo "Usage: $0 PROBLEM IMPLEMENTATION D N M"
    >&2 echo "Output: Matlab PROBLEM IMPLEMENTATION D N M MEMORY_USAGE WALL_TIME CHECKSUM"
    exit 1
fi

/usr/bin/time -v matlab -nodisplay -nojvm -r "disp('BEGIN');main $1 $2 $3 $4 $5;exit" >timing.tmp 2>memory.tmp
echo Matlab $1 $2 $3 $4 $5 $(grep "Maximum resident set size" memory.tmp | grep -o "[0-9]*") $(sed -e '1,/BEGIN/d' timing.tmp)

rm timing.tmp memory.tmp

