// --------------------------------------------------------------
// This macro is intended to be used with ROOT files prepared
// for the PHENIX Collaboration document titled
// "Neutral meson and photon ntuples: explanation and examples".
//
// NB. This version is written for ROOT6
//
// The files are: MBntup_gnt.root and ERTntup_gnt.root
// They contain the so-called "single cluster ntuple" referred to
// as ggntuple in the code below.
//
// The first argument selects a segment within the macro corresponding
// to plots and code snippets in the document. Valid choices are:
//
// position
// ecore
// chisq
//
// For exact semantics of each choice please see the PDF document
// --------------------------------------------------------------
void single_cluster_r6(TString option, TString MBntup="MBntup_gnt.root", TString ERTntup="ERTntup_gnt.root") {
  TFile* mb = new TFile(MBntup);
  TFile* ert = new TFile(ERTntup);

  TNtuple *gnt_mb  = (TNtuple*)mb->Get("gnt");
  TNtuple *gnt_ert = (TNtuple*)ert->Get("gnt");

  int W=1200;
  int H=400;

  if (option=="position") { // ############ position
    TCanvas *canvas1  = new TCanvas("canvas1",  "Cluster position", W, H);
    canvas1->Divide(2,1);

    canvas1->cd(1);
    gnt_mb->Draw("y:z","sec==1","colz");

    canvas1->cd(2);
    gnt_ert->Draw("y:z","sec==1","colz");
  }
  else if (option=="ecore") {  // ########### ecore
    TCanvas *canvas2  = new TCanvas("canvas2",  "ecent/ecore:ecore", 3*W/2, H);
    canvas2->Divide(3,1);

    canvas2->cd(1);
    gnt_mb->Draw("ecent/ecore:ecore","ecore<4.0","colz");

    canvas2->cd(2);
    gnt_mb->Draw("ecent/ecore:ecore","ecore<4.0 && chisq<3.0","colz");

    canvas2->cd(3);
    gnt_mb->Draw("ecent/ecore:ecore","ecore<4.0 && chisq>5.0","colz");
  }
  else if (option=="chisq") {  // ############ chisq
    TCanvas *canvas3  = new TCanvas("canvas3",  "chi*82 cut", W, H*2);
    canvas3->cd();
    canvas3->SetLogy();

    TH1D *h1 = new TH1D("h1","h1",100,0.0,50.0);
    TH1D *h2 = new TH1D("h2","h2",100,0.0,50.0);
    h1->SetLineWidth(2.0);
    h2->SetLineWidth(2.0);
    h2->SetLineColor(2);
    gnt_ert->Draw("pt>>h1","");
    gnt_ert->Draw("pt>>h2","chisq<3.0");
    h1->Draw();
    h2->Draw("same");    
  }
}
