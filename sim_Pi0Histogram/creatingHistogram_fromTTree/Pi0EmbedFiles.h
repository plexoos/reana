//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 23 15:38:31 2019 by ROOT version 5.34/36
// from TTree mpi0/pi0 data
// found on file: result00000.root
//////////////////////////////////////////////////////////

#ifndef Pi0EmbedFiles_h
#define Pi0EmbedFiles_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Pi0EmbedFiles {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         stat;
   Float_t         evn;
   Float_t         ntrk;
   Float_t         nclus;
   Float_t         ncclus;
   Float_t         trig;
   Float_t         zvtx;
   Float_t         cent;
   Float_t         vp;
   Float_t         vpt;
   Float_t         vpx;
   Float_t         vpy;
   Float_t         vpz;
   Float_t         vnd;
   Float_t         vasym;
   Float_t         vpid1;
   Float_t         vpid2;
   Float_t         vtrk0;
   Float_t         vte0;
   Float_t         vte1;
   Float_t         vte2;
   Float_t         vte3;
   Float_t         vte4;
   Float_t         vte5;
   Float_t         vte6;
   Float_t         vte7;
   Float_t         vtsec;
   Float_t         vtsece;
   Float_t         vtge0;
   Float_t         vtge1;
   Float_t         vtge2;
   Float_t         vtge3;
   Float_t         vtge4;
   Float_t         vtge5;
   Float_t         vtge6;
   Float_t         vtge7;
   Float_t         vtgsec;
   Float_t         vtgsece;
   Float_t         vce0;
   Float_t         vce1;
   Float_t         vce2;
   Float_t         vce3;
   Float_t         vce4;
   Float_t         vce5;
   Float_t         vce6;
   Float_t         vce7;
   Float_t         vcsec;
   Float_t         vcsece;
   Float_t         vcge0;
   Float_t         vcge1;
   Float_t         vcge2;
   Float_t         vcge3;
   Float_t         vcge4;
   Float_t         vcge5;
   Float_t         vcge6;
   Float_t         vcge7;
   Float_t         vcgsec;
   Float_t         vcgsece;
   Float_t         cid1;
   Float_t         edep1;
   Float_t         ecore1;
   Float_t         x1;
   Float_t         y1;
   Float_t         z1;
   Float_t         sec1;
   Float_t         chi21;
   Float_t         sto1;
   Float_t         ntwr1;
   Float_t         ntrk1;
   Float_t         dead1;
   Float_t         warn1;
   Float_t         trk11;
   Float_t         anclvl11;
   Float_t         pid11;
   Float_t         p11;
   Float_t         edep11;
   Float_t         x11;
   Float_t         y11;
   Float_t         z11;
   Float_t         impx11;
   Float_t         impy11;
   Float_t         impz11;
   Float_t         trk12;
   Float_t         anclvl12;
   Float_t         pid12;
   Float_t         p12;
   Float_t         edep12;
   Float_t         x12;
   Float_t         y12;
   Float_t         z12;
   Float_t         impx12;
   Float_t         impy12;
   Float_t         impz12;
   Float_t         cid2;
   Float_t         edep2;
   Float_t         ecore2;
   Float_t         x2;
   Float_t         y2;
   Float_t         z2;
   Float_t         sec2;
   Float_t         chi22;
   Float_t         sto2;
   Float_t         ntwr2;
   Float_t         ntrk2;
   Float_t         dead2;
   Float_t         warn2;
   Float_t         trk21;
   Float_t         anclvl21;
   Float_t         pid21;
   Float_t         p21;
   Float_t         edep21;
   Float_t         x21;
   Float_t         y21;
   Float_t         z21;
   Float_t         impx21;
   Float_t         impy21;
   Float_t         impz21;
   Float_t         trk22;
   Float_t         anclvl22;
   Float_t         pid22;
   Float_t         p22;
   Float_t         edep22;
   Float_t         x22;
   Float_t         y22;
   Float_t         z22;
   Float_t         impx22;
   Float_t         impy22;
   Float_t         impz22;
   Float_t         asym;
   Float_t         mass;
   Float_t         pt;
   Float_t         na81;
   Float_t         asymecore;
   Float_t         massecore;
   Float_t         ptecore;
   Float_t         na82;

   // List of branches
   TBranch        *b_stat;   //!
   TBranch        *b_evn;   //!
   TBranch        *b_ntrk;   //!
   TBranch        *b_nclus;   //!
   TBranch        *b_ncclus;   //!
   TBranch        *b_trig;   //!
   TBranch        *b_zvtx;   //!
   TBranch        *b_cent;   //!
   TBranch        *b_vp;   //!
   TBranch        *b_vpt;   //!
   TBranch        *b_vpx;   //!
   TBranch        *b_vpy;   //!
   TBranch        *b_vpz;   //!
   TBranch        *b_vnd;   //!
   TBranch        *b_vasym;   //!
   TBranch        *b_vpid1;   //!
   TBranch        *b_vpid2;   //!
   TBranch        *b_vtrk0;   //!
   TBranch        *b_vte0;   //!
   TBranch        *b_vte1;   //!
   TBranch        *b_vte2;   //!
   TBranch        *b_vte3;   //!
   TBranch        *b_vte4;   //!
   TBranch        *b_vte5;   //!
   TBranch        *b_vte6;   //!
   TBranch        *b_vte7;   //!
   TBranch        *b_vtsec;   //!
   TBranch        *b_vtsece;   //!
   TBranch        *b_vtge0;   //!
   TBranch        *b_vtge1;   //!
   TBranch        *b_vtge2;   //!
   TBranch        *b_vtge3;   //!
   TBranch        *b_vtge4;   //!
   TBranch        *b_vtge5;   //!
   TBranch        *b_vtge6;   //!
   TBranch        *b_vtge7;   //!
   TBranch        *b_vtgsec;   //!
   TBranch        *b_vtgsece;   //!
   TBranch        *b_vce0;   //!
   TBranch        *b_vce1;   //!
   TBranch        *b_vce2;   //!
   TBranch        *b_vce3;   //!
   TBranch        *b_vce4;   //!
   TBranch        *b_vce5;   //!
   TBranch        *b_vce6;   //!
   TBranch        *b_vce7;   //!
   TBranch        *b_vcsec;   //!
   TBranch        *b_vcsece;   //!
   TBranch        *b_vcge0;   //!
   TBranch        *b_vcge1;   //!
   TBranch        *b_vcge2;   //!
   TBranch        *b_vcge3;   //!
   TBranch        *b_vcge4;   //!
   TBranch        *b_vcge5;   //!
   TBranch        *b_vcge6;   //!
   TBranch        *b_vcge7;   //!
   TBranch        *b_vcgsec;   //!
   TBranch        *b_vcgsece;   //!
   TBranch        *b_cid1;   //!
   TBranch        *b_edep1;   //!
   TBranch        *b_ecore1;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_y1;   //!
   TBranch        *b_z1;   //!
   TBranch        *b_sec1;   //!
   TBranch        *b_chi21;   //!
   TBranch        *b_sto1;   //!
   TBranch        *b_ntwr1;   //!
   TBranch        *b_ntrk1;   //!
   TBranch        *b_dead1;   //!
   TBranch        *b_warn1;   //!
   TBranch        *b_trk11;   //!
   TBranch        *b_anclvl11;   //!
   TBranch        *b_pid11;   //!
   TBranch        *b_p11;   //!
   TBranch        *b_edep11;   //!
   TBranch        *b_x11;   //!
   TBranch        *b_y11;   //!
   TBranch        *b_z11;   //!
   TBranch        *b_impx11;   //!
   TBranch        *b_impy11;   //!
   TBranch        *b_impz11;   //!
   TBranch        *b_trk12;   //!
   TBranch        *b_anclvl12;   //!
   TBranch        *b_pid12;   //!
   TBranch        *b_p12;   //!
   TBranch        *b_edep12;   //!
   TBranch        *b_x12;   //!
   TBranch        *b_y12;   //!
   TBranch        *b_z12;   //!
   TBranch        *b_impx12;   //!
   TBranch        *b_impy12;   //!
   TBranch        *b_impz12;   //!
   TBranch        *b_cid2;   //!
   TBranch        *b_edep2;   //!
   TBranch        *b_ecore2;   //!
   TBranch        *b_x2;   //!
   TBranch        *b_y2;   //!
   TBranch        *b_z2;   //!
   TBranch        *b_sec2;   //!
   TBranch        *b_chi22;   //!
   TBranch        *b_sto2;   //!
   TBranch        *b_ntwr2;   //!
   TBranch        *b_ntrk2;   //!
   TBranch        *b_dead2;   //!
   TBranch        *b_warn2;   //!
   TBranch        *b_trk21;   //!
   TBranch        *b_anclvl21;   //!
   TBranch        *b_pid21;   //!
   TBranch        *b_p21;   //!
   TBranch        *b_edep21;   //!
   TBranch        *b_x21;   //!
   TBranch        *b_y21;   //!
   TBranch        *b_z21;   //!
   TBranch        *b_impx21;   //!
   TBranch        *b_impy21;   //!
   TBranch        *b_impz21;   //!
   TBranch        *b_trk22;   //!
   TBranch        *b_anclvl22;   //!
   TBranch        *b_pid22;   //!
   TBranch        *b_p22;   //!
   TBranch        *b_edep22;   //!
   TBranch        *b_x22;   //!
   TBranch        *b_y22;   //!
   TBranch        *b_z22;   //!
   TBranch        *b_impx22;   //!
   TBranch        *b_impy22;   //!
   TBranch        *b_impz22;   //!
   TBranch        *b_asym;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_na81;   //!
   TBranch        *b_asymecore;   //!
   TBranch        *b_massecore;   //!
   TBranch        *b_ptecore;   //!
   TBranch        *b_na82;   //!

   Pi0EmbedFiles(TTree *tree=0);
   virtual ~Pi0EmbedFiles();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Pi0EmbedFiles_cxx
Pi0EmbedFiles::Pi0EmbedFiles(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pi0_dAuMB.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pi0_dAuMB.root");
      }
      f->GetObject("mpi0",tree);

   }
   Init(tree);
}

Pi0EmbedFiles::~Pi0EmbedFiles()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Pi0EmbedFiles::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Pi0EmbedFiles::LoadTree(Long64_t entry)
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

void Pi0EmbedFiles::Init(TTree *tree)
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

   fChain->SetBranchAddress("stat", &stat, &b_stat);
   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("ntrk", &ntrk, &b_ntrk);
   fChain->SetBranchAddress("nclus", &nclus, &b_nclus);
   fChain->SetBranchAddress("ncclus", &ncclus, &b_ncclus);
   fChain->SetBranchAddress("trig", &trig, &b_trig);
   fChain->SetBranchAddress("zvtx", &zvtx, &b_zvtx);
   fChain->SetBranchAddress("cent", &cent, &b_cent);
   fChain->SetBranchAddress("vp", &vp, &b_vp);
   fChain->SetBranchAddress("vpt", &vpt, &b_vpt);
   fChain->SetBranchAddress("vpx", &vpx, &b_vpx);
   fChain->SetBranchAddress("vpy", &vpy, &b_vpy);
   fChain->SetBranchAddress("vpz", &vpz, &b_vpz);
   fChain->SetBranchAddress("vnd", &vnd, &b_vnd);
   fChain->SetBranchAddress("vasym", &vasym, &b_vasym);
   fChain->SetBranchAddress("vpid1", &vpid1, &b_vpid1);
   fChain->SetBranchAddress("vpid2", &vpid2, &b_vpid2);
   fChain->SetBranchAddress("vtrk0", &vtrk0, &b_vtrk0);
   fChain->SetBranchAddress("vte0", &vte0, &b_vte0);
   fChain->SetBranchAddress("vte1", &vte1, &b_vte1);
   fChain->SetBranchAddress("vte2", &vte2, &b_vte2);
   fChain->SetBranchAddress("vte3", &vte3, &b_vte3);
   fChain->SetBranchAddress("vte4", &vte4, &b_vte4);
   fChain->SetBranchAddress("vte5", &vte5, &b_vte5);
   fChain->SetBranchAddress("vte6", &vte6, &b_vte6);
   fChain->SetBranchAddress("vte7", &vte7, &b_vte7);
   fChain->SetBranchAddress("vtsec", &vtsec, &b_vtsec);
   fChain->SetBranchAddress("vtsece", &vtsece, &b_vtsece);
   fChain->SetBranchAddress("vtge0", &vtge0, &b_vtge0);
   fChain->SetBranchAddress("vtge1", &vtge1, &b_vtge1);
   fChain->SetBranchAddress("vtge2", &vtge2, &b_vtge2);
   fChain->SetBranchAddress("vtge3", &vtge3, &b_vtge3);
   fChain->SetBranchAddress("vtge4", &vtge4, &b_vtge4);
   fChain->SetBranchAddress("vtge5", &vtge5, &b_vtge5);
   fChain->SetBranchAddress("vtge6", &vtge6, &b_vtge6);
   fChain->SetBranchAddress("vtge7", &vtge7, &b_vtge7);
   fChain->SetBranchAddress("vtgsec", &vtgsec, &b_vtgsec);
   fChain->SetBranchAddress("vtgsece", &vtgsece, &b_vtgsece);
   fChain->SetBranchAddress("vce0", &vce0, &b_vce0);
   fChain->SetBranchAddress("vce1", &vce1, &b_vce1);
   fChain->SetBranchAddress("vce2", &vce2, &b_vce2);
   fChain->SetBranchAddress("vce3", &vce3, &b_vce3);
   fChain->SetBranchAddress("vce4", &vce4, &b_vce4);
   fChain->SetBranchAddress("vce5", &vce5, &b_vce5);
   fChain->SetBranchAddress("vce6", &vce6, &b_vce6);
   fChain->SetBranchAddress("vce7", &vce7, &b_vce7);
   fChain->SetBranchAddress("vcsec", &vcsec, &b_vcsec);
   fChain->SetBranchAddress("vcsece", &vcsece, &b_vcsece);
   fChain->SetBranchAddress("vcge0", &vcge0, &b_vcge0);
   fChain->SetBranchAddress("vcge1", &vcge1, &b_vcge1);
   fChain->SetBranchAddress("vcge2", &vcge2, &b_vcge2);
   fChain->SetBranchAddress("vcge3", &vcge3, &b_vcge3);
   fChain->SetBranchAddress("vcge4", &vcge4, &b_vcge4);
   fChain->SetBranchAddress("vcge5", &vcge5, &b_vcge5);
   fChain->SetBranchAddress("vcge6", &vcge6, &b_vcge6);
   fChain->SetBranchAddress("vcge7", &vcge7, &b_vcge7);
   fChain->SetBranchAddress("vcgsec", &vcgsec, &b_vcgsec);
   fChain->SetBranchAddress("vcgsece", &vcgsece, &b_vcgsece);
   fChain->SetBranchAddress("cid1", &cid1, &b_cid1);
   fChain->SetBranchAddress("edep1", &edep1, &b_edep1);
   fChain->SetBranchAddress("ecore1", &ecore1, &b_ecore1);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("y1", &y1, &b_y1);
   fChain->SetBranchAddress("z1", &z1, &b_z1);
   fChain->SetBranchAddress("sec1", &sec1, &b_sec1);
   fChain->SetBranchAddress("chi21", &chi21, &b_chi21);
   fChain->SetBranchAddress("sto1", &sto1, &b_sto1);
   fChain->SetBranchAddress("ntwr1", &ntwr1, &b_ntwr1);
   fChain->SetBranchAddress("ntrk1", &ntrk1, &b_ntrk1);
   fChain->SetBranchAddress("dead1", &dead1, &b_dead1);
   fChain->SetBranchAddress("warn1", &warn1, &b_warn1);
   fChain->SetBranchAddress("trk11", &trk11, &b_trk11);
   fChain->SetBranchAddress("anclvl11", &anclvl11, &b_anclvl11);
   fChain->SetBranchAddress("pid11", &pid11, &b_pid11);
   fChain->SetBranchAddress("p11", &p11, &b_p11);
   fChain->SetBranchAddress("edep11", &edep11, &b_edep11);
   fChain->SetBranchAddress("x11", &x11, &b_x11);
   fChain->SetBranchAddress("y11", &y11, &b_y11);
   fChain->SetBranchAddress("z11", &z11, &b_z11);
   fChain->SetBranchAddress("impx11", &impx11, &b_impx11);
   fChain->SetBranchAddress("impy11", &impy11, &b_impy11);
   fChain->SetBranchAddress("impz11", &impz11, &b_impz11);
   fChain->SetBranchAddress("trk12", &trk12, &b_trk12);
   fChain->SetBranchAddress("anclvl12", &anclvl12, &b_anclvl12);
   fChain->SetBranchAddress("pid12", &pid12, &b_pid12);
   fChain->SetBranchAddress("p12", &p12, &b_p12);
   fChain->SetBranchAddress("edep12", &edep12, &b_edep12);
   fChain->SetBranchAddress("x12", &x12, &b_x12);
   fChain->SetBranchAddress("y12", &y12, &b_y12);
   fChain->SetBranchAddress("z12", &z12, &b_z12);
   fChain->SetBranchAddress("impx12", &impx12, &b_impx12);
   fChain->SetBranchAddress("impy12", &impy12, &b_impy12);
   fChain->SetBranchAddress("impz12", &impz12, &b_impz12);
   fChain->SetBranchAddress("cid2", &cid2, &b_cid2);
   fChain->SetBranchAddress("edep2", &edep2, &b_edep2);
   fChain->SetBranchAddress("ecore2", &ecore2, &b_ecore2);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("y2", &y2, &b_y2);
   fChain->SetBranchAddress("z2", &z2, &b_z2);
   fChain->SetBranchAddress("sec2", &sec2, &b_sec2);
   fChain->SetBranchAddress("chi22", &chi22, &b_chi22);
   fChain->SetBranchAddress("sto2", &sto2, &b_sto2);
   fChain->SetBranchAddress("ntwr2", &ntwr2, &b_ntwr2);
   fChain->SetBranchAddress("ntrk2", &ntrk2, &b_ntrk2);
   fChain->SetBranchAddress("dead2", &dead2, &b_dead2);
   fChain->SetBranchAddress("warn2", &warn2, &b_warn2);
   fChain->SetBranchAddress("trk21", &trk21, &b_trk21);
   fChain->SetBranchAddress("anclvl21", &anclvl21, &b_anclvl21);
   fChain->SetBranchAddress("pid21", &pid21, &b_pid21);
   fChain->SetBranchAddress("p21", &p21, &b_p21);
   fChain->SetBranchAddress("edep21", &edep21, &b_edep21);
   fChain->SetBranchAddress("x21", &x21, &b_x21);
   fChain->SetBranchAddress("y21", &y21, &b_y21);
   fChain->SetBranchAddress("z21", &z21, &b_z21);
   fChain->SetBranchAddress("impx21", &impx21, &b_impx21);
   fChain->SetBranchAddress("impy21", &impy21, &b_impy21);
   fChain->SetBranchAddress("impz21", &impz21, &b_impz21);
   fChain->SetBranchAddress("trk22", &trk22, &b_trk22);
   fChain->SetBranchAddress("anclvl22", &anclvl22, &b_anclvl22);
   fChain->SetBranchAddress("pid22", &pid22, &b_pid22);
   fChain->SetBranchAddress("p22", &p22, &b_p22);
   fChain->SetBranchAddress("edep22", &edep22, &b_edep22);
   fChain->SetBranchAddress("x22", &x22, &b_x22);
   fChain->SetBranchAddress("y22", &y22, &b_y22);
   fChain->SetBranchAddress("z22", &z22, &b_z22);
   fChain->SetBranchAddress("impx22", &impx22, &b_impx22);
   fChain->SetBranchAddress("impy22", &impy22, &b_impy22);
   fChain->SetBranchAddress("impz22", &impz22, &b_impz22);
   fChain->SetBranchAddress("asym", &asym, &b_asym);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("na81", &na81, &b_na81);
   fChain->SetBranchAddress("asymecore", &asymecore, &b_asymecore);
   fChain->SetBranchAddress("massecore", &massecore, &b_massecore);
   fChain->SetBranchAddress("ptecore", &ptecore, &b_ptecore);
   fChain->SetBranchAddress("na82", &na82, &b_na82);
   Notify();
}

Bool_t Pi0EmbedFiles::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Pi0EmbedFiles::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Pi0EmbedFiles::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Pi0EmbedFiles_cxx
