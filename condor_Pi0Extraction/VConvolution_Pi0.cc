/**
The overall objective of this code is to get corrected Pi0 spectrum, given a raw Pi0 spectrum and a Response matrix from the simulation. 
The procedure used to obtain this is called "Unfolding by Folding". 

Procedure : take a starting vector (S1) (obtained as a Hagedorn fit to Run3 Pi0 data, multiply it with Response Matrix (RM), Rebin the vector to match the binning of raw Pi0 spectrum.  Compare point by point and obtain a ratio. Correct S1 by the ratio and d another iteation. 

In 5 iteration, it converges to the raw Pi0 spectrum. 

This will create a four panel Canvas. Panel 1 has the starting spectrum. Panel two has the RM and panel three has the rotated vector and the true data and panel 4 has a ratio plot

Errors are calculated in a different code. 
**/


void VConvolution_Pi0(){



  const int NPT_UEB=28;
  const int NPT_EB=60;
  const int NCE = 5;
  const int NPID = 3;
  const int NSEC =2;
  const int NTI =3;
  int startCent[NCE] = {00, 20, 40, 60, 00}; //lower bound on centrality based binning
  int stopCent[NCE]  = {20, 40, 60, 88, 88};//upper bound on centrality based binning
 
  char pid[NPID][10]={"noPID","Chi2","Stoch"};
 char sector [NSEC][10] = {"PbSc", "PbGl"};
 char buffer1[100];
 char buffer2[100];




 TH1D *s_EB[NTI]; // starting equal distribution
 TH1D *s_UEB[NTI]; 
 TH1D *s_UEB_RBN[NTI]; 

 TH1D *f_EB[NTI];
 TH1D *f_UEB[NTI];
 TH1D* f_UEB_RBN[NTI];//rebinned and normalised

double bufferRatio_UEB[NTI+1][NPT_UEB];
double bufferRatio_EB[NTI+1][NPT_EB];
 
for(int iti =0 ; iti<NTI+1; iti++)
   {
     for (int l=0; l<NPT_UEB; l++) //loop over pt
       bufferRatio_UEB[iti][l] = 1; // the first iteration of yield will be 1. (as we don't know the ratio before we obtain the ratio..)  
     for (l=0; l<NPT_EB; l++) //loop over pt
       bufferRatio_EB[iti][l] = 1; // the first iteration of yield will be 1. (as we don't know the ratio before we obtain the ratio..) 
   }


 double ptl_UEB[NPT_UEB+1];//28 itervals. [i,i+1] are the 28 intervals. so 29 numbers
 for(int i=0;i<NPT_UEB+1;i++) {
   if(i<21) ptl_UEB[i]=i*0.5;
   else if(i<27) ptl_UEB[i]=10+(i-20)*2.0;
   else if(i==27) ptl_UEB[i] = 25.0;
   else if(i==28) ptl_UEB[i] = 30.0;
   
 }
 
 
 double pt_bW_UEB[NPT_UEB];
 double pt_bM_UEB[NPT_UEB];
 for(int i=0; i<NPT_UEB; i++)
   {
     pt_bW_UEB[i]=ptl_UEB[i+1]-ptl_UEB[i];
     pt_bM_UEB[i]=(ptl_UEB[i]+ptl_UEB[i+1])/2;
   }


	     
 double ptl_EB[NPT_EB+1];
 for(int i=0;i<NPT_EB+1;i++) {
   ptl_EB[i]=i*0.5;
 }
 
 double pt_bW_EB[NPT_EB];
 double pt_bM_EB[NPT_EB];
 for(int i=0; i<NPT_EB; i++)
   {
     pt_bW_EB[i]=ptl_EB[i+1]-ptl_EB[i];
     pt_bM_EB[i]=(ptl_EB[i]+ptl_EB[i+1])/2;
   }
 
 
 

  
//************* Equal Binned vector **************** 

for (int icent =4; icent<NCE; icent++)
   {
     for (int iPID =1; iPID<2; iPID++)
       {
	 for(int isec=0; isec<1; isec++)
	   {

	     TFile *IR_EB = new TFile ("Pion_RM.root","READ");//Input root equal binning.
	     ifstream TH_EB; //trial Hagedorn equal binning
	     ofstream CS_EB; //Corrected Spectrum equal binned final iteration result from the convolution
	     ofstream CS_UEB; //Corrected Spectrum unequal binned final iteration result from the convolution
	     
	     TH2D *RM_EB;
	     double matrix_EB[NPT_EB][NPT_EB];
	     TH2 *start_EB;
	     
	     
	     TH_EB.open("inputTrialFunction_Pi0.txt");
	     double pt_EB[NPT_EB],yield_EB[NPT_EB];
	     double x,y,z;
	     TH1D *h_EB; // the histogram (you should set the number of bins, the title etc)
	     h_EB = new TH1D("", "",NPT_EB,ptl_EB);
	     
	     int i=0;
	     while(TH_EB>>x>>y>>z)
	       {
		 // cout<<"\n"<<x<<"\t"<<y;
		 pt_EB[i]=x;
		 yield_EB[i]=y;
		 h_EB->Fill(x,yield_EB[i]); 
		 i++;
		 
	       }
	     
	     TH_EB.close();
	     
	  	     
	     sprintf (buffer1, "RM_%dCC%d_%s_%s",startCent[icent], stopCent[icent],pid[iPID],sector[isec]);
	     RM_EB =(TH2D*) IR_EB->Get(buffer1);
	     
	     for (int i=0; i<NPT_EB; i++){ //gen for generated    
	       for (int j=0; j<NPT_EB; j++){//mea for measured
		 matrix_EB[i][j]=RM_EB->GetBinContent(i+1,j+1);
		 //	 if(j==1)
		 //cout<<"\n"<<matrix_EB[i][j];
	       }
	     }
	     
	    
	    

	     //******BBCpERT function that we draw as histogram *****
	    
	     ifstream bbc;
	     bbc.open(Form("output_plots/txt/scaledUEB_rawPi0_BBCpERT_%s_%dCC%d_%s_3Sig.txt", sector[isec], startCent[icent], stopCent[icent],pid[iPID]));
	     double pt_bbc[NPT_UEB];
	     double pt_err[NPT_UEB];
	     double yield_bbc[NPT_UEB];
	     double yield_err_bbc[NPT_UEB];
	     int i=0; 
	     double pt, y, ye;
	     for(int a=0; a<NPT_UEB; a++)
	       {
		 pt_bbc[a]=pt_err[a]=yield_bbc[a]=yield_err_bbc[a]=0;
	       }
	     
	     while(bbc>>pt>>y>>ye)
	       {
		 pt_bbc[i]=pt;
		 yield_bbc[i]=y;
		 yield_err_bbc[i]=ye; 
		 //cout<<"\n BBC opened";
		 //	 cout<<"\n"<<pt_bbc[i]<<"\t"<<yield_bbc[i];
		 i++;
	       }
	    
	     int numPtpoints_UEB=0;
	     int numPtpoints_EB=0;
	     //cout<<"\n The last pt bin"<<pt_bbc[i-1];
	       for (int k=0; k<NPT_UEB; k++)
		 {
		   if (pt_bM_UEB[k]<=pt_bbc[i-1])
		     numPtpoints_UEB++;
		 }
	       for (int k=0; k<NPT_EB; k++)
		 {
		   // if (pt_bM_EB[k]<=pt_bbc[i-1])
		   if (pt_bM_EB[k]<=ptl_UEB[i+1])
		   {
		     numPtpoints_EB++;
		     //cout<<"\n"<<icent<<"\t"<<pt_bM_EB[k]<<"\t"<<pt_bbc[i-1]<<"\t"<<ptl_UEB[i+1];
		     }
		 } 
	       // numPtpoints_EB+=3;
	     double yield_final[NPT_UEB];
	     double yield_err_final[NPT_UEB];
	     double yield_err_ratio[NPT_UEB];
	     TH1D *h_RawYield; // the histogram (you should set the number of bins, the title etc)
	     h_RawYield = new TH1D("equalBin", "equalBin",NPT_UEB,ptl_UEB);
	    
	     for(int i=0; i<NPT_UEB; i++)
	       {
		 for (int j=0; j<NPT_UEB; j++)
		   {
	
		     if (pt_bM_UEB[i]==pt_bbc[j])
		       {
			 yield_final[i]=yield_bbc[j];
			 yield_err_final[i]=yield_err_bbc[j];
			 yield_err_ratio[i]=yield_err_bbc[j]/yield_bbc[j];
			
			 break;
		       }
		     else
		       {
		       yield_final[i]=0;
		       yield_err_final[i]=0;
		     
		       }
		     
		   }//end of  j loop
		 h_RawYield->Fill(pt_bM_UEB[i],yield_final[i]);
		 h_RawYield->SetBinError(i+1,yield_err_final[i]);
		 //cout<<"\n"<<pt_bM_UEB[i]<<"\t"<<yield_final[i]<<"\t"<<yield_err_final[i];
	       }// end of i loop
		 
	     //****Calculating the Ratio***************************. 
	     for(int iti = 0; iti<NTI; iti++)
	       {
		 //cout<<"\n Iteration Number "<<iti;
		 for (i=1; i<NPT_UEB; i++)
		   {
		     for(j=1; j<NPT_EB; j++)
		       {
			 if (pt_bM_EB[j]<=ptl_UEB[i+1]&&pt_bM_EB[j]>ptl_UEB[i])
			   {
			     // cout<<"\n"<<ptl_UEB[i]<<"\t"<<pt_bM_EB[j]<<"\t"<<ptl_UEB[i+1];
			     bufferRatio_EB[iti][j]=bufferRatio_UEB[iti][i];
			   }
			 else
			   continue;
		       }//end of UEB loop
		   }//end of EB loop
		s_EB[iti] = new TH1D("V", "",NPT_EB,ptl_EB); 
		CS_EB.open(Form("output_plots/txt/scaledEB_corrPi0_BBCpERT_%s_%dCC%d_%s_3Sig.txt",sector[isec], startCent[icent], stopCent[icent],pid[iPID]));
		CS_UEB.open(Form("output_plots/txt/scaledUEB_corrPi0_BBCpERT_%s_%dCC%d_%s_3Sig.txt",sector[isec], startCent[icent], stopCent[icent],pid[iPID]));
		 for (i=1; i<numPtpoints_EB; i++)
		   {
		     if (bufferRatio_EB[iti][i]!=0)
		       
		       yield_EB[i]=yield_EB[i]*bufferRatio_EB[iti][i];
		     //  cout<<"\n"<<pt_EB[i]<<"\t"<<bufferRatio_EB[iti][i]<<"\t"<<yield_EB[i];
		     s_EB[iti]->Fill(pt_EB[i],yield_EB[i]); // ?
		    
		     CS_EB<<pt_EB[i]<<"\t"<<yield_EB[i]<<"\t0"<<"\n";
		     //  if(iti==0)
		     //cout<<pt_EB[i]<<"\t"<<bufferRatio_EB[iti][i]<<"\t"<<yield_EB[i]<<"\n";
		   }

		 s_UEB[iti] = (TH1D*)s_EB[iti]->Rebin(NPT_UEB,"s_UEB",ptl_UEB);
		 s_UEB_RBN[iti]=new TH1D("check", "check", NPT_UEB,ptl_UEB);
		 for(i=1; i < numPtpoints_UEB; i++) {
		   double r = 0.5*s_UEB[iti]->GetBinContent(i+1)/pt_bW_UEB[i];
		   double scaled_r = r/(2*TMath::Pi())* 1/pt_bM_UEB[i]; 
		  
		   // s_UEB_RBN[iti]->Fill(pt_bM_UEB[i],r);  
		   if(i>0&&yield_bbc[i-1]>0)
		     double err = 2*r*yield_err_bbc[i-1]/yield_bbc[i-1];
		   else 
		     double err=0;
		   s_UEB_RBN[iti]->SetBinContent(i+1,r);
		   s_UEB_RBN[iti]->SetBinError(i+1,err);
		   double scaled_err =  err/(2*TMath::Pi())* 1/pt_bM_UEB[i];
		   //s_UEB_RBN[iti]->Fill(ptl_UEB[i],r);  
		   if(iti==NTI-1)
		     if(i>0&&(r!=0))
		       CS_UEB<<pt_bM_UEB[i]<<"\t"<<r<<"\t"<<err<<"\n";
		   //CS_UEB<<pt_bM_UEB[i]<<"\t"<<r<<"\t"<<err<<"\n";
		     
		 }
	     		 
		 CS_EB.close();
		 CS_UEB.close();
		 		 
		 double resultV_EB[NPT_EB];
		 
		 f_EB[iti] = new TH1D("VM_equalBin", "VM_equalBin",NPT_EB,ptl_EB);
		 for(int a=0; a<NPT_EB; a++)
		   resultV_EB[a]=0;
		 
		 for (int i=1; i<NPT_EB; i++) //gen for generated    
		   {
		     for (int j=1; j<NPT_EB; j++)//mea for measured
		       {
			 resultV_EB[i]+=yield_EB[j]*matrix_EB[j][i];
			 // if (i==1)
			 //cout<<"\n"<<pt_EB[i]<<"\t"<<yield_EB[j]<<"\t"<<matrix_EB[j][i]<<"\t"<<resultV_EB[i];
		       } //end of pt binning
		     //  if(iti==0)
		     //cout<<"\n"<<pt_EB[i]<<"\t"<<resultV_EB[i];
		     f_EB[iti]->Fill(pt_EB[i],resultV_EB[i]); // ?
		     //resultV_EB[i]=resultV_EB[i]/pt_bW_EB[i];
		   }// end of Pt binning
	
	     
	     f_UEB[iti] = (TH1D*)f_EB[iti]->Rebin(NPT_UEB,"f_UEB",ptl_UEB);
	     f_UEB_RBN[iti]=new TH1D("check", "check", NPT_UEB,ptl_UEB);
	     
	     
	     for(i=1; i < numPtpoints_UEB; i++) {
	       double r = 0.5*f_UEB[iti]->GetBinContent(i+1)/pt_bW_UEB[i];
	       f_UEB_RBN[iti]->Fill(ptl_UEB[i],r);  
	     }
	     
	     TGraph *gr2[NTI];
	     TGraph *r1[NTI];
	     double Ratio_UEB[NTI][NPT_UEB];
	     double errRatio[NTI][NPT_UEB];
	     double pt_ratio[NPT_UEB];	    
	     
	     int a=0;

	  
	    	    
	     for (int k=1; k<numPtpoints_UEB;k++)
	       {
		 if(yield_final[k]!=0)
		   {
		     // cout<<"\n"<<yield_final[k]<<"\t"<<f_UEB_RBN[iti]->GetBinContent(k+1);
		     Ratio_UEB[iti][a]=yield_final[k]/f_UEB_RBN[iti]->GetBinContent(k+1);
		     pt_ratio[a]=pt_bM_UEB[k];
		     
		     bufferRatio_UEB[iti+1][k]= Ratio_UEB[iti][a];
		     // cout<<"\n\n"<<iti<<"\t"<<pt_ratio[a]<<"\t"<<Ratio_UEB[iti][a];
		     a++;
		     
		   }
		 else
		   continue;
	       }//end of k loop
	     r1[iti]=new TGraph(a,pt_ratio,Ratio_UEB[iti]); 
	     
	       }//end of Itieration loop
	     

	     
	     //****Drawing the above graphs adn matrix in a Canvas *******
	     double colorN[15]={3,4,7,25,24,16,15,14,13,12,12,12,12,12,7};
	     sprintf (buffer1, "vMv_CC%d_PID%d_PbSc",icent,iPID);	      
 	     TCanvas *c1 = new TCanvas(buffer1, buffer1,0,108,1209,700);
	     gStyle->SetOptStat(0);
	     c1->Divide(2,2);
	     
	     c1->cd(1);
	     gPad->SetLogy();
	     // TH1 *htemp1 = c1->DrawFrame(0,1e-12 ,30,10);
	   
	     // h_EB->GetXaxis()->SetRange(0,25);
	     h_EB->Draw();
	     // htemp1->SetTitle(" ");
	     
	     h_EB->SetLineColor(kRed);
	    
	     for(int iti = NTI-1; iti<NTI; iti++)
	       {
		 s_EB[iti]->Draw("P, same");
		 s_EB[iti]->SetMarkerColor(colorN[iti]);
		 s_EB[iti]->SetMarkerStyle(8);
	       }
	     
	     s_UEB_RBN[NTI-1]->Draw("A, same");
	     s_UEB_RBN[NTI-1]->SetMarkerColor(4);
	     s_UEB_RBN[NTI-1]->SetMarkerStyle(8);


	     h_EB->GetXaxis()->SetTitle("P_{t} (GeV/c)");
	     h_EB->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{dN}{dp_{t}dy} (1/GeV)");
	     h_EB->GetYaxis()->SetNdivisions(503);
	     h_EB->GetYaxis()->SetTitleOffset(1.05);
	     h_EB->GetYaxis()->SetTitleSize(0.042);
	     h_EB->GetXaxis()->SetTitleSize(0.042);
	    
	   
	     c1->cd(2);
	     RM_EB->Draw("colz");
	     RM_EB->GetXaxis()->SetTitle("Input Pi0 Momentum (GeV/c)");	   
	     RM_EB->GetYaxis()->SetTitle("Output Pi0 Momentum (GeV/c)"); 
	     RM_EB->GetYaxis()->SetTitleOffset(1.25); 
	     RM_EB->GetYaxis()->SetTitleSize(0.042);
	     RM_EB->GetXaxis()->SetTitleSize(0.042);
	     RM_EB->SetTitle("");
	     c1->cd(3);
	     gPad->SetLogy();
	     TH1 *htemp1 = c1->DrawFrame(0,1e-12 ,30,1e-1);
	     htemp1->GetXaxis()->SetTitle("P_{t} (GeV/c)");
	     htemp1->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{dN}{dp_{t}} (1/GeV)");
	     htemp1->GetYaxis()->SetNdivisions(503);
	     htemp1->GetYaxis()->SetTitleOffset(1.05);
	     htemp1->GetYaxis()->SetTitleSize(0.042);
	     htemp1->GetXaxis()->SetTitleSize(0.042);
	     htemp1-> SetTitle("");
	   
	     h_RawYield->Draw("E,same");
	     h_RawYield->SetLineColor(kRed);
	     //f_EB[0]->Draw("same");
	     //f_EB[0]->SetLineColor(kRed);
	
	     for(int iti = NTI-1; iti<NTI; iti++)
	       {
		 f_UEB_RBN[iti]->Draw("P, same");
		 f_UEB_RBN[iti]->SetMarkerColor(colorN[iti]);
		 f_UEB_RBN[iti]->SetMarkerStyle(8);
		 
	       }
	     /*
	     f_EB[NTI-1]->Draw("P, same");
	     f_EB[NTI-1]->SetMarkerColor(kRed);
	     f_EB[NTI-1]->SetMarkerStyle(8);
	     */	 

	    
	     c1->cd(4);
	     TH1 *htemp1 = c1->DrawFrame(0,0.1,30,2.1);
	     htemp1->GetXaxis()->SetTitle("P_{t} (GeV/c)");
	     htemp1->GetYaxis()->SetTitle("#frac{convoluted vector}{raw spectrum}");
	     htemp1->GetYaxis()->SetTitleSize(0.045);
	     htemp1->GetXaxis()->SetTitleSize(0.042);
	    
	     for(int iti = NTI-1; iti<NTI; iti++)
	       {
		 r1[iti]->Draw("P, same");
		 r1[iti]->SetMarkerColor(colorN[iti]);
		 r1[iti]->SetMarkerStyle(8);
		 
	       }
	     
	      }//end of sector loop
       }//end of PID loop
     
   }//end of centrality loop



	    
 }

