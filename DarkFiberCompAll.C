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
#include "parametersComp.h"
#include "parameters.h"

using namespace std;



using std::cout;
using std::endl;


void DarkFiberCompAll()
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


	TFile * finDarkAll = new TFile("ROOTFiles/2018Simulations-10Deg-DeadFiberRMS.root");
	finDarkAll->cd();
	

	TH1D *hProjXDarkAll = (TH1D *) finDarkAll->Get("hProjX");
	TH1D *hProjYDarkAll = (TH1D *) finDarkAll->Get("hProjY");

	TH1D * hProjXReDarkAll = new TH1D("DFAllReScaleX","DFAllReScaleX",NBinX,0,MaxBinX);
	TH1D * hProjYReDarkAll = new TH1D("DFAllReScaleY","DFAllReScaleY",NBinY,0,MaxBinY);

	for(int i = 0; i < NBinX; i++){
		XMC = MinMCY + i * sizeX;
		XBinMC = hProjXDarkAll->GetXaxis()->FindBin(XMC);
		EnergyXMC = hProjXDarkAll->GetBinContent(XBinMC);
		hProjXReDarkAll->SetBinContent(i,EnergyXMC);
	}

	//TFile * finDarkPart = new TFile("ROOTFiles/2018Dark-Fiber-Randomly-DistributedRMS.root");
//	TFile * finDarkPart = new TFile("ROOTFiles/2018DarkFiber-Modified-RandomRMS.root");
	TFile * finDarkPart = new TFile("ROOTFiles/2018DarkFiber-Craig-ConfigRMS.root"); 

	finDarkPart->cd();


	TH1D *hProjXDarkPart = (TH1D *) finDarkPart->Get("hProjX");
	TH1D *hProjYDarkPart = (TH1D *) finDarkPart->Get("hProjY");

	TH1D * hProjXReDarkPart = new TH1D("DFPartReScaleX","DFPartReScaleX",NBinX,0,MaxBinX);
	TH1D * hProjYReDarkPart = new TH1D("DFPartReScaleY","DFPartReScaleY",NBinY,0,MaxBinY);



	for(int i = 0; i < NBinX; i++){
		XMC = MinMCY + i * sizeX;
		XBinMC = hProjXDarkPart->GetXaxis()->FindBin(XMC);
		EnergyXMC = hProjXDarkPart->GetBinContent(XBinMC);
		hProjXReDarkPart->SetBinContent(i,EnergyXMC);
	}





	TCanvas *c = new TCanvas("c","c",600,600);
	c->cd();




	hProjXReData->SetLineColor(kBlack);
	hProjXReData->SetLineWidth(2);	
	hProjXReMC->SetLineColor(kRed);
	hProjXReMC->SetLineWidth(2);		
	hProjXReDarkAll->SetLineColor(kBlue);
	hProjXReDarkAll->SetLineWidth(2);	
	hProjXReDarkPart->SetLineColor(kGreen);
	hProjXReDarkPart->SetLineWidth(2);	

	hProjXReData->SetMinimum(EMinBoth);
	hProjXReData->SetMaximum(EMaxBoth);
	
	


	hProjXReData->Draw("hist");
	hProjXReMC->Draw("histSAME");
	hProjXReDarkAll->Draw("histSAME");
	hProjXReDarkPart->Draw("histSAME");



	TLegend * l = new TLegend(0.20,0.71,0.37,0.88,NULL,"brNDC");
	l->SetBorderSize(0);
	l->SetTextSize(0.04);
	l->SetTextFont(42);
	l->SetFillStyle(0);
	l->AddEntry(hProjXReData,"Test Beam Data");
	l->AddEntry(hProjXReMC,"MC Without Dark Fiber");
	l->AddEntry(hProjXReDarkAll,"Dark Filer All Masked");
	l->AddEntry(hProjXReDarkPart,"Dark Fiber 50% Masked Randomly Distributed");

	l->Draw("SAME");


	c->SaveAs("PlotDarkCompAll/AllCompX.png");
	c->SaveAs("PlotDarkCompAll/AllCompX.pdf");


	//Nornalized//

	double XDataMean = double(hProjXReData->Integral(0,NBinX-1))/double(NBinX);
	double XMCMean = double(hProjXReMC->Integral(0,NBinX-1))/double(NBinX);
	double DFAllXMean = double(hProjXReDarkAll->Integral(0,NBinX-1))/double(NBinX);
	double DFPartXMean = double(hProjXReDarkPart->Integral(0,NBinX-1))/double(NBinX);

	


	hProjXReData->Scale(1.0/XDataMean);
	hProjXReMC->Scale(1.0/XMCMean);
	hProjXReDarkAll->Scale(1.0/DFAllXMean);
	hProjXReDarkPart->Scale(1.0/DFPartXMean);

	hProjXReData->SetMaximum(1.4);
	hProjXReData->SetMinimum(0.6);

	hProjXReData->Draw("hist");
	hProjXReMC->Draw("histSAME");
	hProjXReDarkAll->Draw("histSAME");
	hProjXReDarkPart->Draw("histSAME");


	l->Draw("SAME");


	c->SaveAs("PlotDarkCompAll/AllCompNormX.png");
	c->SaveAs("PlotDarkCompAll/AllCompNormX.pdf");


	//DONE Normalized//



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


	for(int i = 0; i < NBinY; i++){
		YMC = MinMCX + i * sizeY;
		YBinMC = hProjYDarkAll->GetXaxis()->FindBin(YMC);
		EnergyYMC = hProjYDarkAll->GetBinContent(YBinMC);
		hProjYReDarkAll->SetBinContent(i,EnergyYMC);
	}

	for(int i = 0; i < NBinY; i++){
		YMC = MinMCX + i * sizeY;
		YBinMC = hProjYDarkPart->GetXaxis()->FindBin(YMC);
		EnergyYMC = hProjYDarkPart->GetBinContent(YBinMC);
		hProjYReDarkPart->SetBinContent(i,EnergyYMC);
	}





	hProjYReData->GetXaxis()->SetTitle("Rescale Y Axis (mm)");
	hProjYReData->GetYaxis()->SetTitle("Energy (GeV)");	
	hProjYReData->SetTitle("Data-MC Comparison - 1 D Projection on Y Axis (8 GeV Beam)");

	hProjYReData->SetMinimum(EMinBoth);
	hProjYReData->SetMaximum(EMaxBoth);


	hProjYReData->SetLineColor(kBlack);
	hProjYReData->SetLineWidth(2);	
	hProjYReMC->SetLineColor(kRed);
	hProjYReMC->SetLineWidth(2);		
	hProjYReDarkAll->SetLineColor(kBlue);
	hProjYReDarkAll->SetLineWidth(2);	
	hProjYReDarkPart->SetLineColor(kGreen);
	hProjYReDarkPart->SetLineWidth(2);	



	hProjYReData->Draw("hist");
	hProjYReMC->Draw("histSAME");
	hProjYReDarkAll->Draw("histSAME");
	hProjYReDarkPart->Draw("histSAME");


	TLegend * l2 = new TLegend(0.20,0.68,0.37,0.88,NULL,"brNDC");
	l2->SetBorderSize(0);
	l2->SetTextSize(0.04);
	l2->SetTextFont(42);
	l2->SetFillStyle(0);
	l2->AddEntry(hProjYReData,"Test Beam Data");
	l2->AddEntry(hProjYReMC,"MC Without Dark Fiber");
	l2->AddEntry(hProjYReDarkAll,"Dark Fiber All Masked");
	l2->AddEntry(hProjYReDarkPart,"Dark Fiber 50% Masked Randomly Distributed");

	l2->Draw("SAME");

	c->SaveAs("PlotDarkCompAll/AllCompY.png");
	c->SaveAs("PlotDarkCompAll/AllCompY.pdf");

	//Normalized//
	
	double YDataMean = double(hProjYReData->Integral(0,NBinY-1))/double(NBinY);
	double YMCMean = double(hProjYReMC->Integral(0,NBinY-1))/double(NBinY);
	double DFAllYMean = double(hProjYReDarkAll->Integral(0,NBinY-1))/double(NBinY);
	double DFPartYMean = double(hProjYReDarkPart->Integral(0,NBinY-1))/double(NBinY);

	


	hProjYReData->Scale(1.0/YDataMean);
	hProjYReMC->Scale(1.0/YMCMean);
	hProjYReDarkAll->Scale(1.0/DFAllYMean);
	hProjYReDarkPart->Scale(1.0/DFPartYMean);

	hProjYReData->SetMaximum(1.4);
	hProjYReData->SetMinimum(0.6);

	hProjYReData->Draw("hist");
	hProjYReMC->Draw("histSAME");
	hProjYReDarkAll->Draw("histSAME");
	hProjYReDarkPart->Draw("histSAME");

	l2->Draw("SAME");

	c->SaveAs("PlotDarkCompAll/AllCompNormY.png");
	c->SaveAs("PlotDarkCompAll/AllCompNormY.pdf");



	//Done Normalize//




	TFile * RMS10DegData = new TFile("ROOTFiles/20186thRMS.root"); 
	TFile * RMS10DegMC = new TFile("ROOTFiles/2018Simulations-10DegreeRMS.root"); 
	TFile * RMS10DegDFAll = new TFile("ROOTFiles/2018Simulations-10Deg-DeadFiberRMS.root"); 
//	TFile * RMS10DegDFPart = new TFile("ROOTFiles/2018Dark-Fiber-Randomly-DistributedRMS.root"); 
	TFile * RMS10DegDFPart = new TFile("ROOTFiles/2018DarkFiber-Craig-ConfigRMS.root"); 



	TH1D * DataEnergy = (TH1D * ) RMS10DegData->Get("MEHis");
	TH1D * MCEnergy = (TH1D * ) RMS10DegMC->Get("MEHis");
	TH1D * DFAllEnergy = (TH1D * ) RMS10DegDFAll->Get("MEHis");
	TH1D * DFPartEnergy = (TH1D * ) RMS10DegDFPart->Get("MEHis");


	DataEnergy->Scale(1.0/DataEnergy->Integral());
	MCEnergy->Scale(1.0/MCEnergy->Integral());
	DFAllEnergy->Scale(1.0/DFAllEnergy->Integral());
	DFPartEnergy->Scale(1.0/DFPartEnergy->Integral());
		
	DataEnergy->SetLineColor(kBlack);
	DataEnergy->SetLineWidth(2);
	MCEnergy->SetLineColor(kRed);
	MCEnergy->SetLineWidth(2);
	DFAllEnergy->SetLineColor(kBlue);
	DFAllEnergy->SetLineWidth(2);
	DFPartEnergy->SetLineColor(kGreen);
	DFPartEnergy->SetLineWidth(2);

	MCEnergy->Draw("hist");
	DataEnergy->Draw("histSAME");
	DFAllEnergy->Draw("histSAME");
	DFPartEnergy->Draw("histSAME");

	TLegend * l3 = new TLegend(0.15,0.68,0.30,0.88,NULL,"brNDC");
	l3->SetBorderSize(0);
	l3->SetTextSize(0.04);
	l3->SetTextFont(42);
	l3->SetFillStyle(0);
	l3->AddEntry(hProjYReData,"Test Beam Data");
	l3->AddEntry(hProjYReMC,"MC Without Dark Fiber");
	l3->AddEntry(hProjYReDarkAll,"Dark Fiber All Masked");
	l3->AddEntry(hProjYReDarkPart,"Dark Fiber 50% Masked Randomly Distributed");

	l3->Draw("SAME");


	c->SaveAs("PlotDarkCompAll/EnergyDis.png");
	c->SaveAs("PlotDarkCompAll/EnergyDis.pdf");







	TFile * finMC1D = new TFile("ROOTFiles/2018/ProjectionSimulations-10Degree.root");

	TFile * finMCDFAll = new TFile("ROOTFiles/2018/ProjectionSimulations-10Deg-DeadFiber.root");


//	TFile * finMCDFPart = new TFile("ROOTFiles/2018/ProjectionDark-Fiber-Randomly-Distributed.root");

//	TFile * finMCDFPart = new TFile("ROOTFiles/2018/ProjectionDarkFiber-Modified-Random.root");

	TFile * finMCDFPart = new TFile("ROOTFiles/2018/ProjectionDarkFiber-Craig-Config.root");

	const int NPlots = 13;
	
	TCanvas * cNew = new TCanvas("cNew","cNew",600,600);
	cNew->cd();
	TLegend * lX[NPlots]; 
	TLegend * lY[NPlots];

	for(int i = 0; i < NPlots; i++){

		TH1D * ProjXHisMC = (TH1D * ) finMC1D->Get(Form("ProjXHis%d",i));
		TH1D * ProjXHisDFAll = (TH1D * ) finMCDFAll->Get(Form("ProjXHis%d",i));
		TH1D * ProjXHisDFPart = (TH1D * ) finMCDFPart->Get(Form("ProjXHis%d",i));

		ProjXHisMC->SetLineColor(kRed);
		ProjXHisMC->SetLineWidth(2);
		ProjXHisDFAll->SetLineColor(kBlue);
		ProjXHisDFAll->SetLineWidth(2);
		ProjXHisDFPart->SetLineColor(kGreen);
		ProjXHisDFPart->SetLineWidth(2);
	
	
		ProjXHisMC->Draw("hist");
		ProjXHisDFAll->Draw("histSAME");
		ProjXHisDFPart->Draw("histSAME");
	

		lX[i] = new TLegend(0.10,0.18,0.27,0.38,NULL,"brNDC");


		lX[i]->SetBorderSize(0);
		lX[i]->SetTextSize(0.04);
		lX[i]->SetTextFont(42);
		lX[i]->SetFillStyle(0);
		lX[i]->AddEntry(ProjXHisMC,"MC Without Dark Fiber");
		lX[i]->AddEntry(ProjXHisDFAll,"Dark Fiber All Masked");
		lX[i]->AddEntry(ProjXHisDFPart,"Dark Fiber 50% Masked Randomly Distributed");
		lX[i]->Draw("SAME");

		cNew->SaveAs(Form("PlotDarkCompAll/New/ProjXHis%d.png",i));
	}


	for(int i = 0; i < NPlots; i++){

		TH1D * ProjYHisMC = (TH1D * ) finMC1D->Get(Form("ProjYHis%d",i));
		TH1D * ProjYHisDFAll = (TH1D * ) finMCDFAll->Get(Form("ProjYHis%d",i));
		TH1D * ProjYHisDFPart = (TH1D * ) finMCDFPart->Get(Form("ProjYHis%d",i));
	
		ProjYHisMC->SetLineColor(kRed);
		ProjYHisMC->SetLineWidth(2);
		ProjYHisDFAll->SetLineColor(kBlue);
		ProjYHisDFAll->SetLineWidth(2);
		ProjYHisDFPart->SetLineColor(kGreen);
		ProjYHisDFPart->SetLineWidth(2);
	
		
		ProjYHisMC->Draw("hist");
		ProjYHisDFAll->Draw("histSAME");
		ProjYHisDFPart->Draw("histSAME");


		lY[i] = new TLegend(0.10,0.18,0.27,0.38,NULL,"brNDC");


		lY[i]->SetBorderSize(0);
		lY[i]->SetTextSize(0.04);
		lY[i]->SetTextFont(42);
		lY[i]->SetFillStyle(0);
		lY[i]->AddEntry(ProjYHisMC,"MC Without Dark Fiber");
		lY[i]->AddEntry(ProjYHisDFAll,"Dark Fiber All Masked");
		lY[i]->AddEntry(ProjYHisDFPart,"Dark Fiber 50% Masked Randomly Distributed");
		lY[i]->Draw("SAME");

		cNew->SaveAs(Form("PlotDarkCompAll/New/ProjYHis%d.png",i));
	}




	//ProjXHis4MC->SetMinimum(0.0);
	//ProjXHis4MC->SetMaximum(1.1);

	//X Aixs//




}
