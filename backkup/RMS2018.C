#include <cmath>
#include <TFile.h>
#include <TString.h>
#include <TLine.h>
#include <TTree.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include "parameters.h"
#include "Variable.h"
#include <fstream>
using namespace std;



using std::cout;
using std::endl;
#endif

void RMS2018()
{
	int BinRefine = 2;
	gSystem->Load("libg4eval.so");
	gSystem->Load("libqa_modules.so");
	gSystem->Load("libPrototype3.so");
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	TString Yeartag = Form("%d",year);
	TString Methodtag;
	TString recabtag;
	TString Typetag;
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
		Typetag = "2018 sPHENIX Simulation (eta ~ 1)";
	}

	TString OutPlotName;
	OutPlotName = Form("Results/%s_%s_%s_%s.png",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());
	TString TitleName; 


	if(year == 2018)	TFile *fin = new TFile(ProjectionFile.Data());

	if(year == 2017)	TFile *fin = new TFile(InterpolatedFile.Data());

	TH2D * Inter = (TH2D *) fin->Get("Inter"); 
	TH1D * MEHis = new TH1D("MEHis","MEHis",EBins*BinRefine,Emin,Emax);




	int XBinMin = Inter->GetXaxis()->FindBin(XBL);
	int XBinMax = Inter->GetXaxis()->FindBin(XBR);

	int YBinMin = Inter->GetYaxis()->FindBin(YBL);
	int YBinMax = Inter->GetYaxis()->FindBin(YBR);

	cout << "XBL = " << XBL << endl;
	cout << "XBR = " << XBR << endl;

	cout << "YBL = " << YBL << endl;
	cout << "YBR = " << YBR << endl;

	cout << "XBinMin = " << XBinMin << endl;
	cout << "XBinMax = " << XBinMax << endl;
	cout << "YBinMin = " << YBinMin << endl;
	cout << "YBinMax = " << YBinMax << endl;

	double MeanEnergy;
	TCanvas *c1 = new TCanvas("c1","c1",600,600);
	c1->cd();


	Inter->Draw("colz");
	Inter->SetMinimum(EminHis);
	Inter->SetMaximum(EmaxHis);
	Inter->Draw("colz");
	Inter->GetXaxis()->SetTitle("Horizontal Position (mm)");
	Inter->GetYaxis()->SetTitle("Vertical Position (mm)");

	TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());

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
		TitleName = "2018 sPHENIX Simulation (eta ~ 1)";
		}
	

	}

	if(year == 2017){
		if ( inputfile==0) TitleName = "2017 Data: Energy vs Horizontal and Vertical Positions After Interpolation - 0 Degree Tilted";
		if ( inputfile==1) TitleName = "Energy vs Horizontal and Vertical Positions After Interpolation - 10 Degree Tilted";
	}
	Inter->SetTitle(Form("E vs XY %s",TitleName.Data()));


	if(DrawLine == 1)
	{
		TLine *l1 = new TLine(XBL,YBL,XBR,YBL);

		l1->SetLineWidth(2);
		l1->Draw("same");

		TLine *l2 = new TLine(XBL,YBR,XBR,YBR);
		l2->SetLineWidth(2);
		l2->Draw("same");



		TLine *l3 = new TLine(XBL,YBL,XBL,YBR);
		l3->SetLineWidth(2);
		l3->Draw("same");

		TLine *l4 = new TLine(XBR,YBL,XBR,YBR);
		l4->SetLineWidth(2);
		l4->Draw("same");
	}
	c1->SaveAs(Form("Results/%d/%s/ProjectionRange.png",year,ordertag.Data()));



	const int YHisBins = YBinMax - YBinMin;
	const int XHisBins = XBinMax - XBinMin;

	//Projection on Region//

	TH1D * hProjX = new TH1D("hProjX","hProjX",YHisBins,YBL,YBR);
	TH1D * hProjY = new TH1D("hProjY","hProjY",XHisBins,XBL,XBR);
	hProjX->GetXaxis()->SetTitle("Horizontal Position (mm)");
	hProjX->GetYaxis()->SetTitle("Energy (GeV)");
	hProjX->SetTitle("Energy vs Horizontal Position");

	hProjY->GetXaxis()->SetTitle("Vertical Position (mm)");
	hProjY->GetYaxis()->SetTitle("Energy (GeV)");
	hProjY->SetTitle("Energy vs Vertical Position");

	Inter->ProjectionX("hProjX",YBinMin,YBinMax);

	Inter->ProjectionY("hProjY",XBinMin,XBinMax);
	TFile *fout = new TFile(RMSFile.Data(),"RECREATE");
	fout->cd();




	hProjX->Scale(1.0/(XHisBins+1));
	hProjY->Scale(1.0/(YHisBins+1));






	hProjX->SetMinimum(0);
	hProjY->SetMinimum(0);
	hProjX->GetXaxis()->SetRange(XBinMin,XBinMax);
	hProjY->GetXaxis()->SetRange(YBinMin,YBinMax);
	hProjX->Draw();



	c1->SaveAs(Form("Results/%d/ProjXHis-%s.png",year,ordertag.Data()));
	hProjY->Draw();
	c1->SaveAs(Form("Results/%d/ProjYHis-%s.png",year,ordertag.Data()));


	hProjX->Write();
	hProjY->Write();

	//Done Projection//

	if(sPHENIXStyle == 1){
		gROOT->LoadMacro("sPhenixStyle.C");
		SetsPhenixStyle();
	}

	for(int i = XBinMin; i < XBinMax; i++)
	{

		for(int j = YBinMin; j < YBinMax; j++)
		{
			MeanEnergy = Inter->GetBinContent(i,j);

			MEHis->Fill(MeanEnergy);


		}

	}
	MEHis->GetXaxis()->SetTitle("Mean Energy (GeV)");
	MEHis->GetYaxis()->SetTitle("Counts");

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

	}

	if(year == 2017){
		if ( inputfile==0) TitleName = "2017 Data: Energy vs Horizontal and Vertical Positions After Interpolation - 0 Degree Tilted";
		if ( inputfile==1) TitleName = "Energy vs Horizontal and Vertical Positions After Interpolation - 10 Degree Tilted";
	}

	MEHis->SetTitle(Form("Mean Energy Distribution for %s",TitleName.Data()));
	MEHis->Draw();
	TCanvas *c2 = new TCanvas("c2","c2",600,600);
	c2->cd();


	c2->SaveAs(Form("Results/%d/RMS-%s.png",year,TitleName.Data()));

	MEHis->Write();
	TF1 *f1 = new TF1("f1","gaus",FitEmin,FitEmax);
	MEHis->Fit(f1,"R");


	double GausMean = f1->GetParameter(1);
	double GausRMS = f1->GetParameter(2);

	//	if(inputfile ==0) GausMean = 4.95;


	MEHis->Draw();
	c2->Update();
	c2->SaveAs(Form("Results/CentralProj/%d%sRMSPlotGausFitted.png",year,ordertag.Data()));


	cout << "------ Gaussian Fits Method ------" << endl;

	cout << "Central 4 x 4 Towers Mean = " << GausMean << endl;
	cout << "Central 4 x 4 Towers RMS = " <<  GausRMS  << endl;
	cout << "Central 4 x 4 Towers RMS/Mean = " << GausRMS/GausMean << endl;

	cout << "------ Direct Get Mean and RMS Method ------" << endl;
	cout << "Central 4 x 4 Towers Mean = " << MEHis->GetMean() << endl;
	cout << "Central 4 x 4 Towers RMS = " << MEHis->GetRMS() << endl;
	cout << "Central 4 x 4 Towers RMS/Mean = " << MEHis->GetRMS()/MEHis->GetMean() << endl;

	ofstream fileout(Form("RMStext/RMS%d%s.dat",year,ordertag.Data()));
	fileout << "------ Gaussian Fits Method ------" << endl;

	fileout << "Central 4 x 4 Towers Mean = " << GausMean << endl;
	fileout << "Central 4 x 4 Towers RMS = " <<  GausRMS  << endl;
	fileout << "Central 4 x 4 Towers RMS/Mean = " << GausRMS/GausMean << endl;

	fileout << "------ Direct Get Mean and RMS Method ------" << endl;
	fileout << "Central 4 x 4 Towers Mean = " << MEHis->GetMean() << endl;
	fileout << "Central 4 x 4 Towers RMS = " << MEHis->GetRMS() << endl;
	fileout << "Central 4 x 4 Towers RMS/Mean = " << MEHis->GetRMS()/MEHis->GetMean() << endl;








	double MeanEnergyRe;
	TH1D * MEHisRe = new TH1D("MEHisRe","MEHisRe",EBins*BinRefine,Emin/GausMean,Emax/GausMean);
	for(int i = XBinMin; i < XBinMax; i++)
	{

		for(int j = YBinMin; j < YBinMax; j++)
		{
			MeanEnergyRe = Inter->GetBinContent(i,j)/GausMean;

			MEHisRe->Fill(MeanEnergyRe);


		}

	}

	MEHisRe->GetXaxis()->SetTitle("Rescaled Mean Energy (GeV)");
	MEHisRe->GetYaxis()->SetTitle("Counts");
	MEHisRe->SetTitle(Form("Rescaled Mean Energy Normalized Distribution for %d 10 Degree Tilted Scan",year));
	MEHisRe->Scale(1.0/MEHisRe->Integral());
	MEHisRe->Draw();
	c2->SaveAs(Form("Results/CentralProj/%d%sRMSPlotRescaled.png",year,ordertag.Data()));
	MEHisRe->Write();
	fout->Close();


}
