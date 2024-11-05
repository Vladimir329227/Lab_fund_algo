#!/bin/bash

PROGRAM="task_3_5.out"

INPUT_FILE="input.txt"

OUTPUT_FILE="output.txt"

TRASSET_FILE="trass.txt"


TEMP_INPUT=$(mktemp)

cat <<EOF > $TEMP_INPUT
1
1
2
Doe
3
John
4
GroupA
5
6
7
8
9
1
10
0
EOF

./$PROGRAM $INPUT_FILE $OUTPUT_FILE $TRASSET_FILE < $TEMP_INPUT | tee output.log

echo "-"
echo "-"
echo "End Test"
echo "-"
echo "-"
