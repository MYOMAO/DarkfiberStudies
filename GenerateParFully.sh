#!/bin/bash

rm -rf Variable.h

XStep=$1
YStep=$2
DrawLine=$3
Method=$4
dointer=$5

echo "int newdata = ${newdata};" >> Variable.h
echo "int DrawLine = ${DrawLine};" >> Variable.h
echo "int Method = ${Method};" >> Variable.h
echo "int dointer = ${dointer};" >> Variable.h
echo "const double Xstep = ${XStep};" >>  Variable.h
echo "const double Ystep = ${YStep};" >>  Variable.h
echo "double XProjstep = ${XStep};" >>  Variable.h
echo "double YProjstep = ${YStep};" >>  Variable.h


sh runall.sh 2017 0 
sh runall.sh 2017 1
sh runall.sh 2018 0
sh runall.sh 2018 1
sh runall.sh 2018 3
sh runall.sh 2018 4
sh runall.sh 2018 5

echo "ALL DONE BRO"

