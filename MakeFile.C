#include "parameters.h"
#include <fstream>
//#include "Variable.h"


void MakeFile(){

	TH2D * h1;
	TH2D * h2;
	TH2D * h3;
	TH3D * Energyhis;

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




	TString TitleName = Form("%s_%s_%s_%s",Yeartag.Data(),Typetag.Data(),Methodtag.Data(),recabtag.Data());


	gSystem->Load("libg4eval.so");
	gSystem->Load("libqa_modules.so");
	gSystem->Load("libPrototype4.so");
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *fin = new TFile(InputFile.Data());


	//	TFile *fin = new TFile("/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root");

	TTree *t = (TTree *)fin->Get("T");
	t->SetAlias("C2_Inner_e", "1*abs(TOWER_RAW_C2[2].energy)");
	t->SetAlias("C2_Outer_e", "1*abs(TOWER_RAW_C2[3].energy)");
	//t->SetAlias("Average_column", "Sum$(TOWER_CALIB_CEMC.get_column() * TOWER_CALIB_CEMC.get_energy())/Sum$(TOWER_CALIB_CEMC.get_energy())");
	// t->SetAlias("Average_HODO_HORIZONTAL", "Sum$(TOWER_CALIB_HODO_HORIZONTAL.towerid * (abs(TOWER_CALIB_HODO_HORIZONTAL.energy)>30) * abs(TOWER_CALIB_HODO_HORIZONTAL.energy))/Sum$((abs(TOWER_CALIB_HODO_HORIZONTAL.energy)>30) * abs(TOWER_CALIB_HODO_HORIZONTAL.energy))");
	t->SetAlias("Valid_HODO_HORIZONTAL", "Sum$(abs(TOWER_CALIB_HODO_HORIZONTAL.energy)>30) > 0");
	t->SetAlias("No_Triger_VETO", "Sum$(abs(TOWER_RAW_TRIGGER_VETO.energy)>15)==0");
	t->SetAlias("Valid_HODO_VERTICAL", "Sum$(abs(TOWER_CALIB_HODO_VERTICAL.energy)>30) > 0");
	//	t->SetAlias("C2_Sum_e", "C2_Inner_e + C2_Outer_e");
	//  t->SetAlias("Average_HODO_VERTICAL","Sum$(TOWER_CALIB_HODO_VERTICAL.towerid * (abs(TOWER_CALIB_HODO_VERTICAL.energy)>30) * abs(TOWER_CALIB_HODO_VERTICAL.energy))/Sum$((abs(TOWER_CALIB_HODO_VERTICAL.energy)>30) * abs(TOWER_CALIB_HODO_VERTICAL.energy))");
	//return;
	t->SetAlias("Energy_Sum_CEMC", "1*Sum$(TOWER_CALIB_CEMC.get_energy())");

	//TH3F *Energyhis = new TH3F("Energyhis","",170,170,340,185,60,245,200,0,10);

	//TH3D *Energyhis = new TH3D("Energyhis","",140,170,310,185,60,245,200,0,12);


	const int XAd = 40;
	const int YAd = 40;
	int Ratio = 10;


	TFile *fin2;
	//	t->Draw("clus_5x5_recalib.sum_E:info.beam_2CV_mm + 5*info.hodo_v:info.beam_2CH_mm - 5*info.hodo_h>>Energyhis","good_e");
	if(doSim == 0){
		if(recab ==1){
			if(posFix ==1){
				cout << " Doing Pos Fix" << endl;
				fin2 = new TFile(PosFixOut.Data());
				TTree *t2 = (TTree *)fin2->Get("RunxyFix");
				t->AddFriend(t2);
				Energyhis = new TH3D("EnerTMath::Sin(theta)gyhis","",XBins, Xmin,Xmax,YBins,Ymin,Ymax,EBins,Emin,Emax);
				t->Draw(Form("clus_5x5_recalib.sum_E*%s:beam_2CV_mm_fix + 5*info.hodo_v*%d:beam_2CH_mm_fix - 5*info.hodo_h*%d>>Energyhis",scale.Data(),dohodo,dohodo),"good_e");
				//return;
				cout << "Mean here =" << Energyhis->GetMean() << endl;
	

			}

			if(posFix ==0){
				cout << "Not Doing Pos Fix" << endl;
				Energyhis = new TH3D("Energyhis","",XBins, Xmin,Xmax,YBins,Ymin,Ymax,EBins,Emin,Emax);
				//	t->Draw(Form("clus_5x5_recalib.sum_E*%s:beam_2CV_mm + 5*info.hodo_v:beam_2CH_mm - 5*info.hodo_h>>Energyhis","good_e",scale.Data()));
				t->Draw(Form("clus_5x5_recalib.sum_E*%s:beam_2CV_mm + 5*info.hodo_v*%d:beam_2CH_mm - 5*info.hodo_h*%d>>Energyhis",scale.Data(),dohodo,dohodo),"good_e");
			}
			cout << "Mean here =" << Energyhis->GetMean() << endl;
		}




		if(recab ==0){
			cout << "Doing Debug" << endl;
			fin2 = new TFile(PosFixOut.Data());
			TTree *t2 = (TTree *)fin2->Get("RunxyFix");
			t->AddFriend(t2);
			Energyhis = new TH3D("Energyhis","",XBins, Xmin,Xmax,YBins,Ymin,Ymax,EBins,Emin,Emax);
			//	t->Draw(Form("clus_5x5_prod.sum_E*%s:beam_2CV_mm_fix + 5*info.hodo_v:beam_2CH_mm_fix - 5*info.hodo_h>>Energyhis",scalerecab.Data()),"good_e");
			//	t->Draw(Form("clus_5x5_prod.sum_E*%s:beam_2CV_mm_fix + 5*info.hodo_v:beam_2CH_mm_fix - 5*info.hodo_h>>Energyhis",scale.Data()),"good_e");

			if(hodoX == 0 && hodoY == 1) t->Draw(Form("clus_5x5_prod.sum_E*%s:beam_2CV_mm_fix + 5*info.hodo_v:beam_2CH_mm_fix - 5*info.hodo_h>>Energyhis",scale.Data()));
			if(hodoX == 1 && hodoY == 1) t->Draw(Form("clus_5x5_prod.sum_E*%s:beam_2CV_mm_fix + 5*info.hodo_v:beam_2CH_mm_fix + 5*info.hodo_h>>Energyhis",scale.Data()));



			//return;
			cout << "Mean here =" << Energyhis->GetMean() << endl;
		}

	}


	//t->Draw("clus_5x5_recalibrate.sum_E:beam_2CV_mm_fix + 5*info.hodo_v:beam_2CH_mm_fix - 5*info.hodo_h>>Energyhis","good_e");

	if(doSim==1){
		cout << "DOING SIMULATIONS" << endl;
		Energyhis = new TH3D("Energyhis","",XBins, Xmin,Xmax,YBins,Ymin,Ymax,EBins,Emin,Emax);
		t->Draw(Form("sum_energy_T*%s:truth_y * 10 + 5*info.hodo_v*%d + %f:truth_z * %f * 10 - 5*info.hodo_h*%d + %f>>Energyhis",scale.Data(),dohodo,shifty,anglecorr,dohodo,shiftx));
		cout << "Mean Simulation =" << Energyhis->GetMean() << endl;
	}



	Energyhis->GetZaxis()->SetTitle("Energy (GeV)");

	//TFile *fout =  new TFile("His2.root","RECREATE");

	if(posFix ==1)
	{
		t->SetAlias("XPos", "beam_2CH_mm_fix");
		t->SetAlias("YPos","beam_2CV_mm_fix");
	}
	if(posFix ==0)
	{
		t->SetAlias("XPos", "beam_2CH_mm");
		t->SetAlias("YPos","beam_2CV_mm");
	}
	TFile *fout =  new TFile(OutFileMakeFile.Data(),"RECREATE");
	fout->cd();
	Energyhis->Write();

	double mean = Energyhis->GetMean();

	cout << "Counts = "<< Energyhis->Integral() << endl;
	cout << "Mean is =  "<< mean << endl;

	//Hodoscope Analysis//
	//
	ofstream foutWrite("DatFiles/XYPosition.dat");
	TH1D * Run = new TH1D("Run","",80,420,500);
	foutWrite << "   Run   " << "   X-Pos   " << "   Y-Pos   " << endl;
	fout->Close();


	TFile * RunF;
	for(int i = 0; i < RunBins; i++)
	{
		cout << "working on  i = " << i << endl;
		RunF = new TFile(Form("Run/Run%dxy.root",i),"RECREATE");
		RunF->cd();
		int runnum = Runmin + i * Runstep;
		//cout << runnum << endl;
		TString event_sel2 = Form("good_e && run == %d", runnum);
		//cout << event_sel << endl;
		TH2D * XYPos = new TH2D("XYPos","",XBins, Xmin, Xmax, YBins,Ymin,Ymax);
		t->Project("XYPos","YPos:XPos",event_sel2.Data());
		TH1D * XPosi = new TH1D("XPosi","",XBins, Xmin, Xmax);
		t->Project("XPosi","XPos",event_sel2.Data());
		TH1D * YPosi = new TH1D("YPosi","",YBins, Ymin, Ymax);
		t->Project("YPosi","YPos",event_sel2.Data());
		cout << "Run = " << runnum  << "  X = " << XPosi->GetMean() << "   Y =  " <<  YPosi->GetMean() << endl;
		foutWrite << "   " << runnum  << "      " << XPosi->GetMean() << "      " <<  YPosi->GetMean() << endl;

		//cout << "Total = " << XYPos->Integral() << endl;
		XYPos->Divide(XYPos);
		XYPos->Scale(runnum);
		XYPos->SetDirectory(RunF);
		XYPos->SetMinimum(Runmin);
		XYPos->SetMaximum(Runmax);
		XYPos->Write();
		XYPos->GetXaxis()->SetTitle("X (mm)");
		XYPos->GetYaxis()->SetTitle("Y (mm)");
		XYPos->SetTitle("Run Number vs X - Y Position");
		RunF->Close();
	}
	//foutWrite->Close();
	cout << "DONE" << endl;
	/*
	   TCanvas* c= new TCanvas("c","",600,600);
	   c->cd();
	   XYPos->Divide(XYPos);
	   XYPos->Draw("colz");
	   c->SaveAs("Results/XYPosition.png");

	   XYPos->Write();
	   t->Project("Run","run",event_sel);
	   Run->GetXaxis()->SetTitle("Run");
	   Run->GetYaxis()->SetTitle("Counts");
	   Run->SetTitle("Run Distribution");

	   Run->Draw();
	   c->SaveAs("Results/Run.png");
	   XYPos->Write();
	   Run->Write();
	   */	
	TFile *fout2 =  new TFile(HodoScope.Data(),"RECREATE");
						fout2->cd();

	if(debug == 1){
		TCut event_sel = "good_e";

		const int N=2;
		TString Hodo1[N] = {"hodo_h","hodo_v"};
		TString Hodo2[N] = {"hodo_h","hodo_v"};
		TString Hodo3[N] = {"hodo_h","hodo_v"};
		TString Hodo4[N] = {"hodo_h","hodo_v"};
		cout << "START DEBUGGING" << endl;

		int Ratio = 5;


		for(int i=0; i <N;i++){

			for(int j=0; j < N; j++){

				for(int k=0; k < N; k++){

					for(int l=0; l < N; l++){
						cout << "Pass 1" << endl;
						if(posFix == 1){

							t->SetAlias("XPosP", Form("beam_2CH_mm_fix + 5* int( %s + 0.5)",Hodo1[i].Data()));
							t->SetAlias("XPosM",Form("beam_2CH_mm_fix - 5* int( %s + 0.5)",Hodo2[j].Data()));  
							t->SetAlias("YPosP", Form("beam_2CV_mm_fix + 5* int(%s + 0.5)",Hodo3[k].Data()));
							t->SetAlias("YPosM", Form("beam_2CV_mm_fix - 5* int(%s + 0.5)",Hodo4[l].Data()));

						}
						cout << "Pass 2" << endl;

						if(posFix == 0){

							t->SetAlias("XPosP", Form("beam_2CH_mm + 5* int( %s + 0.5)",Hodo1[i].Data()));
							t->SetAlias("XPosM",Form("beam_2CH_mm - 5* int( %s + 0.5)",Hodo2[j].Data()));  
							t->SetAlias("YPosP", Form("beam_2CV_mm + 5* int(%s + 0.5)",Hodo3[k].Data()));
							t->SetAlias("YPosM", Form("beam_2CV_mm - 5* int(%s + 0.5)",Hodo4[l].Data()));

						}

						//return;

						//TCut event_sel = "Valid_HODO_HORIZONTAL && Valid_HODO_VERTICAL && No_Triger_VETO";




						//cout << "Cut is " << event_sel.data() << endl;
						t->Draw("XPosP >> h1",event_sel);
						cout << "Pass 3" << endl;



						TH1D *h2= new TH1D("h2","",200,0,7);

						t->Draw("clus_5x5_prod.average_col >> h2",event_sel);

						t->Draw("beam_2CV_mm >> h3",event_sel); 

						t->Draw("YPosP >> h5",event_sel);

						cout << "Pass 4" << endl;



						TH1D *h4= new TH1D("h4","",200,0,7);

						t->Draw("clus_5x5_prod.average_row >> h4",event_sel);

						TH2D *h7= new TH2D("h7","",XBins/5,Xmin+XAd,Xmax+XAd,8,-0.5,7.5);
						TH2D *h8= new TH2D("h8","",YBins/5,Ymin,Ymax,8,-0.5,7.5);  

						TH2D *h9= new TH2D("h9","",XBins/5,Xmin,Xmax,8,-0.5,7.5);
						TH2D *h10= new TH2D("h10","",YBins/5,Ymin-YAd,Ymax-YAd,8,-0.5,7.5);



						t->Draw("clus_5x5_prod.average_col:XPosP >> h7",event_sel);

						cout << "Pass 5" << endl;


						//TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);




						//h7->GetXaxis()->SetTitle("2CH + 5*Hodo (mm)");
						h7->GetYaxis()->SetTitle("Average Column (mm) ");
						h7->SetTitle("Average Column vs X Position Plus");

						h7->Draw("colz");
						cout << "Pass 6" << endl;


						t->Draw("clus_5x5_prod.average_row:YPosP >> h8",event_sel);

						h8->GetXaxis()->SetTitle("2CV + 5*Hodo (mm)");
						h8->GetYaxis()->SetTitle("Average Row (mm)");
						h8->SetTitle("Average Row vs Y Position Plus");

						h8->Draw("colz");


						t->Draw("clus_5x5_prod.average_col:XPosM >> h9",event_sel);

						h9->GetXaxis()->SetTitle("2CH - 5*Hodo (mm)");
						h9->GetYaxis()->SetTitle("Average Column (mm) ");
						h9->SetTitle("Average Column vs X Position Minus");

						h9->Draw("colz");


						cout << "Pass 7" << endl;


						t->Draw("clus_5x5_prod.average_row:YPosM >> h10",event_sel);

						h10->GetXaxis()->SetTitle("2CV - 5*Hodo (mm)");
						h10->GetYaxis()->SetTitle("Average Row (mm)");
						h10->SetTitle("Average Row vs Y Position Minus");
						h10->Draw("colz");
						cout << "Pass 7.9" << endl;
			
						/*
						h1->Write();
						h2->Write();
						h3->Write();
						h4->Write();
		
						//h5->Write();
						//h6->Write();
						h7->Write();

						h8->Write(); 

						h9->Write();
		
						h10->Write();
						*/
						cout << "Pass 1" << endl;

						h7->GetXaxis()->SetTitle(Form("beam_2CH_mm + 5* int( %s + 0.5)",Hodo1[i].Data()));
						h7->GetYaxis()->SetTitle("clus_5x5_prod.average_col");
						h8->GetXaxis()->SetTitle(Form("beam_2CV_mm + 5* int( %s + 0.5)",Hodo3[k].Data()));
						h8->GetYaxis()->SetTitle("clus_5x5_prod.average_row");
						h9->GetXaxis()->SetTitle(Form("beam_2CH_mm - 5* int( %s + 0.5)",Hodo2[j].Data()));
						h9->GetYaxis()->SetTitle("clus_5x5_prod.average_col");
						h10->GetXaxis()->SetTitle(Form("beam_2CV_mm - 5* int( %s + 0.5)",Hodo4[l].Data()));
						h10->GetYaxis()->SetTitle("clus_5x5_prod.average_row");
						TCanvas* c= new TCanvas("c","",1200,1200);
						c->Divide(2,2);
						c->cd(1);
						h7->Draw("colz");
						c->cd(2);
						h8->Draw("colz");
						c->cd(3);
						cout << "Pass Here" << endl;

						h9->Draw("colz");
						c->cd(4);
						cout << "Pass 2" << endl;
						h10->Draw("colz");
						c->SaveAs(Form("Results/%d/%s_AllPossible_%d_%d_%d_%d.png",year,TitleName.Data(),i,j,k,l));
						if(i == 0 && j ==0 && k == 1&& l == 1)
						{
							c->SaveAs(Form("Hodo/Hodoscope%d%s.png",year,ordertag.Data()));

						}
					}
				}
			}
		}

	}


	if(debug == 0){
		if(doSim == 0){
			TCut event_sel = "good_e";
			t->SetAlias("XPosM","beam_2CH_mm_fix - 5* int(hodo_h + 0.5)");
			t->SetAlias("YPosP", "beam_2CV_mm_fix + 5* int(hodo_v + 0.5)");
			t->Project("h1","clus_5x5_prod.average_col:XPosM",event_sel);
			t->Project("h2","clus_5x5_prod.average_row:YPosP",event_sel);
		}

		if(doSim == 1){
			t->SetAlias("XPosM","beam_2CH_mm - 5* int(hodo_h + 0.5)");
			t->SetAlias("YPosP", "beam_2CV_mm + 5* int(hodo_v + 0.5)");
			t->Project("h1","clus_5x5_prod.average_col:XPosM");
			t->Project("h2","clus_5x5_prod.average_row:YPosP");
		}


		h1= new TH2D("h1","",XBins/5,Xmin+XAd,Xmax+XAd,8,-0.5,7.5);
		h2= new TH2D("h2","",YBins/5,Ymin,Ymax,8,-0.5,7.5);

		h1->GetXaxis()->SetTitle("2CH - 5*Hodo (mm)");
		h1->GetYaxis()->SetTitle("Average Column (mm) ");
		h1->SetTitle("Average Column vs X Position Minus");
		h2->GetXaxis()->SetTitle("2CV + 5*Hodo (mm)");
		h2->GetYaxis()->SetTitle("Average Row (mm) ");
		h2->SetTitle("Average Row vs Y Position Plus");

		TCanvas* c= new TCanvas("c","",1200,600);
		c->Divide(2,1);
		c->cd(1);
		h1->Draw("colz");
		c->cd(2);
		h2->Draw("colz");
		h1->Write();
		h2->Write();
		c->SaveAs("Results/AllPossible.png");

	}

	if(debug == 2 || debug==1)
	{
		TH2D * ClusRow = new TH2D("ClusRow","",80,-0.5,7.5,80,-0.5,7.5);
		TH2D * ClusCol = new TH2D("ClusCol","",80,-0.5,7.5,80,-0.5,7.5);
		t->Project("ClusRow","clus_5x5_prod.max_row:clus_5x5_prod.average_row","good_e");
		t->Project("ClusCol","clus_5x5_prod.max_col:clus_5x5_prod.average_col","good_e");

		TCanvas* c= new TCanvas("c","",1200,600);
		c->Divide(2,1);
		c->cd(1);
		ClusRow->GetXaxis()->SetTitle("clus_5x5_prod.average_row");
		ClusRow->GetYaxis()->SetTitle("clus_5x5_prod.max_row");
		ClusRow->SetTitle("clus_5x5_prod.max_row vs clus_5x5_prod.average_row");
		ClusRow->Draw("COLZ");
		c->cd(2);
		ClusCol->GetXaxis()->SetTitle("clus_5x5_prod.average_col");
		ClusCol->GetYaxis()->SetTitle("clus_5x5_prod.max_col");
		ClusCol->SetTitle("clus_5x5_prod.max_col vs clus_5x5_prod.average_col");
		ClusCol->Draw("COLZ");

		ClusRow->Write();
		ClusCol->Write();

		c->SaveAs("Results/HVCorrelations.png");


	}

	fout2->Close();

}
