#!/bin/bash

if [ -n "$1" ]; then
    cmd=$1
else
    cmd=./calc_big_int
fi

if [ -n "$2" ]; then
    test_cases=$2
else
    test_cases=test_cases.txt
fi

failures=0
DONE=false
until $DONE; do
    read test_case || DONE=true
    lineno=$((${lineno:=0}+1))
    args=$(echo $test_case | sed 's/^\(\([^\ ]*\ \)\{3\}\).*$/\1/')
    exp=$(echo $test_case | sed 's/^\(\([^\ ]*\ \{0,1\}\)\{3\}\)\(.*\)$/\3/')
    if [ ! -n "$args" -a ! -n "$exp" ]; then
        continue
    fi
    result=$($cmd $args 2>&1)
    exit_code=$?
    if [ "$exit_code" -ne "0" -a ! -n "$result" ]; then
        result="exception"
    fi
    if [ "$result" != "$exp" ]; then
        echo "**************************************************************"
        echo "File \"$test_cases\", line $lineno"
        echo "Failed case:"
        echo "  $args"
        echo "Expected:"
        echo "  $exp"
        echo "Got:"
        echo "  $result"
        echo "**************************************************************"
        failures=$(($failures+1))
    fi
done < $test_cases

if [ "$failures" -gt "0" ]; then
    echo "***Test Failed*** $failures failures."
fi
