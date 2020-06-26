#include "Variable.h"

int doSim = 0;
int year=2018;
int newdata = 0;
int inputfile =1;
int debug = 1;
int reverse =1;
int posFix =1;
int recab = 1;
int doNormalize=1;
int runinfo =1;
int sPHENIXStyle = 0;
int dohodo = 1;
int hodoX =0;
int hodoY =1;
TString ordertag = "4th";

//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root";
//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib/dst.lst_EMCalCalib.root";
//TString InputFile ="/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root";
//TString InputFile = "/gpfs/mnt/gpfs04/sphenix/user/jinhuang/Prototype_2018/ShowerCalib/dst.lst_EMCalCalib.root";

//TString InputFile ="/sphenix/user/zshi/sPHENIX/2018TestBeam/MyCode/EnergyScan/Codes/analysis/Prototype4/EMCal/macros/ScanList.list_EMCalCalib.root";

int correction = 0;

TString InputFile ="/sphenix/user/zshi/sPHENIX/2018TestBeam/MyCode/EnergyScan/Codes/analysis/Prototype4/EMCal/macros/ScanListsPHENIX.list_EMCalCalib.root";

//TString InputFile ="/sphenix/user/zshi/sPHENIX/2018TestBeam/MyCode/EnergyScan/Codes/analysis/Prototype4/EMCal/macros/ScanListDual.list_EMCalCalib.root";

//TString InputFile="/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/4thPositionScan/dst.lst_EMCalCalib.root";

//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/3rdPositionScan/dst.lst_EMCalCalib.root";

TString scale = "0.13";
TString scalerecab= "0.13";
TString PositionFile = "DatFiles/XYPosition3.dat";
TString MakePlotInf="HisFiles/HisAll.root";
TString PosFixOut="ROOTFiles/PosFix.root";
TString OutFileMakeFile = "ROOTFiles/His3.root";
TString OutFileReadHis2 = "ROOTFiles/EnergyPosition.root";
TString OutFileInter = "ROOTFiles/Interpolated.root";
TString HodoScope = "ROOTFiles/AVHS.root";
TString InterpolatedFile =Form("ROOTFiles/%d/Interpolated2Reversed.root",year);
TString ProjectionFile =Form("ROOTFiles/%d/Projection%s.root",year,ordertag.Data());
TString RMSFile =Form("ROOTFiles/%d%sRMS.root",year,ordertag.Data());

const int Xmin = 400 - correction;  
const int Xmax = 580 - correction;
const int Ymin = 80 - correction;
const int Ymax = 285 - correction;
const int Emin = 1.5;
const int Emax = 8.0;
const int Statmin = 0;
const int Statmax = 100;

/*
const int Xmin = 400;  
const int Xmax = 505;
const int Ymin = 150;
const int Ymax = 270;
//const int Emin = 3.8;
//const int Emax = 5.0;

const int Emin = 1.5;
const int Emax = 8.0;
*/
const double EminHis = 2.5;
const double EmaxHis = 5.5;


const double Estep = 0.2;
const double Runstep = 1;
const int Statstep = 5;
/*
double LowEThres = 2;
double HighEThres = 10;

const double FitEmin = 3.0;
const double FitEmax = 11.0;

const int HisEmin = 2.0;
const int HisEmax = 12.0;
*/

double LowEThres = 3.0;
double HighEThres = 6.0;

const double FitEmin = 2.0;
const double FitEmax = 8.0;

const int HisEmin = 0.0;
const int HisEmax = 10.0;
//For the 0 Degree Scan//
/*
   int Nearest=15; 
   int ThresX = 20;
   int ThresY= 8;
   double yshift = 11;
   double xshift =11;

*/
//Fot the 10 Degree Scan//
//	int Nearest=15; 



int ThresX = 20;
int ThresY= 50;
int ThresYH = 20;


double yshift = 21;
double xshift =8;


//const int Runmin = 901;  
//const int Runmax= 995;
//const int Runmin =380;  
//const int Runmax=420;

const int Runmin = 901;  
const int Runmax= 995;

const int XBinsCal = (Xmax - Xmin)/Xstep;
const int YBinsCal =  (Ymax - Ymin)/Ystep;
const int EBinsCal = (Emax - Emin)/Estep;
const int RunBinCal = (Runmax - Runmin)/Runstep;
const int StatBinsCal = (Statmax - Statmin)/Statstep;

const int XBins = XBinsCal;
const int YBins = YBinsCal;
const int EBins = EBinsCal;
const int RunBins = RunBinCal;
const int StatBins = StatBinsCal;
//

//Set Tower Horizontal Lines//
double y1 = 82 + yshift;
double y2 = 107 + yshift;
double y3 = 132 + yshift;
double y4 = 157 + yshift;
double y5 = 182 + yshift;
double y6 = 207 + yshift;
double y7 = 232 + yshift;

double x1 = 417 + xshift;
double x2 = 442 + xshift;
double x3 = 467 + xshift;
double x4 = 492 + xshift;
double x5 = 517 + xshift;
double x6 = 542 + xshift;


double YBL = y2;
double YBR = y6;

double XBL = x2;
double XBR = x6;

//Projection Centers//

double cxshfit = 4; 
double cyshift = 10;


double cy1 = 81.7 + cyshift;
double cy2 = 105.6 + cyshift;
double cy3 = 130.5 + cyshift;
double cy4 = 154.5 + cyshift;
double cy5 = 179.3 + cyshift;
double cy6 = 203.5 + cyshift;
double cy7 = 228.1 + cyshift;
double cy8 = 252.3 + cyshift;

double cx1 = 417.4 - cxshfit;
double cx2 = 443.0 - cxshfit;
double cx3 = 463.8 - cxshfit;
double cx4 = 489.4 - cxshfit;
double cx5 = 509.1 - cxshfit;
double cx6 = 534.6 - cxshfit;
double cx7 = 553.4 - cxshfit;



//Set Tower Vertical Lines//


const int iFile = 901;
const int fFile = 995;

//const int nFiles = fFile-iFile+1;
const int nFiles = 82;

double ProjectionXmin = x1;
double ProjectionYmin = y1;

double ProjectionstepX = (x2 - x1)/2;
double ProjectionstepY = (y2 - y1)/2;
const int Binwidth = 10;

const int NTowerX = 6;
const int NTowerY = 7;
double xinitial[NTowerX*2-1] = {x1,(x1+x2)/2,x2,(x2+x3)/2,x3,(x3+x4)/2,x4,(x4+x5)/2,x5,(x5+x6)/2,x6};
double yinitial[NTowerY*2-1] = {y1,(y1+y2)/2,y2,(y2+y3)/2,y3,(y3+y4)/2,y4,(y4+y5)/2,y5,(y5+y6)/2,y6,(y6+y7)/2,y7};



//HisFiles//
//

