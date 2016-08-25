#!/bin/bash
for i in {1..500}; do
    NUM_PAREN=`shuf -i 1-30000 -n 1`
    NUM_ROT=`shuf -i 0-$NUM_PAREN -n 1`

    echo "$NUM_PAREN $NUM_ROT"
done
