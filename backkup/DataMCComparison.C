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
#include "Variable.h"
#include "parametersComp.h"
#include "parameters.h"

using namespace std;



using std::cout;
using std::endl;
#endif

void DataMCComparison()
{



	gSystem->Load("libg4eval.so");
	gSystem->Load("libqa_modules.so");
	gSystem->Load("libPrototype3.so");
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	finData->cd();
	finMC->cd();

	TH1D *hProjXData = (TH1D *) finData->Get("hProjX");
	TH1D *hProjYData = (TH1D *) finData->Get("hProjY");
	TH1D *hProjXMC = (TH1D *) finMC->Get("hProjX");
	TH1D *hProjYMC = (TH1D *) finMC->Get("hProjY");

	TH1D * hProjXReData = new TH1D("DataReScaleX","DataReScaleX",NBinX,0,MaxBinX);
	TH1D * hProjYReData = new TH1D("DataReScaleY","DataReScaleY",NBinY,0,MaxBinY);

	TH1D * hProjXReMC = new TH1D("MCReScaleX","MCReScaleX",NBinX,0,MaxBinX);
	TH1D * hProjYReMC = new TH1D("MCReScaleY","MCReScaleY",NBinY,0,MaxBinY);


	double EnergyXData;
	double EnergyXMC;
	double EnergyYData;
	double EnergyYMC;
	int XData;
	int XMC;
	int XBinData;
	int XBinMC;

	for(int i = 0; i < NBinX; i++){

		XData = MinDataY + i * sizeX;
		XBinData = hProjXData->GetXaxis()->FindBin(XData);
		EnergyXData = hProjXData->GetBinContent(XBinData);
		hProjXReData->SetBinContent(i,EnergyXData);

	}

	for(int i = 0; i < NBinX; i++){
		XMC = MinMCY + i * sizeX;
		XBinMC = hProjXMC->GetXaxis()->FindBin(XMC);
		EnergyXMC = hProjXMC->GetBinContent(XBinMC);
		hProjXReMC->SetBinContent(i,EnergyXMC);
	}

	hProjXReData->GetXaxis()->SetTitle("Rescale X Axis (mm)");
	hProjXReData->GetYaxis()->SetTitle("Energy (GeV)");	
	hProjXReData->SetTitle("Data-MC Comparison - 1 D Projection on X Axis (8 GeV Beam)");
	//	hProjXReData->SetMinimum(EminHis);
	//	hProjXReData->SetMaximum(EmaxHis);



	TCanvas *c = new TCanvas("c","c",600,600);
	c->cd();


	hProjXReData->Draw();
	c->SaveAs(DataPlotX.Data());
	hProjXReMC->Draw();
	c->SaveAs(MCPlotX.Data());


	hProjXReData->SetLineColor(kBlue);
	hProjXReData->SetLineWidth(2);	
	hProjXReMC->SetLineColor(kRed);
	hProjXReMC->SetLineWidth(2);		

	hProjXReData->SetMinimum(EMinBoth);
	hProjXReData->SetMaximum(EMaxBoth);
	hProjXReData->Draw();
	hProjXReMC->Draw("SAME");

	TLegend * l = new TLegend(0.30,0.71,0.47,0.91,NULL,"brNDC");
	l->SetBorderSize(0);
	l->SetTextSize(0.04);
	l->SetTextFont(42);
	l->SetFillStyle(0);
	l->AddEntry(hProjXReData,"1D projection X Data Rescaled");
	l->AddEntry(hProjXReMC,"1D projection X MC Rescaled");
	l->Draw("SAME");

	c->SaveAs(DataMCPlotX.Data());

	int YData;
	int YMC;
	int YBinData;
	int YBinMC;


	for(int i = 0; i < NBinY; i++){

		YData = MinDataX + i * sizeY;
		YBinData = hProjYData->GetXaxis()->FindBin(YData);
		EnergyYData = hProjYData->GetBinContent(YBinData);
		hProjYReData->SetBinContent(i,EnergyYData);

	}

	for(int i = 0; i < NBinY; i++){
		YMC = MinMCX + i * sizeY;
		YBinMC = hProjYMC->GetXaxis()->FindBin(YMC);
		EnergyYMC = hProjYMC->GetBinContent(YBinMC);
		hProjYReMC->SetBinContent(i,EnergyYMC);
	}



	hProjYReData->GetXaxis()->SetTitle("Rescale Y Axis (mm)");
	hProjYReData->GetYaxis()->SetTitle("Energy (GeV)");	
	hProjYReData->SetTitle("Data-MC Comparison - 1 D Projection on Y Axis (8 GeV Beam)");

	hProjYReData->Draw();
	c->SaveAs(DataPlotY.Data());
	hProjYReMC->Draw();
	c->SaveAs(MCPlotY.Data());


	hProjYReData->SetLineColor(kBlue);
	hProjYReData->SetLineWidth(2);	
	hProjYReMC->SetLineColor(kRed);
	hProjYReMC->SetLineWidth(2);		

	hProjYReData->Draw();
	hProjYReData->SetMinimum(EMinBoth);
	hProjYReData->SetMaximum(EMaxBoth);

	hProjYReMC->Draw("SAME");

	TLegend * l2 = new TLegend(0.30,0.68,0.47,0.88,NULL,"brNDC");
	l2->SetBorderSize(0);
	l2->SetTextSize(0.04);
	l2->SetTextFont(42);
	l2->SetFillStyle(0);
	l2->AddEntry(hProjYReData,"1D projection Y Data Rescaled");
	l2->AddEntry(hProjYReMC,"1D projection Y MC Rescaled");
	l2->Draw("SAME");

	c->SaveAs(DataMCPlotY.Data());

	double XDataMean = double(hProjXReData->Integral(0,NBinX-1))/double(NBinX);
	double XMCMean = double(hProjXReMC->Integral(0,NBinX-1))/double(NBinX);
	double YDataMean = double(hProjYReData->Integral(0,NBinY-1))/double(NBinY);
	double YMCMean = double(hProjYReMC->Integral(0,NBinY-1))/double(NBinY);

	cout << "XDataMean = " << XDataMean << endl;
	cout << "XMCMean = " << XMCMean << endl;
	cout << "YDataMean = " << YDataMean << endl;
	cout << "YMCMean = " << YMCMean << endl;

	hProjXReData->Scale(1.0/XDataMean);
	hProjXReMC->Scale(1.0/XMCMean);

	hProjXReData->SetMinimum(EMinNBoth);
	hProjXReData->SetMaximum(EMaxNBoth);
	hProjXReData->SetTitle("Normalized Data-MC Comparison - 1 D Projection on X Axis (8 GeV Beam)");
	hProjXReData->Draw();
	hProjXReMC->Draw("SAME");
	l->Draw("SAME");
	c->SaveAs(DataMCPlotXNormalized.Data());


	hProjYReData->Scale(1.0/YDataMean);
	hProjYReMC->Scale(1.0/YMCMean);
	hProjYReData->SetMinimum(EMinNBoth);
	hProjYReData->SetMaximum(EMaxNBoth);
	hProjYReData->SetTitle("Normalized Data-MC Comparison - 1 D Projection on Y Axis (8 GeV Beam)");
	hProjYReData->Draw();
	hProjYReMC->Draw("SAME");
	l2->Draw("SAME");
	c->SaveAs(DataMCPlotYNormalized.Data());


	hProjXReData->Divide(hProjXReMC);
	hProjXReData->SetTitle("Normalized Data to MC Ratio of 1 D Projection on X Axis (8 GeV Beam)");
	hProjXReData->Draw();
	c->SaveAs(DataMCPlotXRatio.Data());


	hProjYReData->Divide(hProjYReMC);
	hProjYReData->SetTitle("Normalized Data to MC Ratio of 1 D Projection on Y Axis (8 GeV Beam)");
	hProjYReData->Draw();
	c->SaveAs(DataMCPlotYRatio.Data());

	cout << "X Agreement = " << hProjXReData->GetRMS()/NBinX << endl;
	cout << "Y Agreement = " << hProjYReData->GetRMS()/NBinY << endl;
	
	double NRatioX;
	double AgreementX;
	double TotalDivX = 0;

	double NRatioY;
	double AgreementY;
	double TotalDivY = 0;


	for(int i = 0; i < NBinX; i++){
		NRatioX = hProjXReData->GetBinContent(i);
		TotalDivX = abs(NRatioX - 1) + TotalDivX;
	}

	for(int i = 0; i < NBinY; i++){
		NRatioY = hProjYReData->GetBinContent(i);
		TotalDivY = abs(NRatioY - 1) + TotalDivY;

	}

	AgreementX = TotalDivX/NBinX;
	AgreementY = TotalDivY/NBinY;
	
	cout << "Data MC Agreement X = " << AgreementX << endl;
	cout << "Data MC Agreement Y = " << AgreementY << endl;




}
