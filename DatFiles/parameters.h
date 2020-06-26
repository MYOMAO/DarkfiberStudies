const int Xmin = 400;  
const int Xmax = 600;
const int Ymin = 80;
const int Ymax = 220;
const int Emin = 0.0;
const int Emax = 9.0;
const double Xstep =1;
const double Ystep =1;
const double Estep = 0.1;
const double Runstep = 1;

const int Runmin = 420;  
const int Runmax = 500;

const int XBinsCal = (Xmax - Xmin)/Xstep;
const int YBinsCal =  (Ymax - Ymin)/Ystep;
const int EBinsCal = (Emax - Emin)/Estep;
const int RunBinCal = (Runmax - Runmin)/Runstep;

const int XBins = XBinsCal;
const int YBins = YBinsCal;
const int EBins = EBinsCal;
const int RunBins = RunBinCal;

double yshift = 11;
double xshift =16;

//Set Tower Horizontal Lines//
double y1 = 82 + yshift;
double y2 = 107 + yshift;
double y3 = 132 + yshift;
double y4 = 157 + yshift;
double y5 = 182 + yshift;
double y6 = 207 + yshift;

double x1 = 442 + xshift;
double x2 = 467 + xshift;
double x3 = 492 + xshift;
double x4 = 517 + xshift;
double x5 = 542 + xshift;

//Set Tower Vertical Lines//


const int iFile = 322;
const int fFile = 568;

const int N = fFile-iFile+1;
const int nFiles = N;

TString OutFileMakeFile = "ROOTFiles/His3.root";
TString OutFileReadHis2 = "ROOTFiles/EnergyPosition.root";
TString OutFileInter = "ROOTFiles/Interpolated.root";
TString HodoScope = "ROOTFiles/AVHS.root";
