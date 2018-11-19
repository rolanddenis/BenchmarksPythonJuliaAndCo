#!/usr/bin/env bash
set -e

if [ "$#" -ne 5 ]
then
    >&2 echo "Usage: $0 PROBLEM IMPLEMENTATION D N M"
    >&2 echo "Output: Python PROBLEM IMPLEMENTATION D N M MEMORY_USAGE WALL_TIME CHECKSUM"
    exit 1
fi

# Pythran compilation
if [[ "$2" == Pythran_* ]]
then
    cd "$1/$2"
    make &> /dev/null # Error handling ?
    cd - > /dev/null
fi

/usr/bin/time -v python main.py $1 $2 $3 $4 $5 >timing.tmp 2>memory.tmp
echo Python $1 $2 $3 $4 $5 $(grep "Maximum resident set size" memory.tmp | grep -o "[0-9]*") $(cat timing.tmp)

rm timing.tmp memory.tmp

