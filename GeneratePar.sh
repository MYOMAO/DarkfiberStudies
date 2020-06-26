#!/bin/bash

doSIM=1
SIMANGLE=5

SIMPAR=$((6+$SIMANGLE/5))


echo "SIMPAR = " $SIMPAR

rm -rf Variable.h

#newdata=0

if [ $doSIM -eq 0 ]; then    
DrawLine=1
Method=0
dointer=0
XStep=5
YStep=5
newdata=1
fi

if [ $doSIM -eq 1 ]; then    
DrawLine=1
Method=0
dointer=0
XStep=1
YStep=1
newdata=2
fi



echo "int newdata = ${newdata};" >> Variable.h
echo "int DrawLine = ${DrawLine};" >> Variable.h
echo "int Method = ${Method};" >> Variable.h
echo "int dointer = ${dointer};" >> Variable.h
echo "const double Xstep = ${XStep};" >>  Variable.h
echo "const double Ystep = ${YStep};" >>  Variable.h
echo "double XProjstep = ${XStep};" >>  Variable.h
echo "double YProjstep = ${YStep};" >>  Variable.h




if [ $doSIM -eq 0 ]; then    
#sh runall.sh 2017 0 
#sh runall.sh 2017 1
#sh runall.sh 2018 0
#sh runall.sh 2018 1
#sh runall.sh 2018 3
sh runall.sh 2018 4
#sh runall.sh 2018 5
fi

if [ $doSIM -eq 1 ]; then  
sh runall.sh 2018 $SIMPAR
fi


echo "ALL DONE BRO"

