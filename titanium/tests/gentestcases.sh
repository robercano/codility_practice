#!/bin/bash
if [ "$1" == "" ]; then
    echo "Usage:"
    echo "    gentestcases.sh <num_cases>"
    echo ""
    exit 1
fi

for ((i=0; i<=$1; i++)); do
    NUM_PAREN=`shuf -i 1-30000 -n 1`
    NUM_ROT=`shuf -i 0-$NUM_PAREN -n 1`

    echo "$NUM_PAREN $NUM_ROT"
done
