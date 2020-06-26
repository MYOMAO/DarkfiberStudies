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
//#include "Variable.h"

using namespace std;



using std::cout;
using std::endl;


void Projection2018()
{

	gSystem->Load("libg4eval.so");
	gSystem->Load("libqa_modules.so");
	gSystem->Load("libPrototype3.so");
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gStyle->SetPalette(55);
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
		if ( inputfile==2) Typetag = "G4Simulations-10-Degrees";
		if ( inputfile==1) 	Typetag = "G4Simulations-5-Degrees";
		if ( inputfile==0) Typetag = "G4Simulations-0-Dergee";

	}
	TH2D * InterNew;
	TLatex* texCol;
	TH1D * ProjXHis;
	TH1D * ProjYHis;

	TString OutPlotName;
	OutPlotName = Form("Results/%s_%s_%s_%s.png",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());
	TString TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());


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

	if(dointer == 1 || year == 2017)
	{
		TFile * fin = new TFile(InterpolatedFile.Data());
		TH2D * Inter = (TH2D *) fin->Get("Inter");
	}
	if(dointer == 0){
		TFile * fin = new TFile(OutFileReadHis2.Data());
		InterNew = (TH2D *) fin->Get("EnPo");
		InterNew->SetMinimum(EminHis);
		InterNew->SetMaximum(EmaxHis);
	}

	int XBinMin = InterNew->GetXaxis()->FindBin(Xmin);
	int XBinMax = InterNew->GetXaxis()->FindBin(Xmax);

	int YBinMin = InterNew->GetYaxis()->FindBin(Ymin);
	int YBinMax = InterNew->GetYaxis()->FindBin(Ymax);

	cout << "Inter Counts = " << InterNew->Integral() << endl;

	TH2D * Inter = new TH2D("Inter","Inter",XBins, Xmin,Xmax,YBins,Ymin,Ymax);
	Inter->GetXaxis()->SetTitle("Horiztontal Position (mm)");
	Inter->GetYaxis()->SetTitle("Vertical Postion (mm)");
	Inter->SetTitle(Form("Energy vs XY Position %s",TitleName.Data()));
	Inter->SetMinimum(EminHis);
	Inter->SetMaximum(EmaxHis);

	TCanvas *c22 = new TCanvas("c22", "c22",0,0,800,600);
	c22->cd();
	if(Reverse ==1){
		for(int i = XBinMin; i < XBinMax; i++)
		{
			int iNow = XBinMax - i;
			for(int j = YBinMin; j<YBinMax; j++)
			{

				int jNow = YBinMax - j;

				double EnergyV = InterNew->GetBinContent(iNow,jNow);
				cout << "iNow = " << iNow << "  Energy Value = " << EnergyV << endl;
				Inter->SetBinContent(i,j,EnergyV);
			}
		}
	}
	TFile *fout = new TFile(ProjectionFile.Data(),"RECREATE");
	fout->cd();
	Inter->Write();


	Inter->GetXaxis()->SetTitleOffset(1.4);
	Inter->Draw("colz");


	// Horizontal line Tower 6 //
	TLine *l1 = new TLine(Xmin,Y1,Xmax,Y1);
	l1->SetLineWidth(1);
	l1->Draw("same");


	texCol= new TLatex(Xmin,Y1,"Row 1");
	texCol->SetTextAlign(11);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();


	// Horizontal line Tower 5 //


	TLine *l2 = new TLine(Xmin,Y2,Xmax,Y2);
	l2->SetLineWidth(1);
	l2->Draw("same");



	texCol= new TLatex(Xmin,Y2,"Row 2");
	texCol->SetTextAlign(11);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();

	// Horizontal line Tower 4//


	TLine *l3 = new TLine(Xmin,Y3,Xmax,Y3);
	l3->SetLineWidth(1);
	l3->Draw("same");



	texCol= new TLatex(Xmin,Y3,"Row 3");
	texCol->SetTextAlign(11);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();



	// Horizontal line Tower 3 //


	TLine *l4 = new TLine(Xmin,Y4,Xmax,Y4);
	l4->SetLineWidth(1);
	l4->Draw("same");



	texCol= new TLatex(Xmin,Y4,"Row 4");
	texCol->SetTextAlign(11);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();

	// Horizontal line Tower 2 //


	TLine *l5 = new TLine(Xmin,Y5,Xmax,Y5);
	l5->SetLineWidth(1);
	l5->Draw("same");




	texCol= new TLatex(Xmin,Y5,"Row 5");
	texCol->SetTextAlign(11);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();


	// Horizontal line Tower 1 //
	if(year == 2018){
		TLine *l12 = new TLine(Xmin,Y6,Xmax,Y6);
		l12->SetLineWidth(1);
		l12->Draw("same");



		texCol= new TLatex(Xmin,Y6,"Row 6");
		texCol->SetTextAlign(11);
		texCol->SetTextSize(0.03);
		texCol->SetTextFont(42);
		texCol->Draw();
	}
	/*
	   TLine *l13 = new TLine(Xmin,y7,Xmax,y7);
	   l13->SetLineWidth(1);
	   l13->Draw("same");


	   TLatex* texCol;
	   texCol= new TLatex(Xmin,y6,"Row 7");
	   texCol->SetTextAlign(11);
	   texCol->SetTextSize(0.03);
	   texCol->SetTextFont(42);
	   texCol->Draw();
	   */

	// Vertical line Tower 6 //


	TLine *l14 = new TLine(x1,Ymin,x1,Ymax);
	l14->SetLineWidth(1);
	l14->Draw("same");


	texCol= new TLatex(x1,Ymax,"Column 1");
	texCol->SetTextAlign(33);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();



	TLine *l6 = new TLine(x2,Ymin,x2,Ymax);
	l6->SetLineWidth(1);
	l6->Draw("same");


	texCol= new TLatex(x2,Ymax,"Column 2");
	texCol->SetTextAlign(33);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();


	// Horizontal line Tower 5 //


	TLine *l7 = new TLine(x3,Ymin,x3,Ymax);
	l7->SetLineWidth(1);
	l7->Draw("same");

	texCol= new TLatex(x3,Ymax,"Column 3");
	texCol->SetTextAlign(33);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();

	// Horizontal line Tower 4//


	TLine *l8 = new TLine(x4,Ymin,x4,Ymax);
	l8->SetLineWidth(1);
	l8->Draw("same");


	texCol= new TLatex(x4,Ymax,"Column 4");
	texCol->SetTextAlign(33);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();


	// Horizontal line Tower 3 //

	TLine *l9 = new TLine(x5,Ymin,x5,Ymax);
	l9->SetLineWidth(1);
	l9->Draw("same");


	texCol= new TLatex(x5,Ymax,"Column 5");
	texCol->SetTextAlign(33);
	texCol->SetTextSize(0.03);
	texCol->SetTextFont(42);
	texCol->Draw();


	// Horizontal line Tower 2 //

	if(year == 2018)
	{
		TLine *l10 = new TLine(x6,Ymin,x6,Ymax);
		l10->SetLineWidth(1);
		l10->Draw("same");


		texCol= new TLatex(x6,Ymax,"Column 6");
		texCol->SetTextAlign(33);
		texCol->SetTextSize(0.03);
		texCol->SetTextFont(42);
		texCol->Draw();

		// Horizontal line Tower 1 //

		if(ordertag != "4th"){
			TLine *l11 = new TLine(x7,Ymin,x7,Ymax);
			l11->SetLineWidth(1);
			l11->Draw("same");


			texCol= new TLatex(x7,Ymax,"Column 7");
			texCol->SetTextAlign(33);
			texCol->SetTextSize(0.03);
			texCol->SetTextFont(42);
			texCol->Draw();


			TLine *l14 = new TLine(Xmax,Ymin,Xmax,Ymax);
			l14->SetLineWidth(1);
			l14->Draw("same");


			texCol= new TLatex(x7+8,Ymax,"Column 8");
			texCol->SetTextAlign(13);
			texCol->SetTextSize(0.03);
			texCol->SetTextFont(42);
			texCol->Draw();
		}
	}

	if(Reverse ==1)
	{	


	//	ReverseXAxis(Inter);
	//	ReverseYAxis(Inter);
	}
	c22->Update();




	c22->SaveAs(OutPlotName.Data());

	if(dointer==0 && year == 2018) 
	{

		if(Method == 0) c22->SaveAs(Form("2018NoInterMean/EnPo2018%sScan.png",ordertag.Data()));
		if(Method == 1) c22->SaveAs(Form("2018NoInterFits/EnPo2018%sScan.png",ordertag.Data()));

	}


	double scaling;

	//TH2D* hNor = (TH2D*)Inter->Clone("hNor");
	int blockxmin =  Inter->GetXaxis()->FindBin(x3);
	int blockxmax =  Inter->GetXaxis()->FindBin(x5);
	int blockymin =  Inter->GetYaxis()->FindBin(Y3);
	int blockymax =  Inter->GetYaxis()->FindBin(Y5);

	double TotalSum = Inter->Integral(blockxmin,blockxmax,blockymin,blockymax);
	double TotalBin = (blockxmax - blockxmin+1) * (blockymax - blockymin+1);

	scaling = TotalSum/TotalBin;
	//	scaling = 1.0;
	cout << "scaling = " << scaling << endl;
	cout << "Total Before = " << Inter->Integral() << endl;
	//cout << "mean method = " << Inter->GetMean(blockxmin,blockxmax,blockymin,blockymax) << endl;
	//Step 2 Projection//
	//Inter->Scale(1.0/scaling);
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



	Inter->SetTitle(TitleName.Data());
	Inter->Draw("colz");

	char Outname[512];
	//	int Binwidth;
	double left;
	double right;



	//	double xinteval = ProjectionstepX;
	int LeftBin;
	int RightBin;
	int stepwidth = Binwidth/2;
	int Wide;
	cout << "NTowerY*2-1 = " << NTowerY*2-1 << endl;
	if(doNormalize==1) {
		Inter->Scale(1.0/scaling);
		Inter->SetMinimum(0.6);
		Inter->SetMaximum(1.1);
		Inter->GetXaxis()->SetTitleOffset(0.5);
		Inter->GetYaxis()->SetTitleOffset(1.3);


		Inter->Draw("colz");
//		ReverseXAxis(Inter);
//		ReverseYAxis(Inter);

		TLine *B1 = new TLine(x3,Y3,x3,Y5);
		B1->SetLineWidth(1);
		B1->Draw("same");
		TLine *B2 = new TLine(x5,Y3,x5,Y5);
		B2->SetLineWidth(1);
		B2->Draw("same");
		TLine *B3 = new TLine(x3,Y3,x5,Y3);
		B3->SetLineWidth(1);
		B3->Draw("same");
		TLine *B4 = new TLine(x3,Y5,x5,Y5);
		B4->SetLineWidth(1);
		B4->Draw("same");


		c22->SaveAs(Form("Results/%d/%s/Normalized.png",year,ordertag.Data()));

	}


	for(int i=0; i < NTowerX*2-1; i++)
	{
		TCanvas *c23 = new TCanvas("c23", "c23",0,0,1200,600);

		c23->cd();

		left  = xinitial[i]-stepwidth;
		right  = xinitial[i]+stepwidth;

		LeftBin = Inter->GetXaxis()->FindBin(left);
		RightBin = Inter->GetXaxis()->FindBin(right);
		Inter->GetXaxis()->SetTitleOffset(1.4);
		Inter->Draw("colz");

		if(doNormalize==1){
			Inter->SetMinimum(0.6);
			Inter->SetMaximum(1.1);
		}
		//Binwidth = RightBin - LeftBin;

		cout << "left = " << left << " right = " << right << endl;
		cout << " LeftBin = " << LeftBin << "  RightBin = " << RightBin << "  Binwidth = " << Binwidth << endl;
		Wide = RightBin - LeftBin+1;
		TLine *l1 = new TLine(left,Ymin,left,Ymax);

		l1->SetLineWidth(2);
		l1->Draw("same");

		TLine *l2 = new TLine(right,Ymin,right,Ymax);
		l2->SetLineWidth(2);
		l2->Draw("same");
		sprintf(Outname,"Results/%d/%s/PlotX%d.png",year,ordertag.Data(),i);
//		ReverseXAxis(Inter);
//		ReverseYAxis(Inter);
		cout << "Total = " << Inter->Integral() << endl;
		c23->Update();

		c23->SaveAs(Outname);
//		ProjXHis = new TH1D("ProjXHis","ProjXHis",EBins, Emin, Emax);
		ProjXHis = new TH1D(Form("ProjXHis%d",i),Form("ProjXHis%d",i),EBins, Emin, Emax);
		Inter->ProjectionY(Form("ProjXHis%d",i),LeftBin,RightBin);
		ProjXHis->GetXaxis()->SetTitle("y (mm)");
		ProjXHis->GetYaxis()->SetTitle("Energy (GeV)");
		ProjXHis->SetTitle("Y Axis 10 X Bins Energy Distribution");
		//	ProjXHis->Write();
		ProjXHis->Scale(1.0/(Wide));
		if(doNormalize == 1){
			ProjXHis->SetMinimum(0.0);
			ProjXHis->SetMaximum(1.25);
		}
		if(doNormalize == 0){
			ProjXHis->SetMinimum(HisEmin);
			ProjXHis->SetMaximum(HisEmax);
		}

		ProjXHis->Write();

		ProjXHis->Draw();

	//	ReverseXAxis(ProjXHis);
		c23->Update();
		TString OutnameProjX = Form("Results/%d/%s/ProjectionX%d.png",year,ordertag.Data(),i);
		c23->SaveAs(OutnameProjX);

		c23->Clear();

		c23->cd();
		c23->Divide(2,1);
		c23->cd(1);
		Inter->Draw("colz");

		l1->SetLineWidth(2);
		l1->Draw("same");
		l2->SetLineWidth(2);
		l2->Draw("same");
	//	ReverseXAxis(Inter);
	//	ReverseYAxis(Inter);
		c23->cd(2);
		ProjXHis->Draw();
	//	ReverseXAxis(ProjXHis);
		c23->Update();
		OutnameProjX = Form("Results/%d/%s/CombX%d.png",year,ordertag.Data(),i);
		c23->SaveAs(OutnameProjX);

		TCanvas * c25 = new TCanvas("c25","c25",600,600);
		c25->cd();
		Inter->Draw("colz");
		l1->Draw("same");
		l2->Draw("same");

		TString OutnameDisplayX = Form("Results/%d/%s/2DDisplayX%d.png",year,ordertag.Data(),i);
		c25->SaveAs(OutnameDisplayX);



	}


	double up;
	double down;
	//	double yinitial[NTowerY*2-1] = {y1,(y1+y2)/2,y2,(y2+y3)/2,y3,(y3+y4)/2,y4,(y4+y5)/2,y5,(y5+y6)/2,y6,(y6+y7)/2,y7,(y7+y8)/2,y8};
	//	double yinteval = ProjectionstepY;

	int UpBin;
	int DownBin;
	for(int i=0; i < NTowerY*2-1; i++)
	{
		TCanvas *c22 = new TCanvas("c22", "c22",0,0,1200,600);

		c22->cd();


		down  = yinitial[i]-stepwidth;
		up  = yinitial[i]+stepwidth;

		DownBin = Inter->GetYaxis()->FindBin(down);
		UpBin = Inter->GetYaxis()->FindBin(up);
//		ReverseXAxis(Inter);
//		ReverseYAxis(Inter);
		Inter->GetXaxis()->SetTitleOffset(1.4);
		Inter->Draw("colz");
		
		
		if(doNormalize == 1){
			Inter->SetMinimum(0.6);
			Inter->SetMaximum(1.1);
		}
		


		cout << "down = " << down << " up = " << up << endl;
		cout << " DownBin = " << DownBin << "  RightBin = " << UpBin << "  Binwidth = " << Binwidth << endl;
		Wide = UpBin - DownBin + 1;

		TLine *l1 = new TLine(Xmin,down,Xmax,down);

		l1->SetLineWidth(2);
		l1->Draw("same");

		TLine *l2 = new TLine(Xmin,up,Xmax,up);
		l2->SetLineWidth(2);
		l2->Draw("same");
		sprintf(Outname,"Results/%d/%s/PlotY%d.png",year,ordertag.Data(),i);
//		ReverseXAxis(Inter);
//		ReverseYAxis(Inter);
		c22->Update();

		c22->SaveAs(Outname);

	//	ProjYHis = new TH1D("ProjYHis","ProjYHis",EBins, Emin, Emax);
		ProjYHis = new TH1D(Form("ProjYHis%d",i),Form("ProjYHis%d",i),EBins, Emin, Emax);
		Inter->ProjectionX(Form("ProjYHis%d",i),DownBin,UpBin);
		ProjYHis->GetXaxis()->SetTitle("x (mm)");
		ProjYHis->GetYaxis()->SetTitle("Energy (GeV)");
		ProjYHis->SetTitle("X Axis 10 Y Bins Energy Distribution");
		//		ProjYHis->Write();	
		ProjYHis->Scale(1.0/(Wide));

		if(doNormalize == 1){
			ProjYHis->SetMinimum(0.0);
			ProjYHis->SetMaximum(1.25);
		}
		if(doNormalize == 0){
			ProjYHis->SetMinimum(HisEmin);
			ProjYHis->SetMaximum(HisEmax);
		}



		ProjYHis->Write();

		ProjYHis->Draw();
		ReverseXAxis(ProjYHis);
		c22->Update();
		TString OutnameProjY = Form("Results/%d/%s/ProjectionY%d.png",year,ordertag.Data(),i);
		c22->SaveAs(OutnameProjY);


		c22->Clear();
		c22->cd();

		c22->Divide(2,1);
		c22->cd(1);
		Inter->Draw("colz");
			
		
		l1->SetLineWidth(2);
		l1->Draw("same");
		l2->SetLineWidth(2);
		l2->Draw("same");
//		ReverseXAxis(Inter);
//		ReverseYAxis(Inter);
		c22->cd(2);
		ProjYHis->Draw();
//		ReverseXAxis(ProjXHis);
		c22->Update();
		OutnameProjY = Form("Results/%d/%s/CombY%d.png",year,ordertag.Data(),i);
		c22->SaveAs(OutnameProjY);


		TCanvas * c26 = new TCanvas("c26","c26",600,600);
		c26->cd();
		Inter->Draw("colz");
		l1->Draw("same");
		l2->Draw("same");
		TString OutnameDisplayY = Form("Results/%d/%s/2DDisplayY%d.png",year,ordertag.Data(),i);
		c26->SaveAs(OutnameDisplayY);

	}
	fout->Close();
}

void ReverseXAxis(TH1 *h)
{
	// Remove the current axis
	h->GetXaxis()->SetLabelOffset(999);
	h->GetXaxis()->SetTickLength(0);
	// Redraw the new axis
	gPad->Update();
	TGaxis *newaxis = new TGaxis(gPad->GetUxmax(),
			gPad->GetUymin(),
			gPad->GetUxmin(),
			gPad->GetUymin(),
			h->GetXaxis()->GetXmin(),
			h->GetXaxis()->GetXmax(),
			510,"-");
	newaxis->SetLabelOffset(-0.03);
	newaxis->Draw();
	h->GetListOfFunctions()->Add(newaxis);	

}
void ReverseYAxis(TH1 *h)
{
	// Remove the current axis
	h->GetYaxis()->SetLabelOffset(999);
	h->GetYaxis()->SetTickLength(0);
	// Redraw the new axis
	gPad->Update();
	TGaxis *newaxis = new TGaxis(gPad->GetUxmin(),
			gPad->GetUymax(),
			gPad->GetUxmin()-0.001,
			gPad->GetUymin(),
			h->GetYaxis()->GetXmin(),
			h->GetYaxis()->GetXmax(),
			510,"+");
	newaxis->SetLabelOffset(-0.03);
	newaxis->Draw();
	h->GetListOfFunctions()->Add(newaxis);	
}


