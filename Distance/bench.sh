#!/usr/bin/env bash
set -e

if [ "$#" -ne 6 ]
then
    >&2 echo "Usage: $0 LANGUAGE PROBLEM IMPLEMENTATION D N M"
    >&2 echo "Output: LANGUAGE PROBLEM IMPLEMENTATION D N M MEMORY_USAGE WALL_TIME CHECKSUM"
    exit 1
fi

pushd $1 > /dev/null
shift
./bench.sh "$@"
popd > /dev/null
