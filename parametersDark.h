int Year=2018;
TString Ordertag = "Simulations-10Degree-DarkFiber";




//TFile * finData = new TFile("ROOTFiles/2018Simulations-10Degree-Sean-UpdatedRMS.root");
//TFile * finMC = new TFile("ROOTFiles/2018SimulationsRMS.root");
TFile * finData = new TFile("ROOTFiles/2018Simulations-10DegreeRMS.root");
TFile * finMC = new TFile("ROOTFiles/2018Simulations-10Deg-DeadFiberRMS.root");
int sizeX = 1;
int stepX = 25;
int NBlockX = 4;
int MaxBinX = stepX * (NBlockX - 0);
int NBinX = MaxBinX/sizeX;

int sizeY = 1;
int stepY = 27;
int NBlockY = 4;
int MaxBinY = stepY *(NBlockY - 0);
int NBinY = MaxBinY/sizeY;
double EMinBoth = 5.5;
double EMaxBoth = 9.5;

double EMinNBoth = 0.65;
double EMaxNBoth = 1.30;



TString DataMCPlotX = Form("DarkFiberComp%d/DarkFiberX",Year);
TString DataMCPlotY = Form("DarkFiberComp%d/DarkFiberY",Year);



TString DataPlotX = Form("DarkFiberComp%d/DataX",Year);
TString DataPlotY = Form("DarkFiberComp%d/DataY",Year);


TString MCPlotX = Form("DarkFiberComp%d/MCX",Year);
TString MCPlotY = Form("DarkFiberComp%d/MCY",Year);



TString DataMCPlotXNormalized = Form("DarkFiberComp%d/DarkFiberXNormalized",Year);
TString DataMCPlotYNormalized = Form("DarkFiberComp%d/DarkFiberYNormalized",Year);



TString DataMCPlotXRatio = Form("DarkFiberComp%d/DarkFiberXRatio",Year);
TString DataMCPlotYRatio = Form("DarkFiberComp%d/DarkFiberYRatio",Year);






int MinDataY = 90;
//int MaxDataY = MinDataY + MaxBinY;
int MinDataX = 59;
//int MaxDataX = MinDataX + MaxBinX;

int MinMCY = 90;
//int MaxMCY = MinMCY + MaxBinY;
int MinMCX = 59;
//int MaxMCX = MinMCX + MaxBinX;





