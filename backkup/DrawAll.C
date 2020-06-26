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
//#include "parameters.h"
using namespace std;



using std::cout;
using std::endl;
#endif

void DrawAll()
{
	int DrawMode = 1;

	//gROOT->LoadMacro("sPhenixStyle.C");
	//SetsPhenixStyle();


	TFile *fin1;
	TFile *fin2;
	TFile *fin3;
	TFile *fin4;
	TFile *fin5;
if(DrawMode==1){
	fin1 = new TFile("ROOTFiles/20172ndRMS.root");
	fin2 = new TFile("ROOTFiles/20173rdRMS.root");
	fin3 = new TFile("ROOTFiles/20183rdRMS.root");
	fin4 = new TFile("ROOTFiles/20184thRMS.root");
	}


if(DrawMode==0){
	fin1 = new TFile("ROOTFiles/20172ndRMS.root");
	fin2 = new TFile("ROOTFiles/20173rdRMS.root");
	fin3 = new TFile("ROOTFiles/20185thRMS.root");
	fin4 = new TFile("ROOTFiles/20186thRMS.root");
	fin5 = new TFile("ROOTFiles/20187thRMS.root");

	}

	TH1D * h1 = (TH1D *) fin1->Get("MEHisRe");
	TH1D * h2 = (TH1D *) fin2->Get("MEHisRe");
	TH1D * h3 = (TH1D *) fin3->Get("MEHisRe");
	TH1D * h4 = (TH1D *) fin4->Get("MEHisRe");
if(DrawMode==0) 	TH1D * h5 = (TH1D *) fin5->Get("MEHisRe");

	h1->Rebin(2);
	h2->Rebin(2);
	h3->Rebin(2);
	h4->Rebin(2);
if(DrawMode==0) 	h5->Rebin(2);

	TCanvas  * c = new TCanvas("c","c",1200,1200);
	c->cd();
	h3->SetTitle("2018 and 2018 Position Scan Rescaled Mean Energy Distribution Comparison Plot");
	h3->GetXaxis()->SetTitle("Rescaled Mean Energy");
	h3->GetYaxis()->SetTitle("Probability/Bin");
	h3->GetYaxis()->SetTitleOffset(1.4);
	h3->SetMaximum(0.45);
	h3->SetLineColor(kBlue);
	h3->SetLineWidth(4.5);
	h3->Draw();
	h1->SetLineColor(kRed);
	h1->SetLineWidth(4.5);
	h1->Draw("SAME");
	h2->SetLineColor(kPink-1);
	h2->SetLineWidth(9);
	h2->SetLineStyle(2);
	h2->Draw("SAME");
	h4->SetLineColor(kCyan+3);
	h4->SetLineWidth(9);
	h4->SetLineStyle(2);
	h4->Draw("SAME");
if(DrawMode==0) {

	h5->SetLineColor(kGreen);
	h5->SetLineWidth(9);
	h5->SetLineStyle(2);
	h5->Draw("SAME");

}

	TLegend * l = new TLegend(0.15,0.62,0.85,0.83);
	if(DrawMode == 1)
	{
	l->AddEntry(h1,"2017 2nd 10 Degree Tilted Scan - RMS/Mean = 0.0749","l");
	l->AddEntry(h2,"2017 3rd 0 Degree Tilted Scan - RMS/Mean = 0.0905","l");
	l->AddEntry(h3,"2018 3rd Dual Channeling Scan - RMS/Mean = 0.0847","l");
	l->AddEntry(h4,"2018 4th sPHENIX Rotation Scan - RMS/Mean = 0.0700","l");

	}
	if(DrawMode == 0)
	{
	l->AddEntry(h1,"2017 2nd 10 Degree Tilted Scan - RMS/Mean = 0.0749","l");
	l->AddEntry(h2,"2017 3rd 0 Degree Tilted Scan - RMS/Mean = 0.0905","l");
	l->AddEntry(h3,"2018 5rd Dual Channeling Scan - RMS/Mean = 0.819","l");
	l->AddEntry(h4,"2018 6th sPHENIX + 5 Scan - RMS/Mean = 0.0682","l");
	l->AddEntry(h5,"2017 7th sPHENIX Rotation Scan - RMS/Mean = 0.787","l");
	}

	l->Draw("SAME");

	c->SaveAs(Form("AllComparison/AllComparison%d.png",DrawMode));
	TFile *fout = new TFile(Form("AllComparison%d.root",DrawMode),"RECREATE");
	fout->cd();
	h1->Write();
	h2->Write();
	h3->Write();
	h4->Write();
	if(DrawMode == 0) h5->Write();
	fout->Close();
}

