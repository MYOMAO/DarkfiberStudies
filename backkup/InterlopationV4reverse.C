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

using namespace std;



using std::cout;
using std::endl;
#endif

void InterlopationV4reverse()
{

	if(dointer == 0) return;
	if(dointer == 1){
		gStyle->SetOptFit(0);
		gStyle->SetOptStat(0);

		//	TFile *fin = new TFile(OutFileReadHis2.Data());
		//	TFile *fin = new TFile("EnergyPosition3.root");
		TFile *fin = new TFile(OutFileReadHis2.Data());

		TString Yeartag = Form("%d",year);
		TString Methodtag;
		TString recabtag;
		TString Typetag;
		if(Method == 0) Methodtag ="Mean";
		if(Method == 1) Methodtag ="Fits";
		if(recab == 0)  recabtag="prod";
		if(recab == 1)  recabtag="recalib";
		if(year == 2017){
			if ( inputfile==1) Typetag = "Interpolation-10-Degree-Tilted";
			if ( inputfile==0) Typetag = "Interpolation-0-Degree-Tilted";
		}
		if(year == 2018){
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
				Typetag = "Simulations";
			}

		}

		TString OutPlotName;
		OutPlotName = Form("Results/%s_%s_%s_%s.png",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());
		TString TitleName; 
		int binx;

		if(year == 2018){
			if(newdata == 1)
			{
				if ( inputfile==0) TitleName = "Fifth Position Scan (2018b, April 2018, Dual Channeling Rotation)";
				if ( inputfile==2) TitleName = "Sixth Position Scan (2018b, April 2018, sPHENIX+5)";
				if ( inputfile==1) TitleName = "Seventh Position Scan (2018b, April 2018, sPHENIX)";
			}
			if(newdata == 2)
			{
				TitleName = "Position Scan G4 Simulations";
			}

		}

		if(year == 2017){
			if ( inputfile==0) TitleName = "2017 Data: Energy vs Horizontal and Vertical Positions After Interpolation - 0 Degree Tilted";
			if ( inputfile==1) TitleName = "Energy vs Horizontal and Vertical Positions After Interpolation - 10 Degree Tilted";
		}



		int forward = 2;
		int backward = 2;

		int biny;
		double step = 1;
		/*
		   double Xmin = 170;
		   double Xmax = 340.0;

		   double Ymin = 60;
		   double Ymax = 245.0;
		   */
		double x;
		double y;

		cout << "XBins = " << XBins << endl;
		cout << "YBins = " << YBins << endl;


		double value[XBins][YBins];

		double finalvalue[XBins][YBins];

		TH2D *Inter = new TH2D("Inter","",XBins,Xmin,Xmax,YBins,Ymin,Ymax);
		int Nearest = 20;
		/*
		   double ylower = 35;
		   double yhigher = 188;
		   double xlower = 178;
		   double xhigher = 301; 
		   */
		int k;

		int NumberofValue;
		double Sum;

		double Modify;
		double ModifySum;
		double NModify;
		double Iactual;
		double Jactual;
		int NearestD;
		int NearestU;
		TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);

		c1->cd();

		TH2D * EnPo = (TH2D*) fin->Get("EnPo");

		int XBinMin = EnPo->GetXaxis()->FindBin(Xmin);
		int XBinMax = EnPo->GetXaxis()->FindBin(Xmax);

		int YBinMin = EnPo->GetYaxis()->FindBin(Ymin);
		int YBinMax = EnPo->GetYaxis()->FindBin(Ymax);



		EnPo->GetXaxis()->SetRange(XBinMin,XBinMax);
		EnPo->GetYaxis()->SetRange(YBinMin,YBinMax);
		EnPo->Draw("colz");

		TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());

		c1->SaveAs(Form("Results/%d/%s-Before0DegreeReverseRange.png",year,TitleName.Data()));


		TH2D *ReverseEnPo= new TH2D("ReverseEnPo","",XBins,Xmin,Xmax,YBins,Ymin,Ymax);
		double EnergyFill;
		for(int i = XBinMin; i < XBinMax; i++){

			for(int j=YBinMin; j<YBinMax;j++)
			{
				EnergyFill = EnPo->GetBinContent(i,j);
				ReverseEnPo->SetBinContent(XBinMax - i,YBinMax -j,EnergyFill);
				cout << "Energy Fill = " << EnergyFill << endl;
			}

		}


		ReverseEnPo->GetXaxis()->SetTitle("Horizontal Axis (mm)");
		ReverseEnPo->GetYaxis()->SetTitle("Vertical Axis (mm)");
		if(year == 2018){
			if(newdata == 2)
			{
				TitleName = "Position Scan G4 Simulations";
			}
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

		ReverseEnPo->SetTitle(Form("%s Beofre Interpolation",TitleName.Data()));
		ReverseEnPo->SetMaximum(EmaxHis);
		ReverseEnPo->SetMinimum(EminHis);

		ReverseEnPo->Draw("colz");
		c1->Update();


		double XVP;
		double YVP;


		int XNow;
		int YNow;

		if(reverse ==1)
		{	
			ReverseXAxis(ReverseEnPo);
			ReverseYAxis(ReverseEnPo);
		}
		c1->Update();
EnPo2018
		TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());


		c1->SaveAs(Form("Results/%d/%s-Before0DegreeReverse.png",year,TitleName.Data()));






		for(int i = XBinMin; i < XBinMax; i++)
		{

			x = Xmin + Xstep*(i-XBinMin);


			for(int j = YBinMin; j < YBinMax; j++)
			{

				//	TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
				y = Ymin + Ystep*(j-YBinMin);




				value[i-XBinMin][j-YBinMin] = EnPo->GetBinContent(i,j);

				//cout << " i = " << i  << "  x = " << x << "  j = " << j <<  "  y = " << y << "  Value  = " <<  value[i-XBinMin][j-YBinMin]  << endl;
				cout << "  x = " << x << "  y = " << y << "  Value  = " <<  value[i-XBinMin][j-YBinMin]  << endl;

			}
		}

		//Horizontal Interpolation Begins//

		for(int i =XBinMin + backward; i < XBinMax - backward; i++)
		{

			for(int j =YBinMin+ backward; j < YBinMax - backward; j++)
			{

				//cout << "OK" << endl;

				NumberofValue = 0;
				Sum = 0;

				XNow = XBins - i;
				YNow = YBins - j;


				for(int k = i - backward-XBinMin; k < i + forward +1-XBinMin; k++)
				{

					for(int m = j - backward-YBinMin; m < j+backward+1-YBinMin; m++)
					{

						if(value[k][m] > 0) NumberofValue = NumberofValue + 1;

						Sum = Sum + value[k][m];
EnPo2018
					}

				}

				cout << "Number of Value = " << NumberofValue << endl;

				cout << "Sum = " << Sum << endl;

				if(NumberofValue > 0) finalvalue[i-XBinMin][j-YBinMin] = Sum/NumberofValue;
				if(NumberofValue ==0) finalvalue[i-XBinMin][j-YBinMin] = 0;



				if(finalvalue[i-XBinMin][j-YBinMin]  == 0 && i > XBinMin + ThresX  && i < XBinMax - ThresX && j > YBinMin +ThresYH  && j < YBinMax - ThresY){
					NModify = 0;
					ModifySum = 0;
					NearestDX = -Nearest;
					NearestUX = Nearest;
					NearestDY = -Nearest;
					NearestUY = Nearest;

					if(i-XBinMin-Nearest < 0 ) NearestDX = -ThresX +1;
					if(i-XBinMin+Nearest >  XBinMax-3 ) NearestUX = ThresX -1;
					if(j-YBinMin-Nearest < 0 ) NearestDY = -ThresY +1;
					if(j-YBinMin+Nearest >  YBinMax-3 ) NearestUY = ThresY -1;

					cout << "Nearest U = " <<  NearestU << endl;
					cout <<  "i-XBinMin-Nearest  = " << i-XBinMin+NearestU << endl;
					cout << "XBinmax  = " << XBinMax << endl;

					for(int  iredo = NearestDX; iredo < NearestUX+1; iredo++) 
					{
						Iactual = iredo;

						for(int jredo = NearestDY; jredo < NearestUY+1; jredo++)
						{
							Jactual = jredo;

							Modify = finalvalue[i-XBinMin+iredo][j-YBinMin+jredo];
							if(Modify > 0){
								NModify = NModify+1/sqrt(Iactual*Iactual+Jactual*Jactual);
								ModifySum = ModifySum + Modify/sqrt(Iactual*Iactual+Jactual*Jactual);	
							}
						}
					}
					if (NModify > 0) finalvalue[i-XBinMin][j-YBinMin] = ModifySum/NModify;
					cout << "New Final Value = " << 	finalvalue[i-XBinMin][j-YBinMin]  << endl;
				}

				cout << " i = " << i <<  "  j = " << j << endl;
				cout << " Xnow = " << XNow <<  "  YNow = " << YNow << endl;



				cout << "Final Value is " << finalvalue[i-XBinMin][j-YBinMin]  << endl;


				//Inter->SetBinContent(i,j,finalvalue[i][j]);

				//		Inter->SetBinContent(i-XBinMin,j-YBinMin,finalvalue[i-XBinMin][j-YBinMin]);
				Inter->SetBinContent(XNow,YNow,finalvalue[i-XBinMin][j-YBinMin]);

			}


		}

		/*
		   cout << "Horizontal Done" << endl;
		   /%s_%s_%s.png",Typetag.Data(),Methodtag.Data(),recabtag.Data()

		//Vertical Interpolation Begins//

		cout << "DONE Value" << endl;
		Interpolation-DualChannel-Reversed_Mean_recalib.png
		for(int i = 1; i < XBins; i++)
		{

		for(int j = 1; j < YBins; j++)
		{

		cout << "Before Updating: Binx =  " << i << "   " << "Bin y = " << j << " Value =  " << value[i][j] << endl;


		if (value[i][j] < 6.8 && value[i][j-1] >0 && i < XBins && j < YBins)
		{


		k = j;
		do {
		k = k + 1;

		//	cout << "k value is = " << k << endl;
		}
		while(value[i][k] == 0 && k < YBins); 

		//cout << "neW k " << k  << endl;

		value[i][j] =value[i][j-1] + (value[i][k] - value[i][j-1])/(k+1-j);

		cout << "After Updating: Binx =  " << i << "   " << "  Bin y = " << j << "  Value =  " <<value[i][j] << endl;

		}


		}


		}

		cout << "Vk =" << k << endl;

		//Vertical Interpolation Ends//

		cout << "VERTICAL DONE" << endl;

*/
		/*
		   for(int i =0; i < XBins; i++)
		   {



		   for(int j = 1; j < YBins; j++)
		   {


		   }


		   }
		   */



		Inter->GetXaxis()->SetTitle("Horizontal Axis (mm)");
		Inter->GetYaxis()->SetTitle("Vertical Axis (mm)");
			if(year == 2018){
			if(newdata == 2)
			{
				TitleName = "Position Scan G4 Simulations";
			}
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


		TFile *fout = new TFile(InterpolatedFile.Data(),"RECREATE");
		Inter->Write();


		TCanvas *c22 = new TCanvas("c22", "c22",0,0,800,600);

		c22->cd();

		Inter->SetMinimum(EminHis);

		Inter->SetMaximum(EmaxHis);





		Inter->Draw("colz");


		if(year == 2017){
			// Horizontal line Tower 6 //
			if(DrawLine == 1){
				TLine *l1 = new TLine(Xmin,y1,Xmax,y1);
				l1->SetLineWidth(1);
				l1->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(Xmin,y1,"Row 1");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 5 //


				TLine *l2 = new TLine(Xmin,y2,Xmax,y2);
				l2->SetLineWidth(1);
				l2->Draw("same");



				texCol= new TLatex(Xmin,y2,"Row 2");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 4//


				TLine *l3 = new TLine(Xmin,y3,Xmax,y3);
				l3->SetLineWidth(1);
				l3->Draw("same");



				texCol= new TLatex(Xmin,y3,"Row 3");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();



				// Horizontal line Tower 3 //


				TLine *l4 = new TLine(Xmin,y4,Xmax,y4);
				l4->SetLineWidth(1);
				l4->Draw("same");



				texCol= new TLatex(Xmin,y4,"Row 4");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 2 //


				TLine *l4 = new TLine(Xmin,y5,Xmax,y5);
				l4->SetLineWidth(1);
				l4->Draw("same");




				texCol= new TLatex(Xmin,y5,"Row 5");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Vertical line Tower 6 //


				TLine *l14 = new TLine(x1,Ymin,x1,Ymax);
				l14->SetLineWidth(1);
				l14->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x1,Ymax,"Column 1");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();



				TLine *l6 = new TLine(x2,Ymin,x2,Ymax);
				l6->SetLineWidth(1);
				l6->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x2,Ymax,"Column 2");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 5 //


				TLine *l7 = new TLine(x3,Ymin,x3,Ymax);
				l7->SetLineWidth(1);
				l7->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x3,Ymax,"Column 3");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 4//


				TLine *l8 = new TLine(x4,Ymin,x4,Ymax);
				l8->SetLineWidth(1);
				l8->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x4,Ymax,"Column 4");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 3 //

				TLine *l9 = new TLine(x5,Ymin,x5,Ymax);
				l9->SetLineWidth(1);
				l9->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x5,Ymax,"Column 5");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();
			}

			// Horizontal line Tower 2 //


		}

		if(year == 2018){
			// Horizontal line Tower 6 //
			if(DrawLine == 1){
				TLine *l1 = new TLine(Xmin,y1,Xmax,y1);
				l1->SetLineWidth(1);
				l1->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(Xmin,y1,"Row 1");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 5 //


				TLine *l2 = new TLine(Xmin,y2,Xmax,y2);
				l2->SetLineWidth(1);
				l2->Draw("same");



				texCol= new TLatex(Xmin,y2,"Row 2");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 4//


				TLine *l3 = new TLine(Xmin,y3,Xmax,y3);
				l3->SetLineWidth(1);
				l3->Draw("same");



				texCol= new TLatex(Xmin,y3,"Row 3");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();



				// Horizontal line Tower 3 //


				TLine *l4 = new TLine(Xmin,y4,Xmax,y4);
				l4->SetLineWidth(1);
				l4->Draw("same");



				texCol= new TLatex(Xmin,y4,"Row 4");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 2 //


				TLine *l4 = new TLine(Xmin,y5,Xmax,y5);
				l4->SetLineWidth(1);
				l4->Draw("same");




				texCol= new TLatex(Xmin,y5,"Row 5");
				texCol->SetTextAlign(11);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 1 //

				TLine *l12 = new TLine(Xmin,y6,Xmax,y6);
				l12->SetLineWidth(1);
				l12->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(Xmin,y6,"Row 6");
				texCol->SetTextAlign(13);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				TLine *l13 = new TLine(Xmin,y7,Xmax,y7);
				l13->SetLineWidth(1);
				l13->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(Xmin,y7,"Row 7");
				texCol->SetTextAlign(13);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Vertical line Tower 6 //


				TLine *l14 = new TLine(x1,Ymin,x1,Ymax);
				l14->SetLineWidth(1);
				l14->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x1,Ymax,"Column 1");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();



				TLine *l6 = new TLine(x2,Ymin,x2,Ymax);
				l6->SetLineWidth(1);
				l6->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x2,Ymax,"Column 2");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 5 //


				TLine *l7 = new TLine(x3,Ymin,x3,Ymax);
				l7->SetLineWidth(1);
				l7->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x3,Ymax,"Column 3");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 4//


				TLine *l8 = new TLine(x4,Ymin,x4,Ymax);
				l8->SetLineWidth(1);
				l8->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x4,Ymax,"Column 4");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 3 //

				TLine *l9 = new TLine(x5,Ymin,x5,Ymax);
				l9->SetLineWidth(1);
				l9->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x5,Ymax,"Column 5");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();


				// Horizontal line Tower 2 //


				TLine *l10 = new TLine(x6,Ymin,x6,Ymax);
				l10->SetLineWidth(1);
				l10->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x6,Ymax,"Column 6");
				texCol->SetTextAlign(33);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();

				// Horizontal line Tower 1 //

				TLine *l11 = new TLine(Xmax,Ymin,Xmax,Ymax);
				l11->SetLineWidth(1);
				l11->Draw("same");


				TLatex* texCol;
				texCol= new TLatex(x6+8,Ymax,"Column 7");
				texCol->SetTextAlign(13);
				texCol->SetTextSize(0.03);
				texCol->SetTextFont(42);
				texCol->Draw();
			}
		}

		if(reverse ==1)
		{	
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
		}
		c22->Update();




		c22->SaveAs(OutPlotName.Data());
		if(DrawLine == 0){
			if(Method == 0)	c22->SaveAs(Form("InterMean/Inter%d%sScan.png",year,ordertag.Data()));
			if(Method == 1)	c22->SaveAs(Form("InterFits/Inter%d%sScan.png",year,ordertag.Data()));
		}
		if(DrawLine == 1){
			if(Method == 0)	c22->SaveAs(Form("InterMeanWithLine/Inter%d%sScan.png",year,ordertag.Data()));
			if(Method == 1)	c22->SaveAs(Form("InterFitsWithLine/Inter%d%sScan.png",year,ordertag.Data()));
		}

		//c22->SaveAs("Results/Interpolation-0-Degree-Reversed.png");

		//Projection Code From Here//

		//Step 1 Normalization//

		double scaling;
		
		//TH2D* hNor = (TH2D*)Inter->Clone("hNor");
		
		if(year == 2018)
		{
		int blockxmin =  Inter->GetXaxis()->FindBin(x3);
		int blockxmax =  Inter->GetXaxis()->FindBin(x5);
		int blockymin =  Inter->GetYaxis()->FindBin(y3);
		int blockymax =  Inter->GetYaxis()->FindBin(y5);
		}

		if(year == 2017)
		{
		int blockxmin =  Inter->GetXaxis()->FindBin(x2);
		int blockxmax =  Inter->GetXaxis()->FindBin(x4);
		int blockymin =  Inter->GetYaxis()->FindBin(y2);
		int blockymax =  Inter->GetYaxis()->FindBin(y4);
	}



		double TotalSum = Inter->Integral(blockxmin,blockxmax,blockymin,blockymax);
		double TotalBin = (blockxmax - blockxmin + 1) * (blockymax - blockymin + 1);

		scaling = TotalSum/TotalBin;

		cout << "scaling = " << scaling << endl;
		//cout << "mean method = " << Inter->GetMean(blockxmin,blockxmax,blockymin,blockymax) << endl;
		//Step 2 Projection//

		char Outname[512];

		double left;
		double right;
	//	double xinitial[NTowerX*2-1] = {cx1,(cx1+cx2)/2,cx2,(cx2+cx3)/2,cx3,(cx3+cx4)/2,cx4,(cx4+cx5)/2,cx5,(cx5+cx6)/2,cx6,(cx6+cx7)/2,cx7};
		//	double xinteval = ProjectionstepX;
		int LeftBin;
		int RightBin;
		int stepwidth = Binwidth/2;
		if(doNormalize =1) {
			Inter->Scale(1.0/scaling);
			Inter->Draw("colz");
			Inter->SetMaximum(1.1);
			Inter->SetMinimum(0.6);
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
		TLine *B1 = new TLine(x3,y3,x3,y5);
		B1->SetLineWidth(1);
		B1->Draw("same");

		TLine *B2 = new TLine(x5,y3,x5,y5);
		B2->SetLineWidth(1);
		B2->Draw("same");
		TLine *B3 = new TLine(x3,y3,x5,y3);
		B3->SetLineWidth(1);
		B3->Draw("same");
		TLine *B4 = new TLine(x3,y5,x5,y5);
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
			int	Wide = RightBin - LeftBin+1;
			cout << "left = " << left << endl;
			LeftBin = Inter->GetXaxis()->FindBin(left);
			RightBin = Inter->GetXaxis()->FindBin(right);
			Inter->GetXaxis()->SetTitleOffset(1.4);
			Inter->Draw("colz");

			TLine *l1 = new TLine(left,Ymin,left,Ymax);

			l1->SetLineWidth(2);
			l1->Draw("same");

			TLine *l2 = new TLine(right,Ymin,right,Ymax);
			l2->SetLineWidth(2);
			l2->Draw("same");
			sprintf(Outname,"Results/%d/PlotX%d.png",year,i);
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);

			c23->Update();

			c23->SaveAs(Outname);

			TH1D * ProjXHis = new TH1D("ProjXHis","ProjXHis",EBins, Emin, Emax);
			Inter->ProjectionY("ProjXHis",LeftBin,RightBin);
			ProjXHis->GetXaxis()->SetTitle("y (mm)");
			ProjXHis->GetYaxis()->SetTitle("Energy (GeV)");
			ProjXHis->SetTitle("10 Y Bin Energy Distribution");
			ProjXHis->Scale(1.0/(Wide));
			ProjXHis->Draw();
			ReverseXAxis(ProjXHis);
			c23->Update();
			TString OutnameProjX = Form("Results/%d/ProjectuonX%d.png",year,i);
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
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
			c23->cd(2);
			ProjXHis->SetMinimum(0);
			ProjXHis->SetMaximum(1.2);
			ProjXHis->Draw();
			ReverseXAxis(ProjXHis);
			c23->Update();
			OutnameProjX = Form("Results/%d/%s/CombX%d.png",year,ordertag.Data(),i);
			c23->SaveAs(OutnameProjX);





		}


		double up;
		double down;
	//	double yinitial[NTowerY*2-1] = {cy1,(cy1+cy2)/2,cy2,(cy2+cy3)/2,cy3,(cy3+cy4)/2,cy4,(cy4+cy5)/2,cy5,(cy5+cy6)/2,cy6,(cy6+cy7)/2,cy7,(cy7+cy8)/2,cy8};
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
				Wide = UpBin - DownBin+1;
			DownBin = Inter->GetYaxis()->FindBin(down);
			UpBin = Inter->GetYaxis()->FindBin(up);
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
			Inter->GetXaxis()->SetTitleOffset(1.4);
			Inter->Draw("colz");

			TLine *l1 = new TLine(Xmin,down,Xmax,down);

			l1->SetLineWidth(2);
			l1->Draw("same");

			TLine *l2 = new TLine(Xmin,up,Xmax,up);
			l2->SetLineWidth(2);
			l2->Draw("same");
			sprintf(Outname,"Results/%d/PlotY%d.png",year,i);
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
			c22->Update();

			c22->SaveAs(Outname);

			TH1D * ProjYHis = new TH1D("ProjYHis","ProjYHis",EBins, Emin, Emax);
			Inter->ProjectionX("ProjYHis",DownBin,UpBin);
			ProjYHis->GetXaxis()->SetTitle("x (mm)");
			ProjYHis->GetYaxis()->SetTitle("Energy (GeV)");
			ProjYHis->SetTitle("10 X Bin Energy Distribution");
			ProjYHis->Scale(1.0/(Wide));
			ProjYHis->Draw();
			ReverseXAxis(ProjYHis);
			c22->Update();
			TString OutnameProjY = Form("Results/%d/ProjectuonY%d.png",year,i);
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
			ReverseXAxis(Inter);
			ReverseYAxis(Inter);
			c22->cd(2);
			ProjYHis->SetMinimum(0);
			ProjYHis->SetMaximum(1.2);

			ProjYHis->Draw();
			ReverseXAxis(ProjXHis);
			c22->Update();
			OutnameProjY = Form("Results/%d/%s/CombY%d.png",year,ordertag.Data(),i);
			c22->SaveAs(OutnameProjY);






		}
	}
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
}
