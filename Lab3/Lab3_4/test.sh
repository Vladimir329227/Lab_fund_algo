#!/bin/bash

TEMP_INPUT=$(mktemp)

cat <<EOF > $TEMP_INPUT
1
Moscow
Tverskaya
10
A
1
123456
2.5
12345678901234
01:01:2023/12:00:00
02:01:2023/12:00:00
3
12345678901234
2
12345678901234
4
5
6
EOF

valgrind ./task_3_4.out < $TEMP_INPUT

echo "-"
echo "-"
echo "End Test"
echo "-"
echo "-"

rm $TEMP_INPUT