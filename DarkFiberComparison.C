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
//#include "Variable.h"
#include "parametersDark.h"
#include "parameters.h"

using namespace std;



using std::cout;
using std::endl;


void DarkFiberComparison()
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

	hProjXReData->GetXaxis()->SetTitle("X Axis (mm)");
	hProjXReData->GetYaxis()->SetTitle("Energy (GeV)");	
	hProjXReData->SetTitle("DarkFiber Comparison - 1 D Projection on X Axis (8 GeV Beam)");
	//	hProjXReData->SetMinimum(EminHis);
	//	hProjXReData->SetMaximum(EmaxHis);



	TCanvas *c = new TCanvas("c","c",600,600);
	c->cd();


	hProjXReData->Draw();
	c->SaveAs(Form("%s.png",DataPlotX.Data()));
	c->SaveAs(Form("%s.pdf",DataPlotX.Data()));
	hProjXReMC->Draw();
	c->SaveAs(Form("%s.png",MCPlotX.Data()));
	c->SaveAs(Form("%s.pdf",MCPlotX.Data()));


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
	l->AddEntry(hProjXReData,"Without Dark Fiber Effect");
	l->AddEntry(hProjXReMC,"With Dark Fiber Effect");
	l->Draw("SAME");

	c->SaveAs(Form("%s.png",DataMCPlotX.Data()));
	c->SaveAs(Form("%s.pdf",DataMCPlotX.Data()));

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



	hProjYReData->GetXaxis()->SetTitle("Y Axis (mm)");
	hProjYReData->GetYaxis()->SetTitle("Energy (GeV)");	
	hProjYReData->SetTitle("DarkFiber Comparison - 1 D Projection on Y Axis (8 GeV Beam)");

	hProjYReData->Draw();

	c->SaveAs(Form("%s.png",DataPlotY.Data()));
	c->SaveAs(Form("%s.pdf",DataPlotY.Data()));	
	hProjYReMC->Draw();
	c->SaveAs(Form("%s.png",MCPlotY.Data()));
	c->SaveAs(Form("%s.pdf",MCPlotY.Data()));


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
	l2->AddEntry(hProjYReData,"Without Dark Fiber Effect");
	l2->AddEntry(hProjYReMC,"With Dark Fiber Effect");
	l2->Draw("SAME");

	c->SaveAs(Form("%s.png",DataMCPlotY.Data()));
	c->SaveAs(Form("%s.pdf",DataMCPlotY.Data()));


	double XDataMean = double(hProjXReData->Integral(0,NBinX-1))/double(NBinX);
	double XMCMean = double(hProjXReMC->Integral(0,NBinX-1))/double(NBinX);
	double YDataMean = double(hProjYReData->Integral(0,NBinY-1))/double(NBinY);
	double YMCMean = double(hProjYReMC->Integral(0,NBinY-1))/double(NBinY);

	cout << "XDataMean = " << XDataMean << endl;
	cout << "XMCMean = " << XMCMean << endl;
	cout << "YDataMean = " << YDataMean << endl;
	cout << "YMCMean = " << YMCMean << endl;

	TCanvas *c2 = new TCanvas("c2","c2",600,600);
	c2->cd();

	hProjXReData->Scale(1.0/XDataMean);
	hProjXReMC->Scale(1.0/XMCMean);

	hProjXReData->SetMinimum(EMinNBoth);
	hProjXReData->SetMaximum(EMaxNBoth);
	hProjXReData->SetTitle("Normalized Data-MC Comparison - 1 D Projection on X Axis (8 GeV Beam)");
	hProjXReData->Draw("hist");
	hProjXReMC->Draw("histSAME");
	l->Draw("SAME");
	c2->SaveAs(Form("%s.png",DataMCPlotXNormalized.Data()));
	c2->SaveAs(Form("%s.pdf",DataMCPlotXNormalized.Data()));


	TCanvas *c3 = new TCanvas("c3","c3",600,600);
	c3->cd();



	hProjYReData->Scale(1.0/YDataMean);
	hProjYReMC->Scale(1.0/YMCMean);
	hProjYReData->SetMinimum(EMinNBoth);
	hProjYReData->SetMaximum(EMaxNBoth);
	hProjYReData->SetTitle("Normalized Data-MC Comparison - 1 D Projection on Y Axis (8 GeV Beam)");
	hProjYReData->Draw("hist");
	hProjYReMC->Draw("histSAME");
	l2->Draw("SAME");
	c3->SaveAs(Form("%s.png",DataMCPlotYNormalized.Data()));
	c3->SaveAs(Form("%s.pdf",DataMCPlotYNormalized.Data()));

	TCanvas *c4 = new TCanvas("c4","c4",600,600);
	c4->cd();


	hProjXReData->Divide(hProjXReMC);
	hProjXReData->SetTitle("Normalized Data to MC Ratio of 1 D Projection on X Axis (8 GeV Beam)");
	hProjXReData->Draw("hist");
	c4->SaveAs(Form("%s.png",DataMCPlotXRatio.Data()));
	c4->SaveAs(Form("%s.pdf",DataMCPlotXRatio.Data()));


	TCanvas *c5 = new TCanvas("c5","c5",600,600);
	c5->cd();

	hProjYReData->Divide(hProjYReMC);
	hProjYReData->SetTitle("Normalized Data to MC Ratio of 1 D Projection on Y Axis (8 GeV Beam)");
	hProjYReData->Draw("hist");
	c5->SaveAs(Form("%s.png",DataMCPlotYRatio.Data()));
	c5->SaveAs(Form("%s.pdf",DataMCPlotYRatio.Data()));

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
