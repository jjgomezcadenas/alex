// ireneMain example
// J.J. Gomez-Cadenas, August 2014


#include <alex/Alex.h>
#include <alex/ISvc.h>
#include <alex/ASvc.h>
#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/StringOperations.h>
#include <alex/AEvent.h>
#include "RegisterAlgosHeader.hh"

#include <TFile.h>
#include <TChain.h>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>


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

void ParseAlexCommandLine(int argc, char **argv);
string PrintAlexUsage();

/*
AlexConfigData
--------------
  string aAlgoPath; // pat to AlgoConfig file
  string aLevelDebug; // follows Log4CPP conventions DEBUG, INFO, WARN
  string aMode; // running mode: can be IRENE/TALEX/RALEX/ALEX depending of the input DST
  string aDST; // input DST
  string aHisto; //output histogram file
  int aStartEvent, aFinalEvent, aEventDebug; // configures the number of events to run
  double aPressure, aBField, aEnergyFWHM, aXYSigma, aZSigma; //various param

*/

int main(int argc, char **argv)
{

  cout << "-----Alex: Analysis of Electrons in Xenon-- called with args " << argc << endl;
  
  Alex::Instance().Init();
  
  ParseAlexCommandLine(argc,argv);
  cout << Alex::Instance().PrintConfigData();

  
  InitLogger("alex");
  SetDebugLevel(Alex::Instance().ConfigData().aLevelDebug,"alex");
  Alex::Instance().SetLevelDebug(Alex::Instance().ConfigData().aLevelDebug);

  log4cpp::Category& klog = GetLogger("alex");

  if (Alex::Instance().ConfigData().aMode != "IRENE" and 
      Alex::Instance().ConfigData().aMode != "ALEX")
  {
    klog << log4cpp::Priority::FATAL << " Mode (must be IRENE/ALEX) = " 
    << Alex::Instance().ConfigData().aMode; 
    exit(-1);
  }
  
  string histoPath = Alex::Instance().ConfigData().aHisto;

  TFile* fHistoFile = new TFile(histoPath.c_str(),"RECREATE");
  klog << log4cpp::Priority::INFO 
       << " Instantiate and register algos " ;

  // Algos must be initiated before we open the irene TFile, so that their pointers
  // stay in the directory of the histogram file
  //--------

  
  RegisterAlgos();
  Alex::Instance().InitAlgorithms();

  //----
  // Instantiate  Event

  if (Alex::Instance().ConfigData().aMode == "IRENE")
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
  
  //init IreneSvc 
  ISvc::Instance().Init(Alex::Instance().ConfigData().aLevelDebug, 
                        Alex::Instance().ConfigData().aEnergyFWHM);
  
  //Get path, open DST file, set Tree
  //string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());

  string fp = Alex::Instance().ConfigData().aDST;
  klog << log4cpp::Priority::INFO << "Open DST file =" << fp;

  
  TChain fEvtTree("EVENT");
  fEvtTree.Add(fp.c_str());   
  fEvtTree.SetBranchAddress("EventBranch", &ievt);
  
  klog << log4cpp::Priority::INFO << "number of entries in DST = " 
       << fEvtTree.GetEntries();

  int evtStart = Alex::Instance().ConfigData().aStartEvent;
  int evtEnd = Alex::Instance().ConfigData().aFinalEvent;
  
  if(evtEnd < evtStart) 
    evtEnd = (int) fEvtTree.GetEntries();
  else 
    evtEnd = std::min(evtEnd, (int) fEvtTree.GetEntries());
  
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
 
    if (ivt%Alex::Instance().ConfigData().aEventDebug ==0)
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

  int evtStart = Alex::Instance().ConfigData().aStartEvent;
  int evtEnd = Alex::Instance().ConfigData().aFinalEvent;

  //init AlesSvc with the same level of debug than alex.
  ASvc::Instance().Init(Alex::Instance().ConfigData().aLevelDebug, evtStart);

  //Get path, open DST file, set Tree
  //string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());

  string fp = Alex::Instance().ConfigData().aDST;
  klog << log4cpp::Priority::INFO << "Open DST file =" << fp;

  TChain fEvtTree("AEVENT");
  fEvtTree.Add(fp.c_str());   
  fEvtTree.SetBranchAddress("ABRANCH", &ievt);
  
  klog << log4cpp::Priority::INFO << "number of entries in DST = " 
       << fEvtTree.GetEntries();

  if(evtEnd < evtStart) 
    evtEnd = (int) fEvtTree.GetEntries();
  else 
    evtEnd = std::min(evtEnd, (int) fEvtTree.GetEntries());
  
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
 
    if (ivt%Alex::Instance().ConfigData().aEventDebug ==0)
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

void ParseAlexCommandLine(int argc, char **argv)
{
  static const char *optString = "l:m:D:h:s:f:D:p:b:e:x:z:H?";
  int opt = 0;
  int longIndex = 0;
  
  static struct option long_options[] = 
    {
      {"levelDebug",    required_argument, 0,  'l' },
      {"mode",  required_argument,       0,  'm'},
      {"dst",  required_argument, 0,  'D'},
      {"histo", required_argument,       0,  'h'},
      {"startEvent", required_argument,       0,  's'},
      {"finalEvent", required_argument,       0,  'f'},
      {"eventsDebug", required_argument,       0,  'd'},
      {"pressure",  required_argument, 0, 'p'},
      {"bfield",    required_argument, 0,  'b' },
      {"energyFWHM",    required_argument, 0,  'e' },
      {"xySigma",    required_argument, 0,  'x' },
      {"zSigma",    required_argument, 0,  'z' },
      {"help",    no_argument, 0,  'H' },
      {0,         0,                 0,  0 }
    };

    
  opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  while( opt != -1 ) 
  {
    switch( opt ) 
    {
      case 'l':
        {
          stringstream ss;
          ss << optarg;
          ss >> Alex::Instance().ConfigData().aLevelDebug;
        }
      break;
      case 'm':
        {
          stringstream ss;
          ss << optarg;
          ss >> Alex::Instance().ConfigData().aMode;
        }
      break; 
      case 'D':
        {
          stringstream ss;
          ss << optarg;
          ss >> Alex::Instance().ConfigData().aDST;
        }
      break;
      case 'h':
        {
          stringstream ss;
          ss << optarg;
          ss >> Alex::Instance().ConfigData().aHisto;
        }
      break;
      case 'p':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aPressure = std::stod(data);
        }
      break;
      case 'b':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aBField = std::stod(data);
        }
      break;
      case 'e':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aEnergyFWHM = std::stod(data);
        }
      break;
      case 'x':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aXYSigma = std::stod(data);
        }
      break;
      case 'z':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aZSigma = std::stod(data);
        }
      break;
      case 's':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aStartEvent = std::stoi(data);
        }
      break;
      case 'f':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aFinalEvent = std::stoi(data);
        }
      case 'd':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          Alex::Instance().ConfigData().aEventDebug = std::stoi(data);
        }
      break;
      case 'H':   /* fall-through is intentional */
      case '?':
        cout << PrintAlexUsage() << endl;
        exit(-1);
      break;         
      default:
        /* You won't actually get here. */
      break;
    }
        
    opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  }
}

string PrintAlexUsage()
{
  std::stringstream s;
  s << std::endl;    
  s << " usage: xAlex -o (--lo) " << endl;
  s << " where -o denotes a short option and --lo denotes a long option " << endl;
  s << " available long (short) options are:" << endl;
  s << " --levelDebug (-l): debug level (DEBUG, INFO, WARN, etc)" << endl;
  s << " --mode (-m): IRENE or ALEX depending of the input DST" << endl; 
  s << " --dst (-D): path to IRENE or ALEX input DST" << endl;
  s << " --histo (-h): path to output histo" << endl;
  s << " --startEvent (-s): start event number" << endl;
  s << " --finalEvent (-f): final  event number" << endl;
  s <<" --eventsDebug (-d): number of events to debug" << endl;
  s << " --pressure (-p): pressure in atms" << endl;
  s << " --bfield (-b): magnetic field in tesla" << endl;
  s << " --energyFWHM (-e): energy resolution FWHM in fraction (0.005 = 5 percent)" << endl; 
  s << " --xySigma (-x): XY sigma resolution  in mm " << endl;
  s << " --zSigma (-z): Z sigma resolution (or sparsing)  in mm " << endl;
  s << " --help (-h): This help message " << endl; 
    
  return s.str();
}
    

