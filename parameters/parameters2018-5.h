#include "Variable.h"
int doSim = 0;
int year=2018;
//int newdata = 1;
int inputfile =1;
int debug = 1;
int Reverse =1;
int posFix =1;
int recab = 0;
int doNormalize=1;
int runinfo =0;
int sPHENIXStyle = 0;
int dohodo = 1;
int hodoX =1;
int hodoY =1;
TString ordertag = "7th";
void ReverseXAxis(TH1 *h);
void ReverseYAxis(TH1 *h);
//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root";
//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib/dst.lst_EMCalCalib.root";
//TString InputFile ="/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root";
//TString InputFile = "/gpfs/mnt/gpfs04/sphenix/user/jinhuang/Prototype_2018/ShowerCalib/dst.lst_EMCalCalib.root";

//TString InputFile ="/sphenix/user/zshi/sPHENIX/2018TestBeam/MyCode/EnergyScan/Codes/analysis/Prototype4/EMCal/macros/ScanList.list_EMCalCalib.root";
int correction = 2;
double anglecorr = 0.705025751;
double shifty = 290;
double shiftx = 120;

TString InputFile ="/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/7thPositionScan/dst.lst_EMCalCalib.root";

//TString InputFile ="/sphenix/user/zshi/sPHENIX/2018TestBeam/MyCode/EnergyScan/Codes/analysis/Prototype4/EMCal/macros/ScanListDual.list_EMCalCalib.root";

//TString InputFile="/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/4thPositionScan/dst.lst_EMCalCalib.root";

//TString InputFile = "/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/3rdPositionScan/dst.lst_EMCalCalib.root";

TString scale = "1.0";
TString scalerecab= "1.0";
TString PositionFile = "DatFiles/XYPosition7.dat";
TString MakePlotInf="HisFiles/HisAll.root";
TString PosFixOut="ROOTFiles/PosFix.root";
TString OutFileMakeFile = "ROOTFiles/His3.root";
TString OutFileReadHis2 = "ROOTFiles/EnergyPosition.root";
TString OutFileInter = "ROOTFiles/Interpolated.root";
TString HodoScope = "ROOTFiles/AVHS.root";
TString InterpolatedFile =Form("ROOTFiles/%d/Interpolated2Reversed.root",year);
TString ProjectionFile =Form("ROOTFiles/%d/Projection%s.root",year,ordertag.Data());
TString RMSFile =Form("ROOTFiles/%d%sRMS.root",year,ordertag.Data());

const int Xmin = 380 - correction;  
const int Xmax = 600 - correction;
const int Ymin = 10 - correction;
const int Ymax = 210 - correction;
const int Emin = 0;
const int Emax = 12;
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
const double EminHis = 4.5;
const double EmaxHis = 8.5;

const double Estep = 0.2;
const double Runstep = 5;
const int Statstep = 5;
/*
double LowEThres = 2;
double HighEThres = 10;

const double FitEmin = 3.0;
const double FitEmax = 11.0;

const int HisEmin = 2.0;
const int HisEmax = 12.0;
*/
double LowEThres = 2.0;
double HighEThres = 11.0;

const double FitEmin = 5.0;
const double FitEmax = 10.0;

const double HisEmin = 0;
const double HisEmax = 9.5;
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



int ThresX = 3;
int ThresY= 5;
int ThresYH = 15;


double yshift = 0;
double xshift = 0;


//const int Runmin = 901;  
//const int Runmax= 995;
//const int Runmin =380;  
//const int Runmax=420;


const int Runmin = 2289;  
const int Runmax= 2360;

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
double Y1 = 33 + yshift;
double Y2 = 57 + yshift;
double Y3 = 83 + yshift;
double Y4 = 108 + yshift;
double Y5 = 135 + yshift;
double Y6 = 157 + yshift;
double Y7 = 183 + yshift;

double x1 = 414 + xshift;
double x2 = 441 + xshift;
double x3 = 468 + xshift;
double x4 = 492 + xshift;
double x5 = 523 + xshift;
double x6 = 549 + xshift;
double x7 = 577 + xshift;


double YBL = Y1;
double YBR = Y5;

double XBL = x1;
//double XBL = 427;
double XBR = x5;

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


const int iFile = 2289;
const int fFile = 2361;

//const int nFiles = fFile-iFile+1;
const int nFiles = 72;

double ProjectionXmin = x1;
double ProjectionYmin = Y1;

double ProjectionstepX = (x2 - x1)/2;
double ProjectionstepY = (Y2 - Y1)/2;
const int Binwidth = 10;

const int NTowerX = 7;
const int NTowerY = 7;


double xinitial[NTowerX*2-1] = {x1,(x1+x2)/2,x2,(x2+x3)/2,x3,(x3+x4)/2,x4,(x4+x5)/2,x5,(x5+x6)/2,x6,(x6+x7)/2,x7};
double yinitial[NTowerY*2-1] = {Y1,(Y1+Y2)/2,Y2,(Y2+Y3)/2,Y3,(Y3+Y4)/2,Y4,(Y4+Y5)/2,Y5,(Y5+Y6)/2,Y6,(Y6+Y7)/2,Y7};


//HisFiles//
//

