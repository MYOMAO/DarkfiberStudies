#include "parameters.h"
#include <fstream>
#include <iostream>
#include "Tree.h"
#include "Variable.h"

void PosFix(){

	const int N = 1000;
//TFile *fin = new TFile("/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root");
TFile *fin = new TFile(InputFile.Data());

	TTree *t = (TTree *)fin->Get("T");
	int Nevents = t->GetEntries();
	
	const int NEvents = Nevents;

	std::ifstream infile;
	int runnumber[nFiles];
	double xpos[nFiles];
	double ypos[nFiles];

	infile.open(PositionFile.Data());

	for(int i = 0; i< nFiles; i++)
	{
		infile >>  runnumber[i] >> xpos[i] >> ypos[i];
		cout <<  runnumber[i] << "  " <<  xpos[i] << "   "  <<  ypos[i] << endl;
	}
t->SetMakeClass(1);	

//	t->SetBranchAddress("run", &run);

	Int_t run_fix;
	Float_t	beam_2CH_mm_fix;
	Float_t	beam_2CV_mm_fix;
//	t->Draw("info.run");
	Int_t run;
	t->SetBranchAddress("run",&run);




	TFile * fout = new TFile(PosFixOut.Data(),"RECREATE");
	fout->cd();
	TTree * RunxyFix = new TTree("RunxyFix","RunxyFix");
	RunxyFix->Branch("run_fix",&run_fix,"run_fix/I");
	RunxyFix->Branch("beam_2CH_mm_fix",&beam_2CH_mm_fix,"beam_2CH_mm_fix/F");
	RunxyFix->Branch("beam_2CV_mm_fix",&beam_2CV_mm_fix,"beam_2CV_mm_fix/F");


	int Exist;


	for(int i =0; i< NEvents; i++)
	{

		if(i%10000==0) cout << "Now Working on Event " << i << endl; 
		t->GetEntry(i);
//	if(run > 1)	cout << "i = " << i << "   run = " << run << endl;
		//Scan Runnumber/
		Exist = 0;
		for(int j =0; j< nFiles; j++)
		{
			if(run == runnumber[j])
			{
			run_fix = runnumber[j];
			beam_2CH_mm_fix = xpos[j];
			beam_2CV_mm_fix = ypos[j];
			Exist = 1;
			}
			
		}
			if(Exist == 1)	RunxyFix->Fill();
	}

	fout->Write();
	fout->Close();

}




