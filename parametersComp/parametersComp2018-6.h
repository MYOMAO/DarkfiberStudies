
TFile * finData = new TFile("ROOTFiles/20185thRMS.root");
TFile * finMC = new TFile("ROOTFiles/2018SimulationsRMS.root");
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



TString DataMCPlotX = "DataMCComp/DataMCX";
TString DataMCPlotY = "DataMCComp/DataMCY";


TString DataPlotX = "DataMCComp/DataX";
TString DataPlotY = "DataMCComp/DataY";


TString MCPlotX = "DataMCComp/MCX";
TString MCPlotY = "DataMCComp/MCY";


TString DataMCPlotXNormalized = "DataMCComp/DataMCXNormalized";
TString DataMCPlotYNormalized = "DataMCComp/DataMCYNormalized";

TString DataMCPlotXRatio = "DataMCComp/DataMCXRatio";
TString DataMCPlotYRatio = "DataMCComp/DataMCYRatio";



int shifty = 14;
int shiftx = 12;


int MinDataY = 428 - shifty;
//int MaxDataY = MinDataY + MaxBinY;
int MinDataX = 65 - - shiftx;
//int MaxDataX = MinDataX + MaxBinX;

int MinMCY = 90 - shifty;
//int MaxMCY = MinMCY + MaxBinY;
int MinMCX = 60 + shiftx;
//int MaxMCX = MinMCX + MaxBinX;





