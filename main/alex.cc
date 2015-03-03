// ireneMain example
// J.J. Gomez-Cadenas, August 2014


#include <alex/Alex.h>
#include <alex/ISvc.h>
#include <alex/ASvc.h>
#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/StringOperations.h>
#include <alex/AEvent.h>
#include "AlexConf.hh"

#include <TFile.h>
#include <TChain.h>


using namespace alex;
using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::ifstream;
using std::vector;

using std::stringstream;


void IreneLoop();
void AlexLoop();

int main(int argc, char **argv)
{

  cout << "-----Alex: Analysis of Electrons in Xenon-- called with args " << argc << endl;

  string debugLevel="DEBUG";
  string inputDst="IRENE";
  
  

  if( argc == 2)   
  {  
    stringstream ss;
    ss << argv[1];
    ss>>debugLevel;
  }
  else if ( argc == 3)   
  { 
    {
      stringstream ss;
      ss << argv[1];
      ss>>debugLevel;
    } 
    {
      stringstream ss;
      ss << argv[2];
      ss>>inputDst;
    }
  }
  // else if ( argc == 4)   
  // { 
  //   ss << argv[1];
  //   ss>>debugLevel;

  //   ss << argv[2];
  //   ss>>inputDst;

  //   evtStart = atoi(argv[3]);
  // }

  // else if ( argc == 5)   
  // { 
  //   ss << argv[1];
  //   ss>>debugLevel;

  //   ss << argv[2];
  //   ss>>inputDst;

  //   evtStart = atoi(argv[3]);
  //   evtEnd = atoi(argv[4]);
  // }
  else
  {
    //cout <<" Usage: alex <debugLevel> <IRENE/ALEX> <evtStart> <evtEnd>" << endl;
    cout <<" Usage: alex <debugLevel> <IRENE/ALEX>" << endl;
    return -1;
  }


  InitLogger("alex");
  SetDebugLevel(debugLevel,"alex");
  log4cpp::Category& klog = GetLogger("alex");

  if (inputDst != "IRENE" and inputDst != "ALEX")
  {
    klog << log4cpp::Priority::FATAL << " inputDst = " << inputDst; 
    exit(-1);
  }
  
  klog << log4cpp::Priority::INFO << " inputDst = " << inputDst;

  // to display histos online
  //TApplication* theApp = new TApplication("App", &argc, argv);

  auto aconf = AlexConf();
  
  klog << log4cpp::Priority::INFO 
        << " Init Alex with debug level " << aconf.DebugLevel();
  alex::Alex::Instance().Init(aconf.DebugLevel());

  //histogram file
  // char namePrefix[22];
  // sprintf(namePrefix, "%i_", evtStart);
  string histoPath = PathFromStrings(aconf.HistoPath(), aconf.HistoName());
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
    IreneLoop();
  else 
    AlexLoop();

  klog << log4cpp::Priority::INFO 
        << " Ending...  " ;
  alex::Alex::Instance().EndAlgorithms();
  
  fHistoFile->Write();
  fHistoFile->Close();
  
   //------------
  //theApp->Run();
   return 0;
}

void IreneLoop()
{
  log4cpp::Category& klog = GetLogger("alex");
  irene::Event* ievt = new irene::Event();
  auto aconf = AlexConf();

  //init IreneSvc with the same level of debug than alex.
  ISvc::Instance().Init(GetDebugLevel("alex"), aconf.pEnergyResolutionFWHM);
  
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

  int evtStart = (int) aconf.pEventStart;
  int evtEnd = (int) aconf.pEventEnd;

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
           << "IRENE::Read event " << ivt << " nb = " << nb;
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

void AlexLoop()
{
  
  log4cpp::Category& klog = GetLogger("alex");
  alex::AEvent* ievt = new alex::AEvent();
  auto aconf = AlexConf();
  int evtStart = (int) aconf.pEventStart;
  int evtEnd = (int) aconf.pEventEnd;

  //init AlesSvc with the same level of debug than alex.
  ASvc::Instance().Init(GetDebugLevel("alex"), evtStart);
  
  //Get path, open DST file, set Tree
  string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());
  klog << log4cpp::Priority::INFO << "Open DST file =" << fp;

  TChain fEvtTree("AEVENT");
  fEvtTree.Add(fp.c_str());   
  fEvtTree.SetBranchAddress("ABRANCH", &ievt);
  
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
  
  int nb;
  klog << log4cpp::Priority::INFO 
       << " +++++++Start loop +++++++++++ " ;
  
  int nev =0;
  int npass = 0;
  int nfail = 0;
  for(int ivt = evtStart; ivt < evtEnd; ivt++)
  {

    nb = fEvtTree.GetEntry(ivt);
    ASvc::Instance().LoadEvent(ievt);
 
    if (ivt%aconf.EventsToDebug() ==0)
    {
      klog << log4cpp::Priority::INFO 
           << "ALEX::Read event " << ivt << " nb = " << nb;
      klog << log4cpp::Priority::INFO 
       << " Print ALEX tree " ; 
      fEvtTree.Print();
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
