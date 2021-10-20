void generationRM_Pi0(){

  TFile *input_root = new TFile ("sim_Pi0Histogram/EmbedPi0dAu.root","READ");
 TFile *output_root = new TFile("Pion_RM.root", "RECREATE");
 const int NPT=60;
 const int NCE = 5;
 const int NPID = 3;
 const int NSEC =2;
 
 double ptl[NPT+1];//28 itervals. [i,i+1] are the 28 intervals. so 29 numbers
 for(int i=0;i<NPT+1;i++) {
   ptl[i]=i*0.5;
 }
 
 
 int startCent[NCE] = {00, 20, 40, 60, 00}; //lower bound on centrality based binning
 int stopCent[NCE]  = {20, 40, 60, 88, 88};//upper bound on centrality based binning
 
 
 
 char pid[NPID][10]={"noPID","Chi2","Stoch"};
 char sector [NSEC][10] = {"PbSc", "PbGl"};
 char buffer1[100];
 char buffer2[100];

 TH1D *generatedVpt[NCE];
 TH1D *bufferVpt;
 TH2D *vptVSptecore[NCE][NPID][NSEC];
 TH2D *RM_Matrix[NCE][NPID][NSEC];
 
 int rebin_pt[60];
 double ptcenter[60];
 for (int icent =0 ; icent<NCE; icent++)
    {
       sprintf(buffer2, "NoWeightInputPi0_Vpt_CC%d", icent);
      //sprintf(buffer2, "WeightInputPi0_Vpt_CC%d", icent);
      generatedVpt[icent]= (TH1D*)input_root->Get(buffer2);
           // generatedVpt[icent]->Draw();
      for (int iPID =1 ; iPID<2; iPID++)
	{
	  for(int isec=0; isec<1; isec++)
	    {
	      sprintf (buffer1, "h2dpTecoreVsVpT_CC%d_PID%d_%s",icent,iPID,sector[isec]);
	      
	      vptVSptecore[icent][iPID][isec]= (TH2D*)input_root->Get(buffer1);
	      vptVSptecore[icent][iPID][isec]->Sumw2();
	      sprintf (buffer1, "RM_%dCC%d_%s_%s",startCent[icent], stopCent[icent],pid[iPID],sector[isec]);
	      RM_Matrix[icent][iPID][isec] = new TH2D(buffer1, buffer1,NPT, ptl, NPT, ptl );
	      
	      for (int i=1; i<NPT+1; i++)
		{
		  
		  for (int j=1; j<NPT+1; j++)

		    {
		      
		      //	cout<<"\n"<<vptVSptecore[icent][iPID][isec]->GetBinContent(i,j);
		      //cout<<"\t"<<generatedVpt[icent]->GetBinContent(i);
		      if (generatedVpt[icent]->GetBinContent(i)!=0)
			{
			  double x =  vptVSptecore[icent][iPID][isec]->GetXaxis()->GetBinCenter(i);
			  double y =  vptVSptecore[icent][iPID][isec]->GetYaxis()->GetBinCenter(j);
			  
			  if (y<x+3)
			    {
			      // cout<<"\n X value "<<x<<"\t"<<y;
			      double value = vptVSptecore[icent][iPID][isec]->GetBinContent(i,j)/(generatedVpt[icent]->GetBinContent(i));
			      double err = TMath::Sqrt(vptVSptecore[icent][iPID][isec]->GetBinContent(i,j))/(generatedVpt[icent]->GetBinContent(i));
			    }
			  else
			    double value=0;
			  

			  //	  double value = vptVSptecore[icent][iPID][isec]->GetBinContent(i,j)/(generatedVpt[icent]->GetBinContent(i));
			  //double err = TMath::Sqrt(vptVSptecore[icent][iPID][isec]->GetBinContent(i,j))/(generatedVpt[icent]->GetBinContent(i));


			}
		      else 
			double value=0;
		      // RM_Matrix[icent][iPID][isec]->Sumw2(); 
		      RM_Matrix[icent][iPID][isec]->SetBinContent(i,j,value);
		      RM_Matrix[icent][iPID][isec]->SetBinError(i,j,err); 
		    }		  
		}// end of Pt binning
	      char buffer3[20];
	      //sprintf(buffer3, "TEXT");
	      output_root->cd();
	      RM_Matrix[icent][iPID][isec]->Write();
	      sprintf(buffer3, "colz");
	      
	      sprintf (buffer1, "CombinedPlot_%dCC%d_PID%d_%s",startCent[icent],stopCent[icent],iPID,sector[isec]);	      
	      TCanvas *c1 = new TCanvas(buffer1, buffer1); 
	     
	      gStyle->SetOptStat(0);
	      c1->Divide(3,1);
	      c1->cd(1);
	      vptVSptecore[icent][iPID][isec]->Draw(buffer3);
	      c1->cd(2);
	      sprintf (buffer1, "NumberOfGeneratedPions");	      
	      generatedVpt[icent]->Draw(buffer3);
	      c1->cd(3);
	      RM_Matrix[icent][iPID][isec]->Draw(buffer3);

	      if (strcmp(buffer3, "TEXT")==0)
		{

		  vptVSptecore[icent][iPID][isec]->GetXaxis()->SetRangeUser(10,15);
		  vptVSptecore[icent][iPID][isec]->GetYaxis()->SetRangeUser(10,15);
		  generatedVpt[icent]->GetXaxis()->SetRangeUser(10,15);
		  RM_Matrix[icent][iPID][isec]->GetXaxis()->SetRangeUser(10,15);
		  RM_Matrix[icent][iPID][isec]->GetYaxis()->SetRangeUser(10,15);
		}//end of if condition for draw options
	      
	      vptVSptecore[icent][iPID][isec]->GetXaxis()->SetTitle("generated pi0 pt [GeV]");
	      vptVSptecore[icent][iPID][isec]->GetYaxis()->SetTitle("measured pi0 pt [GeV]");
	      vptVSptecore[icent][iPID][isec]->GetYaxis()->SetTitleOffset(1.20);
	      vptVSptecore[icent][iPID][isec]->GetXaxis()->SetTitleOffset(1.20);
	      vptVSptecore[icent][iPID][isec]->SetTitle("PbSc_0CC88_noPID");
	      //vptVSptecore[icent][iPID][isec]->GetZaxis()->SetMaxDigits(3);
	      TGaxis::SetMaxDigits(3);
	      generatedVpt[icent]->GetXaxis()->SetTitle("generated pi0 pt [GeV]");
	      generatedVpt[icent]->GetYaxis()->SetTitle("Number of pi0");
	      generatedVpt[icent]->SetTitle("Number of pi0 generated");
	      RM_Matrix[icent][iPID][isec]->GetXaxis()->SetTitle(" generated pi0 pt[GeV]");
	      RM_Matrix[icent][iPID][isec]->GetYaxis()->SetTitle("measured pi0 pt [GeV]");
	      RM_Matrix[icent][iPID][isec]->SetTitle("RM_PbSc_0CC88_noPID");
	      RM_Matrix[icent][iPID][isec]->GetYaxis()->SetTitleOffset(1.20);
	      RM_Matrix[icent][iPID][isec]->GetXaxis()->SetTitleOffset(1.20);
	      output_root->cd();
	      c1->Write();
	     

	      if (iPID==(NPID-2)&&icent==(NCE-1))
		c1->Print(Form("%s.pdf)", sector[isec]));
	      else
		c1->Print(Form("%s.pdf(", sector[isec]));
		 

	    }//end of centrality loop
	}//end of PID loop

    }//end of centrality loop
 output_root->Close();
 input_root->Close();
}//end of void
