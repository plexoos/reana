prod_output(int nevents = 10000,
	    const char *dstFile1 = "DST_EVE_MB_run16AuAu_200GeV_CA_pro111-0000459208-9000.root",
	    const char *dstFile2 = "CNT_MB_run16AuAu_200GeV_CA_pro111-0000459208-9000.root",
	    const char *dstFile3 = "DST_SVX_MB_run16AuAu_200GeV_CA_pro111-0000459208-9000.root",
	    const char *outfile = "test_459208.root"
	    )
{
  gROOT->SetBatch(true);

  gSystem->Load("libfun4all.so");
  gSystem->Load("libfun4allfuncs.so");
  gSystem->Load("libCNT.so");
  gSystem->Load("libcompactCNT.so");
  gSystem->Load("libsvx.so");
  gSystem->Load("libsimreco.so");
  gSystem->Load("librecal.so");

  gSystem->Load("libAnaAlignmentProd.so");
  gSystem->Load("libRun11VTXana.so");


  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(0);
  recoConsts *rc = recoConsts::instance();

  MasterRecalibratorManager *mr = new MasterRecalibratorManager();
  se->registerSubsystem(mr);

  SubsysReco *svxtest = new AnaAlignmentProd(outfile);
  se->registerSubsystem(svxtest);

  Fun4AllInputManager *in1 = new Fun4AllDstInputManager("DSTin1", "DST");
  in1->Verbosity(0);
  se->registerInputManager(in1);

  Fun4AllInputManager *in2 = new Fun4AllDstInputManager("DSTin2", "DST");
  in2->Verbosity(0);
  se->registerInputManager(in2);

  Fun4AllInputManager *in3 = new Fun4AllDstInputManager("DSTin3", "DST");
  in3->Verbosity(0);
  se->registerInputManager(in3);

  cout << "Analysis started " << endl;
  gSystem->Exec("date");
  se->fileopen("DSTin1", dstFile1);
  se->fileopen("DSTin2", dstFile2);
  se->fileopen("DSTin3", dstFile3);
  se->run(nevents);

  se->End();

  cout << "Analysis finished " << endl;

}
