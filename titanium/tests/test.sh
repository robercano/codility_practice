#!/bin/bash

TESTFILE=$1

if [ "$TESTFILE" == "" ]; then
    echo "Usage:"
    echo "  test.sh <tescases_file>"
    echo ""
    exit 1
fi

SEED=123213

while read -r NUMPAR NUMROT; do
    ./titanium -s $SEED -n $NUMPAR -k $NUMROT
    SEED=$((SEED+1))
done < $TESTFILE
