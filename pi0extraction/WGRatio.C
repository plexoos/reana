void WGRatio(){

	Bool_t verbose= false;
	const n = 30;
	ifstream bbc;
	ifstream ert;
	ifstream ratio;
	ofstream combined; 

 char path[500];
 sprintf (path,"output_plots/txt/");

 TFile *output_root = new TFile("output_plots/root/CombinedPlot_BBCpERT.root", "RECREATE");
 
 char filename[100];

 // This normaization is obtained from comparing corrected Pi0 with with NN's.
 // Then it is used to boostrap ERT. 

 double normalization_ERT=1;
 double normalization_ERT=1.505/0.963;

 double normalization_MB	= 1;
 const int NCE				= 5;
 const int NPID				= 2;
 const int NSEC				= 2;
 const int NTOF				= 2;
 const int NPT_UEB			= 28;

 double co_pt=6.5;//change over pt

 double ptl_UEB[NPT_UEB+1]; //28 itervals. [i,i+1] are the 28 intervals. so 29 numbers
 for(int i=0;i<NPT_UEB+1;i++) {
   if(i<21) ptl_UEB[i]=i*0.5;
   else if(i<27)  ptl_UEB[i]	= 10+(i-20)*2.0;
   else if(i==27) ptl_UEB[i]	= 25.0;
   else if(i==28) ptl_UEB[i]	= 30.0;
 }


 int startCent[NCE] = {00, 20, 40, 60, 00}; // lower bound on centrality based binning
 int stopCent[NCE]  = {20, 40, 60, 88, 88}; // upper bound on centrality based binning

 TLine *line1 = new TLine(co_pt,1e-12,co_pt,1); 
 line1->SetLineColor(kBlue);
 line1->SetLineStyle(2);

 char pid[NPID][10]={"noPID","Chi2"};
 char sector [NSEC][10] = {"PbSc", "PbGl"};
 char tof[NTOF][10]={"5ns", "3Sig"}; 
 
 TLegend *legend;

 for(int isec=0; isec<NSEC-1; isec++)
   {
     for(int iTOF=1; iTOF<NTOF; iTOF++)
       {
	 for (int icent =4; icent<NCE; icent++)
	   {
	    
	     for (int iPID =1 ; iPID<NPID; iPID++)
	       {
	
	     	 
		 sprintf(filename, "%s_%dCC%d_%s_%s",sector[isec],startCent[icent], stopCent[icent],pid[iPID],tof[iTOF]);
		 // cout<<"\n\n"<<filename;
		 char bbc_file[500];
		 sprintf(bbc_file, "%s/scaledUEB_rawPi0_MB_%s.txt", path,filename);
		 cout<<"\n\n"<<bbc_file;
		 bbc.open(bbc_file);

		 char ert_file[500];
		 sprintf(ert_file, "%s/scaledUEB_rawPi0_ERT_%s.txt", path,filename);	
		 ert.open(ert_file);

		 char ratio_file[500];
		 sprintf (ratio_file,"output_plots/txt/ratio_%s.txt",filename);
		 ratio.open(ratio_file);

		 char combined_file[500];
		 sprintf (combined_file,"output_plots/txt/scaledUEB_rawPi0_BBCpERT_%s.txt",filename);
		 TH1D *pi0Spectra = new TH1D(Form("BBCpERT_%s",filename),Form("BBCpERT_%s",filename),NPT_UEB,ptl_UEB);
		 combined.open(combined_file);

		  double pt_bbc[n];
		  double pt_err[n];
		  double yield_bbc[n];
		  double yield_err_bbc[n];
		  
		  double pt_ert[n];
		  double yield_ert[n];
		  double yield_err_ert[n];
		  
		  double pt,y, ye;//y for yield and ye for yield error.
		  int i=0;
		  for (int a=0; a<30; a++)
		    {
		      pt_bbc[a]=0;
		      pt_err[a]=0;
		      yield_bbc[a]=0;
		      yield_err_bbc[a]=0;
		  
		      pt_ert[a]=0;
		      yield_ert[a]=0;
		      yield_err_ert[a]=0;	 

		    }
		 
		  while(bbc>>pt>>y>>ye)
		    {
		      if(verbose)
			cout<<"\n BBC file opened";
		      pt_bbc[i]=pt;
		      yield_bbc[i]=y/normalization_MB;
		      yield_err_bbc[i]=ye/normalization_MB;     
		      i++;
		    }
		  int j=0;
		  while(ert>>pt>>y>>ye)
		    {
		      if(verbose)
			cout<<"\n ERT file opened";
		      pt_ert[j]=pt;
		      pt_err[j]=0;
		      yield_ert[j]=y/normalization_ERT;
		      yield_err_ert[j]=ye/normalization_ERT;     
		      j++;
		    }
		  
		  
		  
		  TGraphErrors*gr1 = new TGraphErrors(n,pt_bbc,yield_bbc,pt_err,yield_err_bbc);
		  TGraphErrors*gr2 = new TGraphErrors(n,pt_ert,yield_ert,pt_err,yield_err_ert);
		  
		  
		  // Define the Canvas
		  TCanvas *c = new TCanvas(Form("GM_%s",filename), Form("GM_%s",filename),92,50,544,895);
		  c->Divide(1,2);
		  c->cd(1);
		  TH1 *htemp = c->DrawFrame(0,1e-12,25,1);
		  line1->Draw();
		  //  htemp->SetTitle(Form("RawYield_%s",filename));
		  htemp->GetXaxis()->SetTitle("P_{t} (GeV/c)");
		  
		  htemp->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{dN}{dp_{t}} (1/GeV)");
		  htemp->GetXaxis()->SetLabelFont(42);
		  htemp->GetXaxis()->SetLabelSize(0.035);
		  htemp->GetXaxis()->SetTitleSize(0.035);
		  htemp->GetXaxis()->SetTitleFont(42);
		  htemp->GetYaxis()->SetNdivisions(505);
		  htemp->GetYaxis()->SetLabelFont(42);
		  htemp->GetYaxis()->SetTitleOffset(1.4);
  
 
		  gPad->SetLogy();
		  
		  gPad->Range(-4.475309,-12.46094,28.30247,1.761719);
		  gPad->SetLeftMargin(0.1365348);
		  gPad->SetTopMargin(0.1238671);
		  
		  gr1->Draw("P");               
		  gr2->Draw("P,same");   

		  legend = new TLegend(0.5,0.7,0.98,0.9);
		  legend->AddEntry("gr1","BBCLL1(>0 tubes) narrowvtx","lep");
		  legend->AddEntry("gr2","ERT4x4b trigger","lep");
		  legend->Draw();
		   
		  
		  // h1 settings
		  
		  gr1->SetLineColor(4);
		  gr1->SetMarkerColor(1);
		  gr1->SetMarkerStyle(20);
		  gr1->SetMarkerSize(1);
		  
		  
		  // h2 settings
		  gr2->SetMarkerColor(kRed);
		  gr2->SetMarkerStyle(20);
		  gr2->SetMarkerSize(1);

		  bbc.close();
		  ert.close(); 
		 
		  double pt_c[n]; //c for combined
		  double yield_c[n];
		  double yield_err_c[n];
		 

		  for (int l=0; l<j;l++)
		    {
		      pt_c[l]=pt_ert[l];
		      if(pt_ert[l]<co_pt)
			{
			  if (yield_bbc[l]>=0)
			    {
			      yield_c[l]=yield_bbc[l];
			      yield_err_c[l]= yield_err_bbc[l];
			    }
			  else
			    {
			      yield_c[l]=0;
			      yield_err_c[l]= 0;
			    }
			}
		      else
			{
			  if(yield_ert[l]>=0)
			    {
			      yield_c[l]=yield_ert[l];
			      yield_err_c[l]= yield_err_ert[l];
			    }
			  else
			    {
			      yield_c[l]=0;
			      yield_err_c[l]= 0;
			    }
			}
		      
		      if (verbose)
			cout<<pt_c[l]<<"\t"<<yield_c[l]<<"\t"<<yield_err_c[l]<<endl;
		      pi0Spectra->Fill(pt_c[l],yield_c[l]);
		      combined<<pt_c[l]<<"\t"<<yield_c[l]<<"\t"<<yield_err_c[l]<<endl;
		    }
		  combined.close(); 
		  c->cd(2);
		  TH1 *htemp1 = c->DrawFrame(0,1e-12,25,1);
		  //line1->Draw();
		  //  htemp1->SetTitle(Form("CombinedRawYield_%s",filename));
		  htemp1->GetXaxis()->SetTitle("P_{t} (GeV/c)");
		  htemp1->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{dN}{dp_{t}} (1/GeV)");
		  htemp1->GetXaxis()->SetLabelFont(42);
		  htemp1->GetXaxis()->SetLabelSize(0.035);
		  htemp1->GetXaxis()->SetTitleSize(0.035);
		  htemp1->GetXaxis()->SetTitleFont(42);
		  htemp1->GetYaxis()->SetNdivisions(505);
		  htemp1->GetYaxis()->SetLabelFont(42);
		  htemp1->GetYaxis()->SetTitleOffset(1.4);
  
  
		  gPad->SetLogy();
		  
		  gPad->Range(-4.475309,-12.46094,28.30247,1.761719);
		  gPad->SetLeftMargin(0.1365348);
		  gPad->SetTopMargin(0.1238671);
		  
		 

		  TGraphErrors*gr3 = new TGraphErrors(n,pt_c,yield_c,pt_err,yield_err_c);
		  gr3->Draw("*");
		  gr3->SetMarkerColor(kRed);
		  gr3->SetMarkerStyle(20);
		  gr3->SetMarkerSize(1);
		  // pi0Spectra->Draw();

		  output_root->cd();
		  c->Write();
		  pi0Spectra->Write();
		  if (iPID==(NPID-1)&&icent==(NCE-1)&&iTOF==(NTOF-1))
		    c->Print(Form("output_plots/pdf/%s.pdf)", sector[isec]));
		  else
		    c->Print(Form("output_plots/pdf/%s.pdf(", sector[isec]));
		 

	       }//end of PID loop
	   }// end of centrality loop
	   
	}//end of TOF loop
      
    }//end of sector loop
 
 output_root->Close();
}//end of the void function
