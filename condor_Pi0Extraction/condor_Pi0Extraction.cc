// this code extracts the yield of Pi0 in every Pt for various classification of centrality, type of sectors, tof, and PID cut. This does not make the plot for yeild. it only creates a bunch of text files from which yield is plotted. 


#include "universal.h"
const int n =4;

using namespace std;
void SetStyle(Bool_t graypalette=kFALSE);

Bool_t reject;
bool verbose = false;
int num_par=4;

double l_lim1 = 0.045;
double u_lim1 = 0.11;
double l_lim2 = 0.18;
double u_lim2 = 0.35;


Double_t fline(Double_t *x, Double_t *par)
{
  if(reject&&x[0]>=u_lim2&&x[0]<=l_lim1){
    TF1::RejectPoint();
    return 0;
  }

  if (num_par==2)
    return (par[0]+par[1]*x[0]);
  else if (num_par==4)
    return (par[0] +(par[1]*x[0]) + (par[2]*x[0]*x[0])+ (par[3]*x[0]*x[0]*x[0] ) );
  else if (num_par==1)
    return (par[0]);
 else
   return (par[0] +(par[1]*x[0]) + (par[2]*x[0]*x[0]));
}

TLine *line1 = new TLine(0.11,0,0.11,5e5);
TLine *line2 = new TLine(0.18,0,0.18,5e5);
line1->SetLineColor(7);		
line2->SetLineColor(7);		



void condor_Pi0Extraction(char *trigger, char *type, int startCC,int stopCC )
 {
   
   		


  const int NCE = 5;  // number of centrality bins
  const int NPT = 28; // number of pT bins
  const int NPID = 2; //  number of  pid cuts : no pid; chi2;   
  const int NSEC = 2; // PbSc or PbGl
  const int NTOF = 3; //5 nano second and 3Sigma cut
  
  double ptl[NPT+1]; // Number of pt bins is 28, but the range with upper and lower bound is 29.

  gSystem->Load("libTHmul.so");   
  // setting all the number for Pt bins
  for(int i=0;i<NPT+1;i++) {
    if(i<21) ptl[i]=i*0.5;
    else if(i<27) ptl[i]=10+(i-20)*2.;
    else if(i==27) ptl[i] = 25.;
    else if(i==28) ptl[i] = 30.;
    if (verbose)
      printf("ptl%d = %.2lf\n",i,ptl[i]);
  }
  
  //the central value of pt bin against which the yield is plotted.
  Double_t ptbin[28];
  Double_t e_ptbin[28];
  for(int i=0;i<NPT;i++) {
    ptbin[i]= (ptl[i]+ptl[i+1])/2.;
    if (verbose)
      printf("pt bin %d = %lf \n",i,ptbin[i]);
    e_ptbin[i]= 0.;
  }

  //below variables are used in the output files naming and histogram for clarification  
  int o_startCent[NCE] = {00, 20, 40, 60, 00}; //lower bound on centrality based binning
  int o_stopCent[NCE]  = {20, 40, 60, 88, 88};//upper bound on centrality based binning

  char o_pid[NPID][10]={"noPID","Chi2"}; //PID options 
  // char o_tof[NTOF][10]={"5ns", "3Sig"};
  char o_tof[NTOF][10]={"4Sig", "3Sig", "2Sig"};


  //below variables are used in for projection condition form the input ThMulf

  char i_cent[NCE][50]={"&&cent<4","&&cent==4","&&cent==5","&&cent==6","&&cent<7"};
  char i_pid[NPID][50]={"&&chi2>=0","&&chi2>=1&&chi2<=2"};
  char i_sector[20];
  if(strcmp(type,"PbSc")==0)
     sprintf(i_sector,"sec<6");
  else
    sprintf(i_sector,"sec>=6");
  char i_tof [NTOF][30]= {"&&tof>-1", "&&tof>=0&&tof<=4", "&&tof>=0&&tof<=2"};
  
  //with same deadmap, 16460 is MB, 16461 is ERT with embed MB and 16465 is ERT without MB

  int TN = 17748; //Taxi number  
  TFile *input_root_mb = new TFile ("raw_taxiData/Run16dAu200CAnVXMBP107.root");
  // TFile *input_root_mb = new TFile (Form("/gpfs/mnt/gpfs02/phenix/plhf/plhf1/nivram/taxi/Run16dAu200CAnVXMBP107/%d/data/se-454774.root",TN));


  int TN = 17747; //Taxi number  
  //TFile *input_root_ert = new TFile (Form("/gpfs/mnt/gpfs02/phenix/plhf/plhf1/nivram/taxi/Run16dAu200CAnVXERTP107/%d/data/se-454774.root",TN));
  TFile *input_root_ert = new TFile ("raw_taxiData/Run16dAu200CAnVXERTP107.root");
 
  
  double scaledown_mb=513.46;
  double scaledown_ert=1; 
  
  /*
  If I use NEvents instead of from taxi. 
  double scaledown_mb=532;
  double scaledown_ert=2.6025; 
  */

  TH1F *centrality;
  centrality= ((TH1F*)input_root_mb->Get("event_counter"));
  
  int NEvents[5];
  NEvents[0]= centrality->GetBinContent(1)+centrality->GetBinContent(2)+centrality->GetBinContent(3)+centrality->GetBinContent(4);
  NEvents[1]=centrality->GetBinContent(5);
  NEvents[2]=centrality->GetBinContent(6);
  NEvents[3]= centrality->GetBinContent(7);
  NEvents[4] = NEvents[0]+NEvents[1]+NEvents[2]+NEvents[3];
  
 

  THmulf *hm1_mb = new THmulf("hm1_mb","hm1_mb");
  hm1_mb = (THmulf*)input_root_mb->Get("ggh_sysErr_asym");

  THmulf *hm1_ert = new THmulf("hm1_ert","hm1_ert");
  hm1_ert = (THmulf*)input_root_ert->Get("ggh_sysErr_asym");
  
  
  TH1D *Real_IM[NCE][NPID][NTOF][NPT]; //Invariant mass of real events
  TH1D *Real_IM2[NCE][NPID][NTOF][NPT]; //Invariant mass of real events
  TH1D *Mix_IM[NCE][NPID][NTOF][NPT]; //Invariant mass of mixed events
  TH1D *Mix_IM2[NCE][NPID][NTOF][NPT]; //Invariant mass of mixed events
  TH1D *Sub_IM[NCE][NPID][NTOF][NPT];//Invariant mass of Real - mixed events
  TH1D *Sub_IMP[NCE][NPID][NTOF][NPT];//Invariant mass of Real - mixed events -polynomial
  TH1D *Sub_IMPA[NCE][NPID][NTOF][NPT];//Invariant mass of Real - mixed events -polynomial - average
  TH1D *ASub_IM[NCE][NPID][NTOF][NPT];//Invariant mass of Real - mixed events
  //TH1D *Sub_IM[NPT];//Invariant mass of Real - mixed events
  TH1D *Extra_IM[NCE][NPID][NTOF][NPT];//Extra from the subration;
  TF1 *f1;
  TF1 *f2;

  
  double sm_x[200];
  double sm_y[200];
		

  double B_Mean [NPT];
  double B_Err [NPT]; //error of the amount subtracted

  
  //double l_lim1 = 0.055;
  TF1 *fleft = new TF1("fleft",fline,l_lim1,u_lim1,num_par);
  TF1 *fright = new TF1("fright",fline,l_lim2,u_lim2,num_par);  
 
  TF1 *fline_bet = new TF1("flbt", "[0] + [1]*x + [2]*x*x",u_lim1, l_lim2); // line to go in between the pion. 


  char buffer[120];
  

  ofstream Num;
  ofstream Num_fit;
 
  if (verbose)
    cout<<"\n"<<iCENT<<"\t"<<iPID<<"\t"<<iTOF<<"\t"<<iPt;
  

  TFile * output_root[5];
  for (int iCENT =startCC; iCENT<stopCC; iCENT++)
    {
      output_root[iCENT] = new TFile(Form("output_plots/root/%s_%s_%dCC%d.root",trigger,type,o_startCent[iCENT],o_stopCent[iCENT]), "RECREATE");
      
      
      for (int iPID =NPID-1 ; iPID<NPID; iPID++)
	{
	  for (int iTOF =1; iTOF<NTOF-1; iTOF++)
	    {     
	      sprintf(buffer , "output_plots/txt/scaledUEB_rawPi0_%s_%s_%dCC%d_%s_%s.txt",trigger,type,o_startCent[iCENT],o_stopCent[iCENT], o_pid[iPID], o_tof[iTOF]);
	      
	      if (verbose)
		cout<<"\n"<<buffer;
	      Num.open(buffer);
	      for (int iPt=0; iPt<NPT; iPt++)
		    {
		      

		    char ProjCond_Real[240]; //Projection conditions.
		    sprintf(ProjCond_Real, "mix==0%s%s%s&&pt>%f&&pt<=%f&&asym<0.8",i_cent[iCENT],i_pid[iPID],i_tof[iTOF],ptl[iPt], ptl[iPt+1]);
		    
		    Real_IM[iCENT][iPID][iTOF][iPt] = new TH1D(Form("Real_IM_%d_%d_%d_%f",iCENT,iPID,iTOF,ptbin[iPt]),"",160, 0,0.8); 
		    if (strcmp(trigger, "MB")==0)
		      hm1_mb->Projection(Form("Real_IM_%d_%d_%d_%f",iCENT,iPID,iTOF,ptbin[iPt]),"mass",ProjCond_Real);
		    else
		      hm1_ert->Projection(Form("Real_IM_%d_%d_%d_%f",iCENT,iPID,iTOF,ptbin[iPt]),"mass",ProjCond_Real);

		    
		    char ProjCond_Mix[240]; //Projection conditions.
		    sprintf(ProjCond_Mix, "mix==1%s%s%s&&pt>%f&&pt<=%f&&asym<0.8",i_cent[iCENT],i_pid[iPID],i_tof[iTOF],ptl[iPt], ptl[iPt+1]);
		    if(verbose)
		      cout<<"\n****************"<<ProjCond_Real<<"***********************";
		    Mix_IM[iCENT][iPID][iTOF][iPt] = new TH1D(Form("Mix_IM_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"",160, 0,0.8); 
		    
		    if (strcmp(trigger, "MB")==0){
		      hm1_mb->Projection(Form("Mix_IM_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"mass",ProjCond_Mix);
		      Mix_IM2[iCENT][iPID][iTOF][iPt] = (TH1D*)Mix_IM[iCENT][iPID][iTOF][iPt]->Clone();
		      double scaleT =(Real_IM[iCENT][iPID][iTOF][iPt]->Integral(16,20)+Real_IM[iCENT][iPID][iTOF][iPt]->Integral(36,56))/(Mix_IM[iCENT][iPID][iTOF][iPt]->Integral(16,20)+Mix_IM[iCENT][iPID][iTOF][iPt]->Integral(36,56));
		      
		      Mix_IM2[iCENT][iPID][iTOF][iPt]->Scale(scaleT);
		     
		    }
		    else
		      {
		       hm1_ert->Projection(Form("Mix_IM_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"mass",ProjCond_Mix);
		       TF1 * fPol = new TF1("fPol","pol3 ",0.04, 0.8);
		       TH1D* hdiv = (TH1D*)Real_IM[iCENT][iPID][iTOF][iPt]->Clone();
		       hdiv->Divide(Mix_IM[iCENT][iPID][iTOF][iPt]);
		       //hdiv->Draw();
		       //remove the signal peaks from the histrogram (pi0, eta masses)
		       for(int ibin = 0; ibin < hdiv->GetNbinsX(); ibin++){
			 if( (hdiv->GetBinCenter(ibin+1)>0.1&&hdiv->GetBinCenter(ibin+1)<0.2) || (hdiv->GetBinCenter(ibin+1)>0.490&&hdiv->GetBinCenter(ibin+1)<0.61) ){
			   hdiv->SetBinContent(ibin+1, 0);
			 }
		       }
		       //fit with the polynomial
		       hdiv->Fit(fPol, "RQ");
		       //Normalize
		       Mix_IM2[iCENT][iPID][iTOF][iPt] = (TH1D*)Mix_IM[iCENT][iPID][iTOF][iPt]->Clone();
		       for(int ibin = 0; ibin <  Mix_IM2[iCENT][iPID][iTOF][iPt]->GetNbinsX(); ibin++){
			 double center =  Mix_IM2[iCENT][iPID][iTOF][iPt]->GetBinCenter(ibin+1);
			 double content =  Mix_IM2[iCENT][iPID][iTOF][iPt]->GetBinContent(ibin+1);
			 double norm = fPol->Eval(center);
			 Mix_IM2[iCENT][iPID][iTOF][iPt]->SetBinContent(ibin+1, content*norm);
		       }
		       
		       delete fPol;
		      }




		    TCanvas *c1 = new TCanvas(Form("%s_%s_%0.2lfPt%0.2lf_%dCC%d_%s_%s",trigger,type,ptl[iPt],ptl[iPt+1],o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]), "Invariant Mass",0,23,1769,468);
		     
		     
		    TPaveText *pt1 = new TPaveText(0.1,0.90,.9,.95,"blNDC");
		    pt1->SetBorderSize(0);
		    pt1->SetFillColor(0);
		    char name[120];
		    sprintf(name, " Pt range (%0.2f,%0.2f]",ptl[iPt],ptl[iPt+1]);
		    pt1->AddText(name);
		    pt1->Draw();
		    
		    TPaveText *pt2 = new TPaveText(0.1,0.86,.9,.89,"blNDC");
		    pt2->SetBorderSize(0);
		    pt2->SetFillColor(0);
		    char name[120];
		    sprintf(name, "%s_%s_%dCC%d", o_tof[iTOF],o_pid[iPID],o_startCent[iCENT], o_stopCent[iCENT]);
		    pt2->AddText(name);
		    pt2->Draw();
		    
		    TPad* gPad = new TPad("graphs","graphs",0.01,0.05,0.95,0.82);
		    gPad->Draw();
		    gPad->cd();

		    
		    if(Mix_IM[iCENT][iPID][iTOF][iPt]->Integral() >=1000)
		      {
			if(verbose)
			  cout<<"\n For this Pt, I am in the mixed average range"<<(ptl[iPt]+ptl[iPt+1])/2;
			if(Real_IM[iCENT][iPID][iTOF][iPt]->Integral()>=2500)
			  gPad->Divide(6);
			else 
			  gPad->Divide(5);
			
			gPad->cd(1);
		    
			Real_IM[iCENT][iPID][iTOF][iPt]->GetXaxis()->SetTitle("Invariant Mass (GeV)"); 
			Real_IM[iCENT][iPID][iTOF][iPt]->SetLineColor(kRed);
			Real_IM[iCENT][iPID][iTOF][iPt]->Draw();
			if (verbose)
			  cout<<"\n BSUB in pt "<<ptl[iPt]<<"\t"<<ptl[iPt+1]<<"\t"<<Real_IM[iCENT][iPID][iTOF][iPt]->Integral();

			gPad->cd(2);
			Mix_IM[iCENT][iPID][iTOF][iPt]->GetXaxis()->SetTitle("Invariant Mass (GeV)"); 
			Mix_IM[iCENT][iPID][iTOF][iPt]->SetLineColor(kBlue);
			Mix_IM[iCENT][iPID][iTOF][iPt]->Draw();
			
			gPad->cd(3);
			Real_IM[iCENT][iPID][iTOF][iPt]->Draw();
			Mix_IM2[iCENT][iPID][iTOF][iPt]->SetLineColor(kBlue);	   		
			Mix_IM2[iCENT][iPID][iTOF][iPt]->Draw("same");
			
			gPad->cd(4);
			Sub_IM[iCENT][iPID][iTOF][iPt] = (TH1D*)Real_IM[iCENT][iPID][iTOF][iPt]->Clone();
			Sub_IM[iCENT][iPID][iTOF][iPt]->Add(Mix_IM2[iCENT][iPID][iTOF][iPt],-1);
							
			
			if(Real_IM[iCENT][iPID][iTOF][iPt]->Integral()>=2500)
			  {
			    TGaxis::SetMaxDigits(3);
				
			    if(iPt==1)
			      num_par=3;
			    else
			      num_par=3;
			    TF1 *fl = new TF1("fl",fline,l_lim1,u_lim2,num_par);
			    reject=kTRUE;
			    Sub_IM[iCENT][iPID][iTOF][iPt]->Fit(fl,"0,R,Q");
			    reject= kFALSE;
			    
			    fline_bet->SetParameters(fl->GetParameters());
			    Sub_IM[iCENT][iPID][iTOF][iPt]->GetListOfFunctions()->Add(fline_bet);
			    gROOT->GetListOfFunctions()->Remove(fline_bet);
			    fline_bet->SetLineStyle(4);
			    fline_bet->SetLineColor(6);			
			    //For visualisation, storing as separate functions. 
			    
			    fleft->SetParameters(fl->GetParameters());
			    Sub_IM[iCENT][iPID][iTOF][iPt]->GetListOfFunctions()->Add(fleft);
			    gROOT->GetListOfFunctions()->Remove(fleft);
			    fleft->SetLineColor(6);			
			    
			    fright->SetParameters(fl->GetParameters());
			    Sub_IM[iCENT][iPID][iTOF][iPt]->GetListOfFunctions()->Add(fright);
			    gROOT->GetListOfFunctions()->Remove(fright);
			    fright->SetLineColor(6);			
			    
			    Sub_IM[iCENT][iPID][iTOF][iPt]->Draw();
			    
			    fline_bet->Draw("same");
			    gPad->cd(5);
			
			    Sub_IMP[iCENT][iPID][iTOF][iPt] = new TH1D(Form("Sub_IMP_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"",160, 0,0.8); 
		
			    for(int k=0;k<Real_IM[iCENT][iPID][iTOF][iPt]->GetNbinsX();k++)         {                                                                                           
			      Sub_IMP[iCENT][iPID][iTOF][iPt]->SetBinContent(k+1,(Sub_IM[iCENT][iPID][iTOF][iPt]->GetBinContent(k+1)-fl->Eval((k)*0.005+0.0025)));
			 
			    }
		
			    TF1 *fl2 = new TF1("fl2",fline,(l_lim1-0.025),(u_lim2-0.1),2);
			    Sub_IMP[iCENT][iPID][iTOF][iPt]->Fit(fl2,"R,Q");
			    
			    Sub_IMP[iCENT][iPID][iTOF][iPt]->Draw();
			    line1->Draw("same");
			    line2->Draw("same");
			    gPad->cd(6);
			  
			    Sub_IMPA[iCENT][iPID][iTOF][iPt] = new TH1D(Form("Sub_IMPA_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"",160, 0,0.8); 
			    int a=0;
			    for(int k=0;k<Real_IM[iCENT][iPID][iTOF][iPt]->GetNbinsX();k++)         {                                                                                           
			      Sub_IMPA[iCENT][iPID][iTOF][iPt]->SetBinContent(k+1,(Sub_IMP[iCENT][iPID][iTOF][iPt]->GetBinContent(k+1)-fl2->Eval((k)*0.005+0.0025)));
			      a++;
			      
			    }
			    Sub_IMPA[iCENT][iPID][iTOF][iPt]->Draw();
			    line1->Draw("same");
			    line2->Draw("same");
			    
			    double Npi0 = Sub_IMPA[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005);
			  }
			else
			  {
			    TF1 *fl2 = new TF1("fl2",fline,(l_lim1-0.025),(u_lim2-0.1),2);
			    Sub_IM[iCENT][iPID][iTOF][iPt]->Fit(fl2,"R,Q");
			    line1->Draw("same");
			    line2->Draw("same");
			    
			    gPad->cd(5);
			  
			    Sub_IMPA[iCENT][iPID][iTOF][iPt] = new TH1D(Form("Sub_IMPA_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"",160, 0,0.8); 
			    int a=0;
			    for(int k=0;k<Real_IM[iCENT][iPID][iTOF][iPt]->GetNbinsX();k++)         {                                                                                           
			      Sub_IMPA[iCENT][iPID][iTOF][iPt]->SetBinContent(k+1,(Sub_IM[iCENT][iPID][iTOF][iPt]->GetBinContent(k+1)-fl2->Eval((k)*0.005+0.0025)));
			      a++;
			      
			    }
			    Sub_IMPA[iCENT][iPID][iTOF][iPt]->Draw();
			    line1->Draw("same");
			    line2->Draw("same");
			    
			    double Npi0 = Sub_IMPA[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005);



			  }
			if (Npi0>0)
			  	if (strcmp(trigger, "MB")==0)
				  {
				    double eRpi = Real_IM[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005);
				    double eMpi = Mix_IM[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005);
				    double eI = Real_IM[iCENT][iPID][iTOF][iPt]->Integral(16,20)+Real_IM[iCENT][iPID][iTOF][iPt]->Integral(36,56);
				    double eMscale=(Mix_IM[iCENT][iPID][iTOF][iPt]->Integral(16,20)+Mix_IM[iCENT][iPID][iTOF][iPt]->Integral(36,56));
				    double errT = TMath::Sqrt(eRpi + (eI*eMpi*eMpi)/(eMscale*eMscale));

				  }
				else
				  double errT = TMath::Sqrt(Real_IM[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005));
			else
			 double errT=0;
			if (strcmp(trigger, "MB")==0)
			  double scale = 1/ ((ptl[iPt+1]-ptl[iPt])*NEvents[iCENT]*scaledown_ert);  
			else
			  double scale = 1/ ((ptl[iPt+1]-ptl[iPt])*NEvents[iCENT]*scaledown_mb);  
			double scaled_Npi0 = Npi0*scale;
			double scaled_errT = errT*scale;
			if(Npi0!=0)
			  Num<<ptbin[iPt]<<"\t"<<scaled_Npi0<<"\t"<<scaled_errT<<endl;
			//Num<<ptbin[iPt]<<"\t"<<Npi0<<"\t"<<errT<<"\t"<<errT/TMath::Sqrt(Npi0)<<endl;
			  c1->Write();
			  
			  if (iPt<NPT-1)
			    c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf(",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID], o_tof[iTOF]));
			  else
			    c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf)",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]));
     
			
			  if(verbose)
			    cout<<"\n The integral of Real pio peak" <<Real_IM[iCENT][iPID][iTOF][iPt]->Integral();

		      }//End of if statement which determines whether we do mix background subtraction or average subtraction
		       else if(Mix_IM[iCENT][iPID][iTOF][iPt]->Integral() <1000 && Real_IM[iCENT][iPID][iTOF][iPt]->Integral()>5 )		   
		      {
			if(verbose){
			  cout<<"\n For this Pt, I am in the average range"<<(ptl[iPt]+ptl[iPt+1])/2;
			  cout<<"\n The integral of Real pio peak" <<Real_IM[iCENT][iPID][iTOF][iPt]->Integral();
			}
			gPad->Divide(2);
			gPad->cd(1);
		    
			Real_IM[iCENT][iPID][iTOF][iPt]->GetXaxis()->SetTitle("Invariant Mass (GeV)"); 
			Real_IM[iCENT][iPID][iTOF][iPt]->SetLineColor(kRed);
			Real_IM[iCENT][iPID][iTOF][iPt]->Draw();
			double add =0;
			int count=0;      
			//subtracting average values between 0.175 and 0.275
			for(int k=0;k<100;k++) 
			  {
			    // if((k>=8&&k<20)||(k>=40&&k<60)){
			    if((k>=50&&k<70)){
			      double num = Real_IM[iCENT][iPID][iTOF][iPt]->GetBinContent(k+1);
			      add+=num;
			      count++;}
			    else 
			      continue;
			    
			  }

			
			B_Mean[iPt] = add/count;
			B_Err[iPt]= TMath::Sqrt(add)/count;
			if (verbose)	
			  cout<<"\n B_Mean "<< B_Mean[iPt]<<endl;;     
						
			gPad->cd(2);
			ASub_IM[iCENT][iPID][iTOF][iPt] = new TH1D(Form("ASub_IM_%d_%d_%d_%d",iCENT,iPID,iTOF,iPt),"",160, 0,0.8); 
		
			for(int k=0;k<Real_IM[iCENT][iPID][iTOF][iPt]->GetNbinsX();k++)
			  {
			    num = Real_IM[iCENT][iPID][iTOF][iPt]->GetBinContent(k+1);
			    double value = num - B_Mean[iPt];
			    ASub_IM[iCENT][iPID][iTOF][iPt]->SetBinContent(k+1,value);
			  }
		
			
			TGaxis::SetMaxDigits(3);
			ASub_IM[iCENT][iPID][iTOF][iPt]->Draw();
			//Pi0 mass is like 0.132GeV, we are loking in neighbourhood of 0.1 - 0.17.
			line1->Draw("same");
			line2->Draw("same");
			
			double errA;
			double err1;
			double Npi0 = (ASub_IM[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005));
		
			double errA = Real_IM[iCENT][iPID][iTOF][iPt]->Integral(u_lim1/0.005, l_lim2/0.005);
			double errB = (errA-Npi0);
			double errC=B_Err[iPt]*(u_lim1-l_lim2)/0.005;
		
			double err1= TMath::Sqrt(errA+errB);
			double err2= TMath::Sqrt(errA+errC*errC);
			//	double err1= TMath::Sqrt(errA);
			if (strcmp(trigger, "MB")==0)
			  double scale = 1/ ((ptl[iPt+1]-ptl[iPt])*NEvents[iCENT]*scaledown_ert);  
			else
			  double scale = 1/ ((ptl[iPt+1]-ptl[iPt])*NEvents[iCENT]*scaledown_mb); 

			double scaled_Npi0 = Npi0*scale;
			double scaled_err1 = err1*scale;
			double scaled_err2 = err2*scale;
			if(Npi0!=0)
			  Num<<ptbin[iPt]<<"\t"<<scaled_Npi0<<"\t"<<scaled_err2<<"\n";
			//Num<<ptbin[iPt]<<"\t"<<Npi0<<"\t"<<err2<<"\t"<<err2/(TMath::Sqrt(Npi0))<<"\n";
		
			c1->Write();
			if (iPt<NPT-1)
			  c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf(",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]));
			else
			  c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf)",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]));
     

      		      }//end of else if statement. part where we subtract background by averaging
		     
		    else
		      {
			Real_IM[iCENT][iPID][iTOF][iPt]->Draw();
			c1->Write();
			if (iPt<NPT-1)
			  c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf(",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]));
			else
			  c1->Print(Form("output_plots/pdf/%s_%s_%dCC%d_%s_%s.pdf)",trigger,type,o_startCent[iCENT],o_stopCent[iCENT],o_pid[iPID],o_tof[iTOF]));
     			
		
		      } 
		      

	
	
		}//end of PT loop
	      

	    
	    
		
		
	      Num.close();
	      Num_fit.close();
	      if(verbose)
		cout<<"\n Done with TOF:PID:Cent"<<"\t::"<<iTOF<<"\t:"<<iPID<<"\t:"<<iCENT<<endl;
	    } // end of TOF loop
	}//end of PID loop
      output_root[iCENT]->Close();
      //delete output_root[iCENT];
      cout<<"\n \n end of Centrality loop";
    } //end of centrality loop
  
  
} // End of file




