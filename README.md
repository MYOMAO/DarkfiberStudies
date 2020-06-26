### Please Read the Following Instruction to Get Started ###

This repository is made to run the Analysis Macros for sPHENIX EMCAL.




## To START ##

Open a fresh folder on RCF

First clone the entire repository from github:

git clone https://github.com/MYOMAO/DarkfiberStudies.git

To test the Dark Fiber codes, just do 

sh runall.sh 2018 16


root -b -l -q DarkFiberCompAll.C 


All the Dark Fiber studies with Craig's suggested configuration are saved at the folder:

PlotDarkCompAll/

The 2D projection map are shown at 

PlotDarkCompAll/New


## Analysis Structure ##

The analysis workflow of the codes is shown as follows


Cleaning the previously existed files     ------>>>>>   Initialize the parameters according to your input    ----->>>>>   Fix the position of the test beam data due to hodoscope error (if the data is from 2018)     ----->>>>>    Project the energy response to the 3D histogram (X, Y, Energy) with good electron selections applied    ----->>>>>   Extract the mean energy by selecting a X Y bin according to the parameters and generate 2D map of mean energy vs X Y position    ----->>>>>   Interpolate the data due to the missing data between the position scan (Not needed for 2018 data/simulations)   ----->>>>>    Project energy along the X and Y with a given range (normally center of the towers and boundaries between the towers)   ----->>>>>     Compute the mean energy distribution within the central 4 x 4 towers, fit the data with Gaussian or do RMS/Mean, rescale them to unity to give conclusion about the uncertantiesof EMCAL energy measurement due to position non-uniformity


## To Run Your Own Analysis ##


To run the codes, you need to create your own parameter header file setup under the folder

parameters/parameters201X-Number.h


Here X = 7 or 8 and Number's ranges is from 1 - 16   


There is also a set of header files which is used to conduct Data-MC comparison:

parametersComp/parameters2018-CompNum.h

Here CompNum's range is from 6 - 9

For the moment, if we only do simulations, we do not need to run that

What you can do first is that copy a new one and name it as 17

cp parameters/parameters2018-16.h parameters/parameters2018-17.h

In the new header file parameters/parameters2018-17.h


For the moment, to let the codes run, you should only change the following:

doNormalize = 0 

If you change doNormalize to 1, you normalize the shape of the 2D projection on the X and Y axis to unity and compare them

TString ordertag = "DarkFiber-Craig-Config";

If you change this string, you change the tag on the file. Basically, when you change the simulation setup, create a name and replace this string by the name you created.

Also, you will need to modify the line

TFile * RMS10DegDFPart = new TFile("ROOTFiles/2018DarkFiber-Craig-ConfigRMS.root"); 

Also you may need to change the legend:  l->AddEntry(hProjXReDarkPart,"Dark Fiber 50% Masked Randomly Distributed"); to the simulation setup that you actually used in your jobs.

In your DarkFiberCompAll.C codes

To match the ordertag string to the root file name: 2018"ordertag"RMS.root.

TString InputFile="/sphenix/user/zshi/SimulationWork/2019sPHENIXAna/EMCAL/Simulations/TutorialTest/tutorials/AnaTutorial/src/condor/directory/outputfiles/CraigConigGood/CraigConfig.root";

Replace this string by the merged output file from your condor jobs.


Then simply do sh runall.sh 2018 17

root -b -l -q DarkFiberCompAll.C 


Note that you can also change the XY binning size by modifying the Variabl.h file

const double Xstep = 1;
const double Ystep = 1;
double XProjstep = 1;
double YProjstep = 1;
 
In test beam data, the XY binning size 5 mm x 5 mm. But in the simulation, since we can have much more events, we can bin it as 1 mm x 1 mm. You can use your own binning size by changing the values above.

Check if you are able to run the codes. If you see some files not saved because folders missing, mkdir the folder by yourself and rerun the shell script. 

There are a lot of details in the codes that I do not have time to explain in details.

If you have any question, please contact me
