#define Pi0EmbedFiles_cxx
#include "Pi0EmbedFiles.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
bool verbose = true;
Bool_t reject;

using namespace std;
void SetStyle(Bool_t graypalette=kFALSE);



void Pi0EmbedFiles::Loop()

{
  SetStyle();
  //Some initializations....

  double vtxmin=-20.0;
  double vtxmax=20.0;
  double LASYM=0.0;
  double HASYM= 0.8;
   double vpt_l=0.001;
  double vpt_h=30.0;
  double emin = 0.3;
  double emax =0.0 ;
  
  int cc=0;

  TChain *fchain;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();

 char buffer[60];
 char buffer1[60];
 double cent_l = cc*20;
 double cent_h = cc*20+20;
 if(cc==4) {cent_l = 0.0;cent_h = 89;}
 if(cc==3) cent_h = 89;

gSystem->Load("libTHmul.so");

 if (verbose)
   printf("processing %.2lf <= centrality < %.2lf\n",cent_l,cent_h);

 const int NCE = 5;  // number of centrality bins
 const int NPT = 28; // number of pT bins
 const int NPID = 4; //  number of  pid cuts : no pid; chi2; stoch2 : chi2&stoch 
 const int NSEC = 2; // PbSc or PbGl

 int Pi0TotCount[NCE] = {0};// Total number of p10, inside and outside acceptance.

 double startCent[NCE] = {00, 20, 40, 60, 00}; //lower bound on centrality based binning
 double stopCent[NCE]  = {20, 40, 60, 89, 89};//upper bound on centrality based binning

//----------  pT binning -------------------------
 double ptl[29];
 for(int i=0;i<NPT+1;i++) {
   if(i<21) ptl[i]=i*0.5;
   else if(i<27) ptl[i]=10+(i-20)*2.;
   else if(i==27) ptl[i] = 25.;
   else if(i==28) ptl[i] = 30.;
   if (verbose)
     printf("ptl%d = %.2lf\n",i,ptl[i]);
 }
 
 Double_t ptbin[28];
 Double_t e_ptbin[28];
 for(int i=0;i<NPT;i++) {
   ptbin[i]= (ptl[i]+ptl[i+1])/2.;
   if (verbose)
     printf("pt bin %d = %lf \n",i,ptbin[i]);
   e_ptbin[i]= 0.;
 }
 
 //EMCal Parameters:
 
 gSystem->Load("libemc.so");
 recoConsts *rc = recoConsts::instance();
 rc->set_IntFlag("EMCGEOFLAG",1);
 mEmcGeometryModule *gemc = new mEmcGeometryModule(1);
 int isec,iz,iy,status;
 

//Hitogram definitions

 TH1D *hZvtx[NCE];   //  vtx distribution in centrality bins
 TH1D *hPi0vptStat0[NCE]; //  vpt for stat==0  
 TH1D *hPi0vptStat1[NCE]; //  vpt for stat==1
 TH1D *hPi0vptStatN2[NCE]; //  vpt stat==-2

 TH1D *hNoWeightInputPi0Vpt[NCE];//vpt of input pi0 for stat==0, same as hPi0vptStat0
 TH1D *hNoWeightMassEcore_VpT[NCE][NPID][NSEC][NPT]; //   invariant mass calculated from the core energy of the deposited clusters.
 
 TH1D *hWeightInputPi0Vpt[NCE];//vpt weighted by power law of input pi0 for stat==0, same as hPi0vptStat0
 TH1D *hWeightMassEcore_VpT[NCE][NPID][NSEC][NPT]; //   invariant mass calculated from the core energy of the deposited clusters from weighted pt.
 



 TH1D *hEcore[NCE][NPID][NSEC]; // all cluster Ecore distribution
 TH2D *h2dpTecoreVsVpT[NCE][NPID][NSEC]; //2D plot of pt calculated from ecore of cluster and the real pt.
 TH1D *hpTecoreStat2[NCE][NPID][NSEC]; //1D plot of pt calculated form ecore of cluster
 TH1D *hVpTStat2[NCE][NPID][NSEC]; // 1D plot of real pt of simulated pi0.

 TH2D *h2dEcore1VsVpT[NCE][NPID][NSEC]; //2D plot of ecore vs vpt scaled by power law.
 
 
 THmulf *hHitMap = new THmulf("HitMap","HitMap"); // to see where all the simulated events have hit the detector. 
 hHitMap -> AddAxis("sec","sector",8,-0.5,7.5);
 hHitMap -> AddAxis("iy","iy",48,-0.5,47.5); 
 hHitMap -> AddAxis("iz","iz",96,-0.5,95.5);

 TH1D *hCentStat0  = new TH1D("CentHistStat0","CentralityStat0", 100, 0, 100);
 TH1D *hCentStatN2 = new TH1D("CentHistStatN2","CentralityStatN2", 100, 0, 100);


 //Histogram naming and definitions.   
 
for(int ic=0;ic<NCE;ic++) {
  sprintf(buffer,"Zvtx_CC%d",ic);
  hZvtx[ic] = new TH1D(buffer,buffer,200,-50,50);
  hZvtx[ic]->Sumw2();
  
  sprintf(buffer,"InputPi0vpt_Stat0_CC%d",ic);	
  hPi0vptStat0[ic] = new TH1D(buffer,buffer,60,0,30);
  // hPi0vptStat0[ic] = new TH1D(buffer,buffer,NPT,ptl);
  hPi0vptStat0[ic]->Sumw2();
  
  sprintf(buffer,"InputPi0vpt_Stat1_CC%d",ic);		
  hPi0vptStat1[ic] = new TH1D(buffer,buffer,60,0,30);
  hPi0vptStat1[ic]->Sumw2();
  
  sprintf(buffer,"InputPi0vpt_StatN2_CC%d",ic);
  hPi0vptStatN2[ic] = new TH1D(buffer,buffer,60,0,30);
  hPi0vptStatN2[ic]->Sumw2();
  
  sprintf(buffer,"NoWeightInputPi0_Vpt_CC%d",ic);
  // hNoWeightInputPi0Vpt[ic] = new TH1D(buffer,buffer,NPT,ptl);
  hNoWeightInputPi0Vpt[ic] = new TH1D(buffer,buffer,60,0,30);
  hNoWeightInputPi0Vpt[ic]->Sumw2();
  
  sprintf(buffer,"WeightInputPi0_Vpt_CC%d",ic);
  hWeightInputPi0Vpt[ic] = new TH1D(buffer,buffer,NPT,ptl);
  hWeightInputPi0Vpt[ic]->Sumw2();
   
  for(int ipid=0;ipid<NPID;ipid++) {
    for(int isec=0;isec<NSEC-1;isec++) {
      
      if(isec==0) sprintf(buffer,"h2dEcore1VsVpT_CC%d_PID%d_PbSc",ic,ipid);
      else if(isec==1) sprintf(buffer,"h2dEcore1VsVpT_CC%d_PID%d_PbGl",ic,ipid);
      else sprintf(buffer,"h2dEcore1VsVpT_CC%d_PID%d_NonRecognizedSectors",ic,ipid);
      //      h2dEcore1VsVpT[ic][ipid][isec] = new TH2D(buffer,buffer,NPT,ptl,NPT,ptl);
      h2dEcore1VsVpT[ic][ipid][isec] = new TH2D(buffer,buffer,60,0,30,60,0,30);
      if(isec==0) sprintf(buffer,"Ecore_CC%d_PID%d_PbSc",ic,ipid);
      else if(isec==1) sprintf(buffer,"Ecore_CC%d_PID%d_PbGl",ic,ipid);
      else sprintf(buffer,"Ecore_CC%d_PID%d_NonRecognizedSectors",ic,ipid);
      hEcore[ic][ipid][isec] = new TH1D(buffer,buffer,60,0,30);
      hEcore[ic][ipid][isec]->Sumw2();

      if(isec==0) sprintf(buffer,"h2dpTecoreVsVpT_CC%d_PID%d_PbSc",ic,ipid);
      else if(isec==1) sprintf(buffer,"h2dpTecoreVsVpT_CC%d_PID%d_PbGl",ic,ipid);
      else sprintf(buffer,"h2dpTecoreVsVpT_CC%d_PID%d_NonRecognizedSectors",ic,ipid);
      //h2dpTecoreVsVpT[ic][ipid][isec] = new TH2D(buffer,buffer,NPT,ptl,NPT,ptl);
      h2dpTecoreVsVpT[ic][ipid][isec] = new TH2D(buffer,buffer,60,0,30,60,0,30);

      if(isec==0) sprintf(buffer,"hpTecoreStat2_CC%d_PID%d_PbSc",ic,ipid);
      else if(isec==1) sprintf(buffer,"hpTecoreStat2_CC%d_PID%d_PbGl",ic,ipid);
      else sprintf(buffer,"hpTecoreStat2_CC%d_PID%d_NonRecognizedSectors",ic,ipid);
      hpTecoreStat2[ic][ipid][isec] = new TH1D(buffer,buffer,300,0,30);
      hpTecoreStat2[ic][ipid][isec] -> Sumw2();


      if(isec==0) sprintf(buffer,"hVpTStat2_CC%d_PID%d_PbSc",ic,ipid);
      else if(isec==1) sprintf(buffer,"hVpTStat2_CC%d_PID%d_PbGl",ic,ipid);
      else sprintf(buffer,"hVpTStat2_CC%d_PID%d_NonRecognizedSectors",ic,ipid);
      hVpTStat2[ic][ipid][isec] = new TH1D(buffer,buffer,300,0,30);
      hVpTStat2[ic][ipid][isec] -> Sumw2();
      
      for(int ipt=0;ipt<NPT;ipt++) {
	
	if(isec==0) sprintf(buffer1,"PbSc");
	else if(isec==1) sprintf(buffer1,"PbGl");
	else sprintf(buffer1,"NonRecognizedSectors");
	sprintf(buffer,"MassEcoreNoWeightVpT_CC%d_PID%d_%s_pTbin%d",ic,ipid,buffer1,ipt);
	hNoWeightMassEcore_VpT[ic][ipid][isec][ipt]= new TH1D(buffer,buffer,100,0,0.5);
	hNoWeightMassEcore_VpT[ic][ipid][isec][ipt]->Sumw2();
	sprintf(buffer,"MassEcoreWeightVpT_CC%d_PID%d_%s_pTbin%d",ic,ipid,buffer1,ipt);
	hWeightMassEcore_VpT[ic][ipid][isec][ipt]= new TH1D(buffer,buffer,100,0,0.5);
	hWeightMassEcore_VpT[ic][ipid][isec][ipt]->Sumw2();



			
      }//End of pt loop
    }//end of sec loop
  } //end of PID loop
 }// end of centrality loop


 TF1 *fPower = new TF1( Form("fPPpi0[%d]",ic),"[0]*exp(-[1]/(x))*pow((x),[2])",1,30);
 fPower->SetParameters(3.42029e+02 , 6.57555e+00, -8.23040e+00);




 TF1 *fHagedorn[3][5];//first index is sector type, second is centrality binning (index 4 = all data of particular sector)
 /*
TF1 *fPower =new TF1( "fHag_PbSc_n_PbGl","[0]*x/(pow(exp(-[1]*x-[2]*x*x)+x/[3],[4]))",0.0,30.0); //Hagedron funcction
fPower->SetParameters(474.345, -0.0932606, 0.00652148, 2.08672,13.2168);
 */



 //Below are parameters obtanied from Fit to data from Analysis Note 590. Fits and data is under Weight folder
 double hag_PbSc[5][5] = {{22.9658,-0.0834956,0.00685566,3.50411,14.6099},{13.959,-0.0647175,0.00734369,3.52312,15.2056},{18.591,-0.190602,0.00754808,2.30908,10.2918},{21.088,-0.23404,0.00894609,1.61344,9.19704},{67.158,-0.110878,0.00636448,2.87453,12.5732}}; //first index is centrality and second is  5 parameters of Hagedron function 

 double hag_PbGl[5][5]={{21.2056,-0.0644354,0.00630144,3.4583,14.8495},{16.8145,-0.0571699,0.00815783,3.41199,15.3824},{22.9963,-0.216566,0.00757632,2.00562,9.47778},{7.12636,-0.0821495,0.00921562,3.1368,14.4248},{62.5342,-0.075044,0.00650276,2.99893,13.6206}};



 double hag_CS[5][5]={{23.6755,-0.0787074,0.00655066,3.35507,14.3622},{16.5856,-0.0638283,0.00731722,3.18602,14.4872},{21.0208,-0.206243,0.00771052,2.15283,9.8594},{11.5143,-0.133606,0.00700551,2.17181,11.1868},{68.135,-0.0963232,0.00616266,2.84505,12.8174}};

 
 for (int z=0;z<5;z++)
   {
     fHagedorn[0][z] = new TF1( Form("fHag_PbSc_%d",z),"[0]*x/(pow(exp(-[1]*x-[2]*x*x)+x/[3],[4]))",0.0,30.0); //Hagedron funcction
     fHagedorn[0][z]->SetParameters(hag_PbSc[z]);
     fHagedorn[1][z] = new TF1( Form("fHag_PbGl_%d",z),"[0]*x/(pow(exp(-[1]*x-[2]*x*x)+x/[3],[4]))",0.0,30.0); //Hagedron funcction
     fHagedorn[1][z]->SetParameters(hag_PbGl[z]);
     fHagedorn[2][z] = new TF1( Form("fHag_CS_%d",z),"[0]*x/(pow(exp(-[1]*x-[2]*x*x)+x/[3],[4]))",0.0,30.0); //Hagedron funcction
     fHagedorn[2][z]->SetParameters(hag_CS[z]);




     }
 float locx1,locy1,locz1,locx2,locy2,locz2;
 int iz1,iy1,iz2,iy2;
 double vpt_temp[NCE] = {-1}; // NCE 


//---------- DEAD MAP ---------

 int deadMap[8][96][48]={0};
 int masktwr[8][96][48]={0};
 DeadMapReading(deadMap,masktwr);//removing 3*3 masked region around this
 int timing_deadMap[8][96][48]={0};
 int timing_masktwr[8][96][48]={0};
 timing_DeadMapReading(timing_deadMap,timing_masktwr);//removing only the towers

 //cout<<"DeadMap Loaded\n";

 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
 //for (Long64_t jentry=0; jentry<1000000;jentry++) {
   if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl;
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   //if(anclvl11<0 || anclvl12 <0 || anclvl21<0 || anclvl22<0) continue;
   
   if(cent == -1) continue;
   // if (nclus>100) continue;
   for(int ic=0;ic<NCE;ic++) {
     if(cent>=startCent[ic]&&cent<stopCent[ic]) {
       //1 if(stat==0) 
	 //1hZvtx[ic]->Fill(zvtx);	 //  Fill histo Zvtx
     }
    
   }//NCE loop 
   if(zvtx < vtxmin || zvtx > vtxmax) continue;
   if(stat==0) {
     if(vpt<=vpt_l||vpt>vpt_h) continue;
  
     hCentStat0->Fill(cent);
     for(int ic=0;ic<NCE;ic++) {
       if(cent>=startCent[ic]&&cent<stopCent[ic]) {
	 
	 hPi0vptStat0[ic]->Fill(vpt);
	 hNoWeightInputPi0Vpt[ic]->Fill(vpt);
	 // hWeightInputPi0Vpt[ic]->Fill(vpt,fHagedorn[2][ic]->Eval(vpt));
       }
     }//end of centrality loop
     continue;
   }//end of stat==0 condition
   
   if(stat==-2){
     hCentStatN2->Fill(cent);
     for(int ic=0;ic<NCE;ic++) {
       if(cent>=startCent[ic]&&cent<stopCent[ic]) {
	 hPi0vptStatN2[ic]->Fill(vpt);
       }
     }// end of centrality loop
     continue;
   }//end os stat==-2 loop
   
   if(stat==1) {
     if(vpt<=vpt_l||vpt>vpt_h) continue;
  
     //if(anclvl11!=1 ) continue;//choosing only ancestry level 1. Basically only pi0 from direct decay from the pions. 

     // if(anclvl11<0) continue;
     if (ecore1<emin) continue;     
     // if (chi21>3.0) continue;
     // if(vpid1!=1) continue;

     if(masktwr[sec1][z1][y1]!=0)
       continue;
     
     if(timing_masktwr[sec1][z1][y1]!=0)
       continue;
     hHitMap->Fill(1.0,sec1,y1,z1);

     for(int ic=0;ic<NCE;ic++) {
       if(cent<startCent[ic] || cent>=stopCent[ic]) continue;
       if(vpt!=vpt_temp)   {hPi0vptStat1[ic] -> Fill(vpt);vpt_temp[ic]=vpt;}
             
	 if(sec1>=0&&sec1<=5) {
	   if(y1 <= 1 || y1 >= 35) continue;
	   if(z1 <= 1 || z1 >= 71) continue;
  
	  
 
	   hEcore[ic][0][0]->Fill(ecore1);
	   h2dEcore1VsVpT[ic][0][0]->Fill(vpt,ecore1); //No PID Entry
	  
	   if(chi21<3.) {
	   //if(vpid1==1&&ntwr1<30){
	     hEcore[ic][1][0]->Fill(ecore1);
	     h2dEcore1VsVpT[ic][1][0]->Fill(vpt,ecore1); 
	   }
	   /*
	   if(sto1>1.4) {
	     hEcore[ic][2][0]->Fill(ecore1);
	     //h2dEcore1VsVpT[ic][2][0]->Fill(vpt,ecore1,fHagedorn[0][ic]->Eval(vpt)); 
	     h2dEcore1VsVpT[ic][2][0]->Fill(vpt,ecore1); 
	   }
	   if(chi21<3.&&ntwr1<30) {                                 	
	     hEcore[ic][3][0]->Fill(ecore1);
	     //h2dEcore1VsVpT[ic][3][0]->Fill(vpt,ecore1,fHagedorn[0][ic]->Eval(vpt)); 
	     h2dEcore1VsVpT[ic][3][0]->Fill(vpt,ecore1); 
	     }*/
	 }

	 /*
	 //PbGl entries
	 if(sec1>=6&&sec1<=7) {
	 if(y1 <= 1 || y1 >= 47) continue;
	 if(z1 <= 1 || z1 >= 95) continue;
  
	   hEcore[ic][0][1]->Fill(ecore1);
	   //h2dEcore1VsVpT[ic][0][1]->Fill(vpt,ecore1,fHagedorn[1][ic]->Eval(vpt));  //No PID Entry
	   h2dEcore1VsVpT[ic][0][1]->Fill(vpt,ecore1);  //No PID Entry
	   if(chi21<3.) { 
	     hEcore[ic][1][1]->Fill(ecore1);
	     // h2dEcore1VsVpT[ic][1][1]->Fill(vpt,ecore1,fHagedorn[1][ic]->Eval(vpt)); 
	     h2dEcore1VsVpT[ic][1][1]->Fill(vpt,ecore1); 
	   }
	   if(sto1>1.4) {
	     hEcore[ic][2][1]->Fill(ecore1);
	     // h2dEcore1VsVpT[ic][2][1]->Fill(vpt,ecore1,fHagedorn[1][ic]->Eval(vpt)); 
	     h2dEcore1VsVpT[ic][2][1]->Fill(vpt,ecore1); 
	   }
	   if(chi21<3.&&ntwr1<30) {                                 	
	     hEcore[ic][3][1]->Fill(ecore1);
	     // h2dEcore1VsVpT[ic][3][1]->Fill(vpt,ecore1,fHagedorn[1][ic]->Eval(vpt)); 
	     h2dEcore1VsVpT[ic][3][1]->Fill(vpt,ecore1); 
	   }
	   }//pbgl if statement*/
        
     }//NCE loop
     continue;
   }//stat==1 if statement
   
   if(stat==2) {
     //  if(anclvl11!=1 || anclvl21!=1) continue;//choosing only ancestry level 1. Basically only pi0 from direct decay from the pions. 
     //if(	ptecore>10.)  	HASYM = 0.95; // asym cut 0.95 when pt>10GeV, 
     //if(	ptecore<=10.)  	HASYM = 0.8; // asym cut 0.95 when pt>10GeV, 
     if(asymecore <= LASYM || asymecore >= HASYM) continue;	
     if(vpt<=vpt_l||vpt>vpt_h) continue;
     if(masktwr[sec1][z1][y1]!=0) continue;
     if(masktwr[sec2][z2][y2]!=0) continue;
     if(timing_masktwr[sec1][z1][y1]!=0) continue;
     if(timing_masktwr[sec2][z2][y2]!=0) continue;
    
     if(ecore1< emin || ecore2 < emin) continue;
     if(massecore<0.11&&massecore>0.18) continue;
     
     if(sec1>=0&&sec1<=5&&sec1==sec2) {  // PbSc 
       if(y1 <= 1 || y1 >= 35) continue;
       if(z1 <= 1 || z1 >= 71)  continue;
       if(y2 <= 1 || y2 >= 35) continue;
       if(z2 <= 1 || z2 >= 71) continue;
      
       for(int ic=0;ic<NCE;ic++) {
	 if(cent<startCent[ic] || cent>=stopCent[ic]) continue;
	 h2dpTecoreVsVpT[ic][0][0]->Fill(vpt,ptecore); 
	 hVpTStat2[ic][0][0]->Fill(vpt);
	 
	 // if(chi21<3.&&chi22<3.&&ntwr1<30&&ntwr2<30) {
	 if(chi21<3.&&chi22<3.) {
	   h2dpTecoreVsVpT[ic][1][0]->Fill(vpt,ptecore); 
	   hpTecoreStat2[ic][1][0]->Fill(ptecore);
	   hVpTStat2[ic][1][0]->Fill(vpt);
	 }//end of chi2
       }//end of centrality loop	
     }//end of if statement for PbSc
   }//end of stat==2 if statement
  }// End of loop over all entries.
	
 //****************************EVENT Reading over all loop is finished**************************
   

 //---------Scaling for Pi0 which have gone via out of acceptance. 
  
 double R[NCE];
 for(int ic=0;ic<NCE;ic++) {
   R[ic] = hPi0vptStatN2[ic]->GetEntries()/hPi0vptStat0[ic]->GetEntries();
   
   printf("Norm. factor CC%d = 1+%d/%d = %lf\n",ic,hPi0vptStatN2[ic]->GetEntries(),hPi0vptStat0[ic]->GetEntries(),1.+R[ic]);
   hNoWeightInputPi0Vpt[ic]->Scale(1.+R[ic]);
   hWeightInputPi0Vpt[ic]->Scale(1.+R[ic]);
   }
  


//---------------------------------   Saving as a ROOT file ---------------------------------


 TFile *fout = new TFile("EmbedPi0dAu.root","recreate");
	
 for(int ic=0;ic<NCE;ic++) {
   for(int ipid=1;ipid<2;ipid++) {
     for(int isec=0;isec<NSEC-1;isec++) {
       hEcore[ic][ipid][isec]->Write();
       
       for(int ipt=0;ipt<NPT;ipt++) { 
	 //hNoWeightMassEcore_VpT[ic][ipid][isec][ipt]->Write();
	 // hWeightMassEcore_VpT[ic][ipid][isec][ipt]->Write();
       }
				
                  
       h2dpTecoreVsVpT[ic][ipid][isec]->Write();
       //1 hpTecoreStat2[ic][ipid][isec]->Write();
       hVpTStat2[ic][ipid][isec]->Write();
       h2dEcore1VsVpT[ic][ipid][isec]->Write();
     }
   }
   
   
   //1hZvtx[ic]->Write(Form("Zvtx_CC%d",ic));
   hNoWeightInputPi0Vpt[ic]->Write();
   //hWeightInputPi0Vpt[ic]->Write();
   hPi0vptStat0[ic]->Write();
   //1hPi0vptStat1[ic]->Write();
   hPi0vptStatN2[ic]->Write();
   hHitMap->Write();
  
 }
 //hCentStat0->Write();
 //hCentStatN2->Write();

 fout->Close();


  
}// End of LOOP method
      
                  
 



void DeadMapReading(int stat[8][96][48],int mask[8][96][48])
{
   ifstream fin("DeadWarnRun16.txt");
  //ifstream fin("Dead16.txt");
  int sec, iy, iz, status;
  while(fin>>sec>>iy>>iz>>status){
    
      if(sec==4) sec =7;
      else if(sec==5) sec=6;
      else if(sec==6) sec=5;
      else if(sec==7) sec=4;
 
	  stat[sec][iz][iy] = status;
	  if(stat[sec][iz][iy]==1&&iz!=0&&iz!=95&&iy!=0&&iy!=47)  {
            mask[sec][iz][iy]=1;//10
            mask[sec][iz-1][iy]=1;//9
            mask[sec][iz+1][iy]=1;//11
            mask[sec][iz][iy-1]=1;//5
            mask[sec][iz][iy+1]=1;//15
	    mask[sec][iz-1][iy-1]=1;//4
	    mask[sec][iz-1][iy+1]=1;//14
	    mask[sec][iz+1][iy-1]=1;//6
	    mask[sec][iz+1][iy+1]=1;//16
	  }
  }
  fin.close();
  for(int i=0;i<6;i++) for(int j=0;j<96;j++) for(int k=0;k<48;k++) {
    if(j<=1||j>=70||k<=1||k>=34) mask[i][j][k] = 1;
  }
  for(int i=6;i<8;i++) for(int j=0;j<96;j++) for(int k=0;k<48;k++) {
    if(j<=1||j>=94||k<=1||k>=46) mask[i][j][k] = 1;
  }

}

void timing_DeadMapReading(int stat[8][96][48],int mask[8][96][48])
{
  cout<<"Inside timing DeadMAp";
   ifstream fin("timingDeadWarnRun16.txt");
  //ifstream fin("Dead16.txt");
  int sec, iy, iz, status;
  
  while(fin>>sec>>iy>>iz>>status){
    if(sec==4) sec =7;
      else if(sec==5) sec=6;
      else if(sec==6) sec=5;
      else if(sec==7) sec=4;
      
      stat[sec][iz][iy] = status;
      if(stat[sec][iz][iy]==1&&iz!=0&&iz!=95&&iy!=0&&iy!=47)  {
	mask[sec][iz][iy]=1;//10
      }
      }
  fin.close();
}//end of function







void SetStyle(Bool_t graypalette) {
  //cout << "Setting style!" << endl;
  gROOT->SetBatch(kTRUE);
  gStyle->Reset("Plain");
  gStyle->SetOptTitle(1);
  gStyle->SetTitleFont(24,"t");
  gStyle->SetTitleSize(0.06,"t"); 
  gStyle->SetOptStat(0);
  if(graypalette) gStyle->SetPalette(8,0);
  else gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  //gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.15); //gStyle->SetPadRtMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  //gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kBlack);
  //gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetLabelOffset(0.015,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.04,"xyz");
  gStyle->SetTitleOffset(1.75,"y");
  gStyle->SetTitleOffset(1.25,"x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  gStyle->SetTickLength(0.05,"X");
  gStyle->SetTickLength(0.03,"Y"); 
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
  gStyle->SetNdivisions(504);
}

