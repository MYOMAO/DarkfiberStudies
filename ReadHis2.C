#include <cmath>
#include <TFile.h>
#include <TString.h>
#include <TLine.h>
#include <TTree.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <cassert>
#include "SaveCanvas.C"
#include "SetOKStyle.C"
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "parameters.h"
//#include "Variable.h"

using namespace std;



using std::cout;
using std::endl;




void ReadHis2()
{
	TString Methodtag;
	TString recabtag;
	TString Typetag;
	TString Yeartag = Form("%d",year);

	if(Method == 0) Methodtag ="Mean";
	if(Method == 1) Methodtag ="Fits";
	if(recab == 0)  recabtag="prod";
	if(recab == 1)  recabtag="recalib";
	if(newdata == 0)
	{
		if ( inputfile==2) Typetag = "Interpolation-sPHENIX-Rotation-Preview-Reversed";
		if ( inputfile==1) Typetag = "Interpolation-sPHENIX-Rotation-Reversed";
		if ( inputfile==0) Typetag = "Interpolation-Dual-Channel-Reversed";
	}

	if(newdata == 1)
	{
		if ( inputfile==2) Typetag = "Interpolation-sPHENIX-Rotation-More-Reversed";
		if ( inputfile==1) Typetag = "Interpolation-sPHENIX-Rotation-Reversed";
		if ( inputfile==0) Typetag = "Interpolation-Dual-Channel-Reversed";
	}

		if(newdata == 2)
	{
		if ( inputfile==2) Typetag = "G4Simulations-10-Degrees";
		if ( inputfile==1) 	Typetag = "G4Simulations-5-Degrees";
		if ( inputfile==0) Typetag = "G4Simulations-0-Dergee";

	}

	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetPalette(55);
	TString TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());

	gSystem->Load("libg4eval.so");
	gSystem->Load("libqa_modules.so");
	gSystem->Load("libPrototype3.so");
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	double step = 1;
	TH3D * runhis = new TH3D("runhis","runhis",XBins,Xmin,Xmax,YBins,Ymin,Ymax,100,Runmin,Runmax);


	// Fitting: Method = 1; Mean: Method = 0//


	//   int Ini = 3543;
	//int Final = 3579;


	//double Xmin = 170;
	//double Xmax = 310.0;

	//double Ymin = 60;
	//double Ymax = 245.0;


	/*
	   int Xmin = 170;
	   int Xmax = 340.0;

	   int Ymin = 60;
	   int Ymax = 245.0;
	   */

	double Energy;
	double Energy_err;
	double Width;
	double Width_err;
	double Center;
	double Center_err;
	double xcent;
	double ycent;
	int x;
	int y;
	int xhigh;
	int yhigh;
	int binxhigh;
	int binyhigh;

	int binxcent;
	int binycent;


	int binx;
	int biny;
	int Stat;
	//int XBins = (Xmax - Xmin)/step;
	//int YBins = (Ymax - Ymin)/step;

	//int XBins = 200;
	//int YBins = 200;
	char Name[512];

	int index = 0;
	double average;
	int indexmax = XBins * YBins;
		

	//sprintf(inputfile,"His3.root");

	TFile *fin = new TFile(OutFileMakeFile.Data());
	TH2D *EnPo= new TH2D("EnPo","",XBins,Xmin,Xmax,YBins,Ymin,Ymax);
	TH2D *StatPo= new TH2D("StatPo","",XBins,Xmin,Xmax,YBins,Ymin,Ymax);
	StatPo->GetXaxis()->SetTitle("Horiztonal Position (mm)");
	StatPo->GetYaxis()->SetTitle("Vertical Position (mm)");
	StatPo->SetTitle("EMCAL Energy Spectra Statistics vs Position");
	EnPo->GetXaxis()->SetTitle("Horiztonal Position (mm)");
	EnPo->GetYaxis()->SetTitle("Vertical Position (mm)");
	EnPo->SetTitle("EMCAL Mean Energy vs Position");
	TH3D * Energyhis = (TH3D * ) fin->Get("Energyhis");


	TF1 *f1 = new TF1("f1","gaus",FitEmin,FitEmax);
	cout << "XBins = " << XBins << endl;
	cout << "YBins = " << YBins << endl;
	cout << "Energy His Average = " << Energyhis->GetMean() << endl;
	char hisname[512];

	for(int i = 0; i < XBins; i++)
	{

		x = Xmin + XProjstep*i;

		xhigh = Xmin + XProjstep*(i+1);

		xcent = (x + xhigh)/2;

		for(int j = 0; j < YBins; j++)
		{

			TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
			y = Ymin + YProjstep*j;
			yhigh = Ymin + YProjstep*(j+1);
			ycent = (y + yhigh)/2;
			//etTitle("Total Energy vs Position by Fitting");


			binx = Energyhis->GetXaxis()->FindBin(x+0.0001);
			biny = Energyhis->GetYaxis()->FindBin(y+0.0001);

			//binxhigh = binx +1;
			//binyhigh = biny +1;



			binxhigh = Energyhis->GetXaxis()->FindBin(xhigh-0.0001);
			binyhigh = Energyhis->GetYaxis()->FindBin(yhigh-0.0001);

			binxcent = Energyhis->GetXaxis()->FindBin(xcent);
			binycent = Energyhis->GetYaxis()->FindBin(ycent);

			TH1D *h5= new TH1D("h5","",25,HisEmin,HisEmax);


			cout << "binxcent = " << binxcent << "   binycent = " << binycent << endl;

			Energyhis->ProjectionZ("h5",binx,binxhigh,biny,binyhigh);
			Stat = h5->Integral();
			if(Stat == 0)
			{

				cout << "xcent = " << xcent << endl;	
				cout <<"binxcent = " << binxcent << endl;
				cout << "ycent = " << ycent << endl;	
				cout <<"binycent = " << binycent << endl;


			}
			StatPo->SetBinContent(binxcent,binycent,Stat);
			//return;
			cout << " Total Counts = " << h5->Integral() << endl;
			//return;




			//return;
			//

			//Fitting Method //
			if(Method ==1){

				//h5->Rebin(4);


				average = h5->GetMean();
				cout << "average is = " << average << endl;

				if(average > 1) 
				{

					h5->Fit(f1,"R");

					c1->Update();



					Energy = f1->GetParameter(0);
					Energy_err = f1->GetParError(0);
					Center = f1->GetParameter(1);
					Center_err = f1->GetParError(1);
					Width = f1->GetParameter(2);
					Width_err = f1->GetParError(2);


					// Center = h5->GetMean();

					// cout << "x = " <<  x << endl;

					//cout << "y = " <<  y << endl;

					cout << "Center = " << Center << endl;
					if(Center >HighEThres || Center < LowEThres){

						cout << "Old Center = " << Center << endl;

						Center = h5->GetMean();

						//		if(Center >HighEThres) Center = h5->GetMean() * 0.7;
						//if(Center < LowEThres) Center = h5->GetMean();

						cout << "New Center = " << Center << endl;
					}


					if(Center > LowEThres && Center < HighEThres){
						h5->Draw();

						h5->Fit(f1,"R");

						sprintf(Name,"%s Energy Distribution in x = %d mm and y = %d mm ",TitleName.Data(),x,y);
						h5->GetXaxis()->SetTitle("Energy (GeV)");
						h5->GetYaxis()->SetTitle("Counts");
						h5->SetTitle(Name);
						c1->Update();


						sprintf(hisname,"pngfiles/%d%s/Plot_%s_%d-%d.png",year,ordertag.Data(),TitleName.Data(),x,y);

						c1->SaveAs(hisname);


					}

				}


				if(average < 1) Center = 0; 


			}



			//Direct Mean Method//

			if(Method == 0) Center = h5->GetMean();


			EnPo->SetBinContent(binxcent,binycent,Center);
			//   EnPo->SetBinContent(binx,biny,Center);



			if(Center == 0){

				cout << "xcent = " << xcent << endl;	
				cout <<"binxcent = " << binxcent << endl;
				cout << "ycent = " << ycent << endl;	
				cout <<"binycent = " << binycent << endl;

			}

			index = index + 1;

		}

	}

	TCanvas *c22 = new TCanvas("c22", "c22",0,0,800,600);

	c22->cd();
	if(year == 2018){
		if(newdata == 1)
		{
			if ( inputfile==0) TitleName = "Fifth Position Scan (2018b, April 2018, Dual Channeling Rotation)";
			if ( inputfile==2) TitleName = "Sixth Position Scan (2018b, April 2018, sPHENIX+5)";
			if ( inputfile==1) TitleName = "Seventh Position Scan (2018b, April 2018, sPHENIX)";
		}
		if(newdata == 0)
		{
			if ( inputfile==0) TitleName = "Third Position Scan (2018a, March 2018, Dual Channeling Rotation)";
			if ( inputfile==1) TitleName = "Fourth Position Scan (2018a, March 2018, sPHENIX)";
		}
		if(newdata == 2)
		{
			if ( inputfile==0) TitleName = "2018 sPHENIX Simulation (eta ~ 1) 0 Degree";
			if ( inputfile==1) TitleName = "2018 sPHENIX Simulation (eta ~ 1) 5 Degree";
			if ( inputfile==2) TitleName = "2018 sPHENIX Simulation (eta ~ 1) 10 Degree";
		}
	}

	if(year == 2017){
		if ( inputfile==0) TitleName = "2017 Data: Energy vs Horizontal and Vertical Positions After Interpolation - 0 Degree Tilted";
		if ( inputfile==1) TitleName = "Energy vs Horizontal and Vertical Positions After Interpolation - 10 Degree Tilted";
	}
	EnPo->SetTitle(TitleName.Data());
	EnPo->SetMinimum(HisEmin);
	EnPo->Draw("COLZ");
	c22->Update();

	if(Method == 0) c22->SaveAs(Form("EnpoMeanMethod/EnPo%d%sScan.png",year,ordertag.Data()));
	if(Method == 1) c22->SaveAs(Form("EnpoFitsMethod/EnPo%d%sScan.png",year,ordertag.Data()));
	StatPo->Draw("colz");

	c22->Update();

	c22->SaveAs(Form("StatPo/StatPo%d%sScan.png",year,ordertag.Data()));



	//sprintf(Filename,"EnergyPosition.root");


	//sprintf(Filename,"EnergyPosition3.root");

	TFile *fout = new TFile(OutFileReadHis2.Data(),"RECREATE");
	EnPo->Write();
	StatPo->Write();

}
