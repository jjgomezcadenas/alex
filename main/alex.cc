// ireneMain example
// J.J. Gomez-Cadenas, August 2014


#include <alex/Alex.h>
#include <alex/ISvc.h>
#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/StringOperations.h>
#include <alex/AlgoConf.h>

#include <TFile.h>
#include <TChain.h>

// #include <RegisterAlgosHeader.hh>
// #include <AConf.hh> 

using namespace alex;
using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::ifstream;
using std::vector;

using std::stringstream;


void IreneLoop(int evtStart, int evtEnd);
void AlexLoop(int evtStart, int evtEnd);

//alex <debugLevel> <IRENE/ALEX> <evtStart> <evtEnd>

int main(int argc, char **argv)
{
  string debugLevel="DEBUG";
  string inputDst="IRENE";
  int evtStart = 0, evtEnd = -1;
  stringstream ss;

  if( argc == 2)   
  {  
    ss << argv[1];
    ss>>debugLevel;
  }
  else if ( argc == 3)   
  { 
    ss << argv[1];
    ss>>debugLevel;

    ss << argv[2];
    ss>>inputDst;
  }
  else if ( argc == 4)   
  { 
    ss << argv[1];
    ss>>debugLevel;

    ss << argv[2];
    ss>>inputDst;

    evtStart = atoi(argv[3]);
  }

  else if ( argc == 5)   
  { 
    ss << argv[1];
    ss>>debugLevel;

    ss << argv[2];
    ss>>inputDst;

    evtStart = atoi(argv[3]);
    evtEnd = atoi(argv[4]);
  }
  else
  {
    cout <<" Usage: alex <debugLevel> <IRENE/ALEX> <evtStart> <evtEnd>" << endl;
    return -1;
  }

  InitLogger("alex");
  SetDebugLevel(debugLevel,"alex");
  log4cpp::Category& klog = GetLogger("alex");

  if (evtStart <0) evtStart=0;

  if (inputDst != "IRENE" and inputDst != "ALEX")
  {
    klog << log4cpp::Priority::FATAL << " inputDst = " << inputDst; 
  }
  
  // to display histos online
  //TApplication* theApp = new TApplication("App", &argc, argv);

  auto aconf = AlgoConf();
  
  klog << log4cpp::Priority::INFO 
        << " Init Alex with debug level " << aconf.DebugLevel();
  alex::Alex::Instance().Init(aconf.DebugLevel());

  //histogram file
  char namePrefix[22];
  sprintf(namePrefix, "%i_", evtStart);
  string histoPath = PathFromStrings(aconf.HistoPath(), namePrefix + aconf.HistoName());
  klog << log4cpp::Priority::INFO 
        << " Init Histo file =" << histoPath;
  
  //Alex::Instance().InitHistoFile(histoPath);
  TFile* fHistoFile = new TFile(histoPath.c_str(),"RECREATE");
  klog << log4cpp::Priority::INFO 
       << " Instantiate and register algos " ;

  // Algos must be initiated before we open the irene TFile, so that their pointers
  // stay in the directory of the histogram file
  //--------

  
  aconf.RegisterAlgos();
  alex::Alex::Instance().InitAlgorithms();


  //----
  // Instantiate  Event

  if (inputDst == "IRENE")
    IreneLoop(evtStart, evtEnd);
  else 
    AlexLoop(evtStart, evtEnd);

  klog << log4cpp::Priority::INFO 
        << " Ending...  " ;
  alex::Alex::Instance().EndAlgorithms();
  
  fHistoFile->Write();
  fHistoFile->Close();
  
   //------------
  //theApp->Run();
   return 0;
}

void IreneLoop(int evtStart, int evtEnd)
{
  log4cpp::Category& klog = GetLogger("alex");
  irene::Event* ievt = new irene::Event();
  auto aconf = AlgoConf();

  //Get path, open DST file, set Tree
  string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());
  klog << log4cpp::Priority::INFO << "Open DST file =" << fp;

  
  TChain fEvtTree("EVENT");
  fEvtTree.Add(fp.c_str());   
  fEvtTree.SetBranchAddress("EventBranch", &ievt);
  
  klog << log4cpp::Priority::INFO << "number of entries in DST = " 
       << fEvtTree.GetEntries();
  klog << log4cpp::Priority::INFO << "number of events required = " 
       << aconf.EventsToRun();

  if(evtEnd < evtStart) evtEnd = std::min(aconf.EventsToRun(), 
    (int) fEvtTree.GetEntries());

  else evtEnd = std::min(evtEnd, (int) fEvtTree.GetEntries());
  klog << log4cpp::Priority::INFO << "number of events to run  = " 
       << (evtEnd - evtStart);
  
  //-----------Event loop --------
  ISvc::Instance().SetStartEvent(evtStart);
  int nb;
  klog << log4cpp::Priority::INFO 
       << " +++++++Start loop +++++++++++ " ;
  
  int nev =0;
  int npass = 0;
  int nfail = 0;
  for(int ivt = evtStart; ivt < evtEnd; ivt++)
  {
    // klog << log4cpp::Priority::INFO 
    //    << " Print Irene tree " ; 
    // fEvtTree.Print();

    nb = fEvtTree.GetEntry(ivt);
    ISvc::Instance().LoadEvent(ievt);
    ISvc::Instance().SetEvtNum(ivt);
 
    if (ivt%aconf.EventsToDebug() ==0)
    {
      klog << log4cpp::Priority::INFO 
           << "Read event " << ivt << " nb = " << nb;
    }

    klog << log4cpp::Priority::DEBUG 
         << " Executing algos  " ;

    nev++;
    bool test = alex::Alex::Instance().ExecuteAlgorithms();
    if (test == true)
      npass++;
    else
      nfail++;
    
  }

  klog << log4cpp::Priority::INFO  << "Read " << nev << " events" ;
  klog << log4cpp::Priority::INFO  << "Passed selection =" 
       << npass << " Failed selection =" << nfail ;

}

void AlexLoop(int evtStart, int evtEnd)
{
  log4cpp::Category& klog = GetLogger("alex");
  irene::Event* ievt = new irene::Event();
  auto aconf = AlgoConf();

  //Get path, open DST file, set Tree
  string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());
  klog << log4cpp::Priority::INFO << "Open DST file =" << fp;
  
  TChain fEvtTree("EVENT");
  fEvtTree.Add(fp.c_str());   
  fEvtTree.SetBranchAddress("EventBranch", &ievt);
  
  klog << log4cpp::Priority::INFO << "number of entries in DST = " 
       << fEvtTree.GetEntries();
  klog << log4cpp::Priority::INFO << "number of events required = " 
       << aconf.EventsToRun();

  if(evtEnd < evtStart) evtEnd = std::min(aconf.EventsToRun(), 
    (int) fEvtTree.GetEntries());

  else evtEnd = std::min(evtEnd, (int) fEvtTree.GetEntries());
  klog << log4cpp::Priority::INFO << "number of events to run  = " 
       << (evtEnd - evtStart);
  
  //-----------Event loop --------
  ISvc::Instance().SetStartEvent(evtStart);
  int nb;
  klog << log4cpp::Priority::INFO 
       << " +++++++Start loop +++++++++++ " ;
  
  int nev =0;
  int npass = 0;
  int nfail = 0;
  for(int ivt = evtStart; ivt < evtEnd; ivt++)
  {
    // klog << log4cpp::Priority::INFO 
    //    << " Print Irene tree " ; 
    // fEvtTree.Print();

    nb = fEvtTree.GetEntry(ivt);
    ISvc::Instance().LoadEvent(ievt);
    ISvc::Instance().SetEvtNum(ivt);
 
    if (ivt%aconf.EventsToDebug() ==0)
    {
      klog << log4cpp::Priority::INFO 
           << "Read event " << ivt << " nb = " << nb;
    }

    klog << log4cpp::Priority::DEBUG 
         << " Executing algos  " ;

    nev++;
    bool test = alex::Alex::Instance().ExecuteAlgorithms();
    if (test == true)
      npass++;
    else
      nfail++;
    
  }

  klog << log4cpp::Priority::INFO  << "Read " << nev << " events" ;
  klog << log4cpp::Priority::INFO  << "Passed selection =" 
       << npass << " Failed selection =" << nfail ;

}
