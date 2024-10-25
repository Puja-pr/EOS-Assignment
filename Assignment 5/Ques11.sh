#!/bin/bash

echo "Enter the salary : "
read salary
DA=.4
HRA=.2

DA= echo "scale=2;`expr $DA \* $salary | bc`"

HRA= echo "scale=2;`expr $HRA \* $salary | bc`"

salary=`expr $salary - $DA - $HRA`

echo "Net salary = $salary"
