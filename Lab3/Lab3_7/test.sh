#!/bin/bash

PROGRAM="task_3_7.out"

INPUT_FILE="input.txt"

OUTPUT_FILE="output.txt"

TEMP_INPUT=$(mktemp)

cat <<EOF > $TEMP_INPUT
1
1
Bob
2
Bob Brown 1983.4.4
Bobr
Japerdole
Curva
2007
1
1
M
300.0
7
3
Eva Davis 1986.7.7
7
4
Bobr
Curva
0
1
11
2
M
10000.0
2
Grace Rodriguez 2038.11.29 
Bobr
Curva
0
2077
10
17
M
700.0
7
5
7
6
output.txt
8
EOF

./$PROGRAM $INPUT_FILE $OUTPUT_FILE < $TEMP_INPUT | tee output.log

echo "-"
echo "-"
echo "End Test"
echo "-"
echo "-"
