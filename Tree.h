//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  2 19:14:50 2018 by ROOT version 5.34/36
// from TTree T/T
// found on file: /phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root
//////////////////////////////////////////////////////////

#ifndef Tree_h
#define Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //Proto4ShowerCalib::Eval_Run *info;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           run;
   Int_t           event;
   Float_t         beam_mom;
   Int_t           hodo_h;
   Int_t           hodo_v;
   Float_t         C2_sum;
   Float_t         sum_energy_T;
   Float_t         EoP;
   Bool_t          valid_hodo_v;
   Bool_t          valid_hodo_h;
   Bool_t          trigger_veto_pass;
   Bool_t          good_temp;
   Bool_t          good_e;
   Bool_t          good_data;
   Float_t         truth_y;
   Float_t         truth_z;
   Float_t         beam_2CH_mm;
   Float_t         beam_2CV_mm;
/*	
   //Proto4ShowerCalib::Eval_Cluster *clus_3x3_raw;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_5x5_raw;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_3x3_prod;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_5x5_prod;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_3x3_temp;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_5x5_temp;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_3x3_recalib;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
 //Proto4ShowerCalib::Eval_Cluster *clus_5x5_recalib;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           max_col;
   Int_t           max_row;
   Float_t         average_col;
   Float_t         average_row;
   Float_t         sum_E;
*/
   // List of branches
   TBranch        *b_info_fUniqueID;   //!
   TBranch        *b_info_fBits;   //!
   TBranch        *b_info_run;   //!
   TBranch        *b_info_event;   //!
   TBranch        *b_info_beam_mom;   //!
   TBranch        *b_info_hodo_h;   //!
   TBranch        *b_info_hodo_v;   //!
   TBranch        *b_info_C2_sum;   //!
   TBranch        *b_info_sum_energy_T;   //!
   TBranch        *b_info_EoP;   //!
   TBranch        *b_info_valid_hodo_v;   //!
   TBranch        *b_info_valid_hodo_h;   //!
   TBranch        *b_info_trigger_veto_pass;   //!
   TBranch        *b_info_good_temp;   //!
   TBranch        *b_info_good_e;   //!
   TBranch        *b_info_good_data;   //!
   TBranch        *b_info_truth_y;   //!
   TBranch        *b_info_truth_z;   //!
   TBranch        *b_info_beam_2CH_mm;   //!
   TBranch        *b_info_beam_2CV_mm;   //!
   TBranch        *b_clus_3x3_raw_fUniqueID;   //!
   TBranch        *b_clus_3x3_raw_fBits;   //!
   TBranch        *b_clus_3x3_raw_max_col;   //!
   TBranch        *b_clus_3x3_raw_max_row;   //!
   TBranch        *b_clus_3x3_raw_average_col;   //!
   TBranch        *b_clus_3x3_raw_average_row;   //!
   TBranch        *b_clus_3x3_raw_sum_E;   //!
   TBranch        *b_clus_5x5_raw_fUniqueID;   //!
   TBranch        *b_clus_5x5_raw_fBits;   //!
   TBranch        *b_clus_5x5_raw_max_col;   //!
   TBranch        *b_clus_5x5_raw_max_row;   //!
   TBranch        *b_clus_5x5_raw_average_col;   //!
   TBranch        *b_clus_5x5_raw_average_row;   //!
   TBranch        *b_clus_5x5_raw_sum_E;   //!
   TBranch        *b_clus_3x3_prod_fUniqueID;   //!
   TBranch        *b_clus_3x3_prod_fBits;   //!
   TBranch        *b_clus_3x3_prod_max_col;   //!
   TBranch        *b_clus_3x3_prod_max_row;   //!
   TBranch        *b_clus_3x3_prod_average_col;   //!
   TBranch        *b_clus_3x3_prod_average_row;   //!
   TBranch        *b_clus_3x3_prod_sum_E;   //!
   TBranch        *b_clus_5x5_prod_fUniqueID;   //!
   TBranch        *b_clus_5x5_prod_fBits;   //!
   TBranch        *b_clus_5x5_prod_max_col;   //!
   TBranch        *b_clus_5x5_prod_max_row;   //!
   TBranch        *b_clus_5x5_prod_average_col;   //!
   TBranch        *b_clus_5x5_prod_average_row;   //!
   TBranch        *b_clus_5x5_prod_sum_E;   //!
   TBranch        *b_clus_3x3_temp_fUniqueID;   //!
   TBranch        *b_clus_3x3_temp_fBits;   //!
   TBranch        *b_clus_3x3_temp_max_col;   //!
   TBranch        *b_clus_3x3_temp_max_row;   //!
   TBranch        *b_clus_3x3_temp_average_col;   //!
   TBranch        *b_clus_3x3_temp_average_row;   //!
   TBranch        *b_clus_3x3_temp_sum_E;   //!
   TBranch        *b_clus_5x5_temp_fUniqueID;   //!
   TBranch        *b_clus_5x5_temp_fBits;   //!
   TBranch        *b_clus_5x5_temp_max_col;   //!
   TBranch        *b_clus_5x5_temp_max_row;   //!
   TBranch        *b_clus_5x5_temp_average_col;   //!
   TBranch        *b_clus_5x5_temp_average_row;   //!
   TBranch        *b_clus_5x5_temp_sum_E;   //!
   TBranch        *b_clus_3x3_recalib_fUniqueID;   //!
   TBranch        *b_clus_3x3_recalib_fBits;   //!
   TBranch        *b_clus_3x3_recalib_max_col;   //!
   TBranch        *b_clus_3x3_recalib_max_row;   //!
   TBranch        *b_clus_3x3_recalib_average_col;   //!
   TBranch        *b_clus_3x3_recalib_average_row;   //!
   TBranch        *b_clus_3x3_recalib_sum_E;   //!
   TBranch        *b_clus_5x5_recalib_fUniqueID;   //!
   TBranch        *b_clus_5x5_recalib_fBits;   //!
   TBranch        *b_clus_5x5_recalib_max_col;   //!
   TBranch        *b_clus_5x5_recalib_max_row;   //!
   TBranch        *b_clus_5x5_recalib_average_col;   //!
   TBranch        *b_clus_5x5_recalib_average_row;   //!
   TBranch        *b_clus_5x5_recalib_sum_E;   //!

   Tree(TTree *tree=0);
   virtual ~Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Tree_cxx
Tree::Tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/phenix/u/jinhuang/links/sPHENIX_work/Prototype_2018/ShowerCalib_tilted/dst.lst_EMCalCalib.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

Tree::~Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_info_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_info_fBits);
   fChain->SetBranchAddress("run", &run, &b_info_run);
   fChain->SetBranchAddress("event", &event, &b_info_event);
   fChain->SetBranchAddress("beam_mom", &beam_mom, &b_info_beam_mom);
   fChain->SetBranchAddress("hodo_h", &hodo_h, &b_info_hodo_h);
   fChain->SetBranchAddress("hodo_v", &hodo_v, &b_info_hodo_v);
   fChain->SetBranchAddress("C2_sum", &C2_sum, &b_info_C2_sum);
   fChain->SetBranchAddress("sum_energy_T", &sum_energy_T, &b_info_sum_energy_T);
   fChain->SetBranchAddress("EoP", &EoP, &b_info_EoP);
   fChain->SetBranchAddress("valid_hodo_v", &valid_hodo_v, &b_info_valid_hodo_v);
   fChain->SetBranchAddress("valid_hodo_h", &valid_hodo_h, &b_info_valid_hodo_h);
   fChain->SetBranchAddress("trigger_veto_pass", &trigger_veto_pass, &b_info_trigger_veto_pass);
   fChain->SetBranchAddress("good_temp", &good_temp, &b_info_good_temp);
   fChain->SetBranchAddress("good_e", &good_e, &b_info_good_e);
   fChain->SetBranchAddress("good_data", &good_data, &b_info_good_data);
   fChain->SetBranchAddress("truth_y", &truth_y, &b_info_truth_y);
   fChain->SetBranchAddress("truth_z", &truth_z, &b_info_truth_z);
   fChain->SetBranchAddress("beam_2CH_mm", &beam_2CH_mm, &b_info_beam_2CH_mm);
   fChain->SetBranchAddress("beam_2CV_mm", &beam_2CV_mm, &b_info_beam_2CV_mm);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_3x3_raw_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_3x3_raw_fBits);
   fChain->SetBranchAddress("max_col", &max_col, &b_clus_3x3_raw_max_col);
   fChain->SetBranchAddress("max_row", &max_row, &b_clus_3x3_raw_max_row);
   fChain->SetBranchAddress("average_col", &average_col, &b_clus_3x3_raw_average_col);
   fChain->SetBranchAddress("average_row", &average_row, &b_clus_3x3_raw_average_row);
   fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_3x3_raw_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_5x5_raw_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_5x5_raw_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_5x5_raw_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_5x5_raw_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_5x5_raw_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_5x5_raw_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_5x5_raw_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_3x3_prod_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_3x3_prod_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_3x3_prod_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_3x3_prod_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_3x3_prod_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_3x3_prod_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_3x3_prod_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_5x5_prod_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_5x5_prod_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_5x5_prod_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_5x5_prod_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_5x5_prod_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_5x5_prod_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_5x5_prod_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_3x3_temp_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_3x3_temp_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_3x3_temp_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_3x3_temp_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_3x3_temp_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_3x3_temp_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_3x3_temp_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_5x5_temp_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_5x5_temp_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_5x5_temp_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_5x5_temp_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_5x5_temp_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_5x5_temp_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_5x5_temp_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_3x3_recalib_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_3x3_recalib_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_3x3_recalib_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_3x3_recalib_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_3x3_recalib_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_3x3_recalib_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_3x3_recalib_sum_E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_clus_5x5_recalib_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_clus_5x5_recalib_fBits);
//    fChain->SetBranchAddress("max_col", &max_col, &b_clus_5x5_recalib_max_col);
//    fChain->SetBranchAddress("max_row", &max_row, &b_clus_5x5_recalib_max_row);
//    fChain->SetBranchAddress("average_col", &average_col, &b_clus_5x5_recalib_average_col);
//    fChain->SetBranchAddress("average_row", &average_row, &b_clus_5x5_recalib_average_row);
//    fChain->SetBranchAddress("sum_E", &sum_E, &b_clus_5x5_recalib_sum_E);
   Notify();
}

Bool_t Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Tree_cxx
