#!/bin/bash

HASH_FUNCS=("1" "2")
COLLISION_STRATEGIES=("1" "2" "3")
DATASETS=("data1.txt" "data2.txt" "data3.txt")

echo "Hash Function,Collision Strategy,Dataset,Execution Time" > results.csv

for HASH_FUNC in "${HASH_FUNCS[@]}"; do
    for COLLISION in "${COLLISION_STRATEGIES[@]}"; do
        for DATASET in "${DATASETS[@]}"; do
            echo "Running test with Hash Function: $HASH_FUNC, Collision Strategy: $COLLISION, Dataset: $DATASET"
            TIME=$(./main $HASH_FUNC $COLLISION $DATASET | grep "Execution time" | awk '{print $3}')
            echo "$HASH_FUNC,$COLLISION,$DATASET,$TIME" >> results.csv
        done
    done
done
