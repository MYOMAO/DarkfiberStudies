Year=$1
File=$2

echo "START RUNUNG SCRIPT"

rm Results/*png
rm Results/$Year/*
#rm ROOTFiles/$Year/*
rm -rf pngfiles/$Year/*png
rm -rf pngfiles/$Year/Single/*png

echo "DONE CLEARING"


cp parameters/parameters${Year}-${File}.h parameters.h
cp parametersComp/parametersComp${Year}-${File}.h parametersComp.h

echo "START RUNNING MACROS"

if [ $Year -eq 2018 ]; then
	if [ $File -lt 6 ]; then
	root -b -l -q PosFix.C
	fi
fi


root -b -l -q MakeFile.C
root -b -l -q ReadHis2.C
root -b -l -q InterlopationV4reverse.C
root -b -l -q Projection2018.C
root -b -l -q RMS2018.C
                                    
