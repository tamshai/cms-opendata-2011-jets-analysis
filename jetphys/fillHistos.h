//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul  7 17:14:10 2016 by ROOT version 5.32/00
// from TTree ProcessedTree/ProcessedTree
// found on file: tuples0.root
//////////////////////////////////////////////////////////

#ifndef fillHistos_h
#define fillHistos_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <math.h> 

#include "TMath.h"
#include "TF1.h"
#include "TF2.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include <map>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <fstream>

#include "settings.h"
#include "basicHistos.h"
#include "runHistos.h"
#include "tools.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class fillHistos {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   static const UInt_t kMaxNjet = 100;
   static const UInt_t kMaxNtrg = 64;

   // Declaration of leaf variables
   UInt_t          njet;
   Float_t         jet_pt[kMaxNjet];   //[njet]
   Float_t         jet_eta[kMaxNjet];   //[njet]
   Float_t         jet_phi[kMaxNjet];   //[njet]
   Float_t         jet_E[kMaxNjet];   //[njet]
   Float_t         jet_y[kMaxNjet];  // NOTE: not included in the tuple!

   UInt_t          ngen;
   Float_t         gen_pt[kMaxNjet];   //[ngen]
   Float_t         gen_eta[kMaxNjet];   //[ngen]
   Float_t         gen_phi[kMaxNjet];   //[ngen]
   Float_t         gen_E[kMaxNjet];   //[ngen]

   Float_t         gen_y[kMaxNjet];  // NOTE: not included in the tuple!
   
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       event;
   UInt_t          ntrg;

   Bool_t          triggers[kMaxNtrg];   //[ntrg]
   vector<string>  *triggernames;
   UInt_t          prescales[kMaxNtrg];   //[ntrg]

   Float_t         mcweight;

   // List of branches
   TBranch        *b_njet;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!

   TBranch        *b_ngen;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_E;   //!

   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //

   TBranch        *b_ntrg;   //!
   TBranch        *b_triggers;   //!
   TBranch        *b_triggernames;   //!
   TBranch        *b_prescales;   //!

   TBranch        *b_mcweight;   //!

   fillHistos(TTree *tree=0);

   
   virtual ~fillHistos();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::ofstream *ferr;
   std::string _type;
   TFile * _outfile;
   std::map<std::string, std::vector<basicHistos*> > _histos;

   void initBasics(std::string name);
   void fillBasics(std::string name);
   void fillBasic(basicHistos *h);
   void writeBasics();
   void loadLumi(const std::string filename);
   

private:

   // Monte Carlo or Data
   bool _mc;
   bool _dt;

   // MC weights
   double _w, _w0;

   // Recorded luminosity by run and lumisection numbers
   std::map<int, std::map<int, float> > _lums;

   // Helper variable
   TLorentzVector p4;

};

#endif

#ifdef fillHistos_cxx
fillHistos::fillHistos(TTree *tree)
{
   // Reset output file pointer
   _outfile = NULL;

   Init(tree);
   Loop();
}

fillHistos::~fillHistos()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


Int_t fillHistos::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t fillHistos::LoadTree(Long64_t entry)
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

void fillHistos::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   triggernames = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;

   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   _type.assign(_jp_type);
   _dt = (_type=="DATA");
   _mc = !_dt;
   
   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);

   fChain->SetBranchAddress("ngen", &ngen, &b_ngen);
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_E", &gen_E, &b_gen_E);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);

   fChain->SetBranchAddress("ntrg", &ntrg, &b_ntrg);
   fChain->SetBranchAddress("triggers", triggers, &b_triggers);
   fChain->SetBranchAddress("triggernames", &triggernames, &b_triggernames);
   fChain->SetBranchAddress("prescales", prescales, &b_prescales);

   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
   Notify();
}

Bool_t fillHistos::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fillHistos::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

#endif // #ifdef fillHistos_cxx
