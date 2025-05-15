#!/bin/bash

[ $# -eq 0 ] && exit 1

pattern="$1"

while IFS= read -r line; do
    output=""
    i=0
    len=${#line}

    while [ $i -lt $len ]; do
        char="${line:$i:1}"
        
        match=0
        j=0
        k=$i
        while [ $k -lt $len ] && [ $j -lt ${#pattern} ] && [ "${line:$k:1}" = "${pattern:$j:1}" ]; do
            ((k++))
            ((j++))
        done

        if [ $j -eq ${#pattern} ]; then
            for ((x=0; x<${#pattern}; x++)); do
                output+="*"
            done
            ((i+=j))
        else
            output+="$char"
            ((i++))
        fi
    done

    echo "$output"
done