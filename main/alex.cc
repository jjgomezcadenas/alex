// ireneMain example
// J.J. Gomez-Cadenas, August 2014

#include <TROOT.h>
#include <alex/Alex.h>
#include <alex/ISvc.h>
#include <alex/ASvc.h>
#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/StringOperations.h>
#include <alex/AEvent.h>
#include <alex/AXConfigData.h>
#include <alex/AXRun.h>
#include <TBrowser.h>
#include "RegisterAlgosHeader.hh"


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


int main(int argc, char **argv)
{
  char userInput;
  cout << "-----Alex: Analysis of Electrons in Xenon-- "  << endl;
  
  Alex::Instance().Init();

  ParseAlexCommandLine(argc,argv);

  //Get run folder data

  AXRun* axr = (AXRun*) Alex::Instance().GetObject("/FAlex/FRun/AXRunData");
  cout << "++Run data+++" << endl;
  cout << axr->PrintInfo() << endl;

  AXConfigData* axcd = (AXConfigData*) Alex::Instance().GetObject("/FAlex/FConfig/AXConfigData");
  cout << "++Config data+++" << endl;
  cout << axcd->PrintInfo() << endl;

  std::cout << "type any character and return to continue" << std::endl;
  std::cin >> userInput;
  
  InitLogger("alex");
  SetDebugLevel(axcd->GetLevelDebug(),"alex");
  Alex::Instance().SetLevelDebug(axcd->GetLevelDebug());

  log4cpp::Category& klog = GetLogger("alex");

  if (axcd->GetMode() != "IRENE" and axcd->GetMode() != "ALEX")
  {
    klog << log4cpp::Priority::FATAL << " Mode (must be IRENE/ALEX) = " 
    << axcd->GetMode(); 
    exit(-1);
  }

  klog << log4cpp::Priority::INFO << "+++Create Histo file " ;

  TFile* histoFile = new TFile(axcd->GetHistoFile().c_str(),"RECREATE");
  histoFile->SetName("HistoFile");
  Alex::Instance().SetHistoFile(histoFile);

  // TFolder* histoFolder = Alex::Instance().GetFolder("/FAlex/FHisto");
  // histoFolder->Add(histoFile);

  // output tree

  string filename = "/Users/jjgomezcadenas/Development/devnext/DATA/DST/ALEX/test.root";

  klog << log4cpp::Priority::INFO << " Alex output DST file " 
    << filename;

  auto dstFile = new TFile(filename.c_str(), "RECREATE");
  dstFile->SetName("DstFile");

  klog << log4cpp::Priority::DEBUG << " Create DST Tree " ;

  auto dstTree = new TTree("AlexDST","AlexDst");
  Alex::Instance().SetDstTree(dstTree);

  //set up branches for RUN and Config data

  int nb = dstTree->Branch("/FAlex/FRun");
  klog << log4cpp::Priority::INFO << " number of branches in RUN folder " << nb;

  //outTree->SetBranchAddress("/FAlex/FRun", &axr);

  nb = dstTree->Branch("/FAlex/FConfig");
  klog << log4cpp::Priority::INFO << " number of branches in Config folder " << nb;
  dstTree->Print();

  // std::cout << "type any character and return to continue" << std::endl;
  // std::cin >> userInput;

  // outTree->Fill();

  // outDstFile->Write();
  // outDstFile->Close();

  // std::cout << "type any character and return to continue" << std::endl;
  // std::cin >> userInput;

    // klog << log4cpp::Priority::DEBUG << " Set Branch to event " ;

    // fAevtTree->Branch("AEvent", "alex::AEvent",&fAevent);


  
  klog << log4cpp::Priority::DEBUG 
       << " Instantiate and register algos " ;

  // Algos must be initiated before we open the irene TFile, so that their pointers
  // stay in the directory of the histogram file
  //--------

  
  RegisterAlgos();
  Alex::Instance().InitAlgorithms();

  klog << log4cpp::Priority::DEBUG 
       << " Algos registered " ;

  //----
  // Instantiate  Event

  if (axcd->GetMode()  == "IRENE")
  {
    klog << log4cpp::Priority::DEBUG 
       << " Entering Irene Loop " ;
    IreneLoop();
  }
  else 
    AlexLoop();

  klog << log4cpp::Priority::INFO 
        << " Ending...  " ;
  alex::Alex::Instance().EndAlgorithms();
  
  histoFile->Write();
  histoFile->Close();
  
   //------------
  //theApp->Run();
   return 0;
}

void IreneLoop()
{
  log4cpp::Category& klog = GetLogger("alex");

  klog << log4cpp::Priority::DEBUG 
       << " instating irene::Event() " ;

  irene::Event* ievt = new irene::Event();

  klog << log4cpp::Priority::DEBUG 
       << " Retrieving pointers to AXRun and AXConfigData " ;

  AXRun* axr = (AXRun*) Alex::Instance().GetObject("/FAlex/FRun/AXRunData");
  AXConfigData* axcd = (AXConfigData*) Alex::Instance().GetObject("/FAlex/FConfig/AXConfigData");
  
  //init IreneSvc 

  klog << log4cpp::Priority::DEBUG
       << " Init IreneSvc with debug level = " 
       <<axcd->GetLevelDebug() << " and energyFWHM = "
       <<axr->GetEnergyFWHM();

  ISvc::Instance().Init(axcd->GetLevelDebug(), axr->GetEnergyFWHM());
  
  //Get path, open DST file, set Tree
  //string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());

  string fp = axcd->GetDstFile();
  klog << log4cpp::Priority::INFO << "Open Irene DST file =" << fp;

  
  // TChain iTree("EVENT");
  // iTree.Add(fp.c_str());   
  // iTree.SetBranchAddress("EventBranch", &ievt);

  TChain* iTree = new TChain("EVENT","Irene Event");
  iTree->Add(fp.c_str());   
  iTree->SetBranchAddress("EventBranch", &ievt);

  iTree->SetName("IreneTree");

  TFolder* treeFolder = Alex::Instance().GetFolder("/FAlex/FTree");
  treeFolder->Add(iTree);
  
  klog << log4cpp::Priority::INFO << "number of entries in DST = " 
       << iTree->GetEntries();

  int evtStart =axcd->GetStartEvent();
  int evtEnd = axcd->GetFinalEvent();

  
  if(evtEnd < evtStart) 
    evtEnd = (int) iTree->GetEntries();
  else 
    evtEnd = std::min(evtEnd, (int) iTree->GetEntries());
  
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

    nb = iTree->GetEntry(ivt);
    ISvc::Instance().LoadEvent(ievt);
    ISvc::Instance().SetEvtNum(ivt);
 
    if (ivt%axcd->GetEventDebug() ==0)
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
}
// void AlexLoop()
// {
  
//   log4cpp::Category& klog = GetLogger("alex");
//   alex::AEvent* ievt = new alex::AEvent();

//   int evtStart = Alex::Instance().ConfigData().aStartEvent;
//   int evtEnd = Alex::Instance().ConfigData().aFinalEvent;

//   //init AlesSvc with the same level of debug than alex.
//   ASvc::Instance().Init(Alex::Instance().ConfigData().aLevelDebug, evtStart);

//   //Get path, open DST file, set Tree
//   //string fp = PathFromStrings(aconf.DstPath(),aconf.DstName());

//   string fp = Alex::Instance().ConfigData().aDST;
//   klog << log4cpp::Priority::INFO << "Open DST file =" << fp;

//   TChain fEvtTree("AEVENT");
//   fEvtTree.Add(fp.c_str());   
//   fEvtTree.SetBranchAddress("ABRANCH", &ievt);
  
//   klog << log4cpp::Priority::INFO << "number of entries in DST = " 
//        << fEvtTree.GetEntries();

//   if(evtEnd < evtStart) 
//     evtEnd = (int) fEvtTree.GetEntries();
//   else 
//     evtEnd = std::min(evtEnd, (int) fEvtTree.GetEntries());
  
//   klog << log4cpp::Priority::INFO << "number of events to run  = " 
//        << (evtEnd - evtStart);
  
//   //-----------Event loop --------
  
//   int nb;
//   klog << log4cpp::Priority::INFO 
//        << " +++++++Start loop +++++++++++ " ;
  
//   int nev =0;
//   int npass = 0;
//   int nfail = 0;
//   for(int ivt = evtStart; ivt < evtEnd; ivt++)
//   {

//     nb = fEvtTree.GetEntry(ivt);
//     ASvc::Instance().LoadEvent(ievt);
 
//     if (ivt%Alex::Instance().ConfigData().aEventDebug ==0)
//     {
//       klog << log4cpp::Priority::INFO 
//            << "ALEX::Read event " << ivt << " nb = " << nb;
//       klog << log4cpp::Priority::INFO 
//        << " Print ALEX tree " ; 
//       fEvtTree.Print();
//     }

//     klog << log4cpp::Priority::DEBUG 
//          << " Executing algos  " ;

//     nev++;
//     bool test = alex::Alex::Instance().ExecuteAlgorithms();
//     if (test == true)
//       npass++;
//     else
//       nfail++;
    
//   }

//   klog << log4cpp::Priority::INFO  << "Read " << nev << " events" ;
//   klog << log4cpp::Priority::INFO  << "Passed selection =" 
//        << npass << " Failed selection =" << nfail ;

// }

void ParseAlexCommandLine(int argc, char **argv)
{
  static const char *optString = "l:m:D:h:s:f:D:p:b:e:x:z:E:H?";
  int opt = 0;
  int longIndex = 0;

  AXRun* axr = new AXRun();
  axr->SetName("AXRunData");

  AXConfigData* axcd = new AXConfigData();
  axcd->SetName("AXConfigData");
  
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
      {"emin",    required_argument, 0,  'E' },
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
          string levelDebug;
          ss >> levelDebug;
          axcd->SetLevelDebug(levelDebug);

        }
      break;
      case 'm':
        {
          stringstream ss;
          ss << optarg;
          string mode;
          ss >> mode;
          axcd->SetMode(mode);
        }
      break; 
      case 'D':
        {
          stringstream ss;
          ss << optarg;
          string dst;
          ss >> dst;
          axcd->SetDstFile(dst);
        }
      break;
      case 'h':
        {
          stringstream ss;
          ss << optarg;
          string histo;
          ss >> histo;
          axcd->SetHistoFile(histo);
        }
      break;
      case 'p':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetPressure(std::stod(data));
        }
      break;
      case 'b':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetBField(std::stod(data));
        }
      break;
      case 'e':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetEnergyFWHM(std::stod(data)) ;
        }
      break;
      case 'x':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetXYSigma(std::stod(data));
        }
      break;
      case 'z':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetZSigma(std::stod(data));
        }
      break;
      case 'E':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axr->SetEMin(std::stod(data)) ;
        }
      break;
      case 's':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axcd->SetStartEvent(std::stoi(data));
        }
      break;
      case 'f':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axcd->SetFinalEvent(std::stoi(data));
        }
      case 'd':
        {
          stringstream ss;
          string data;
          ss << optarg;
          ss >> data;
          axcd->SetEventDebug(std::stoi(data));
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

  
  TFolder* runFolder = Alex::Instance().GetFolder("/FAlex/FRun");

  // cout << "Try runFolder" << endl;

  // TFolder* runFolder = (TFolder*) gROOT->FindObjectAny("/FAlex/FRun");

  //cout << "Try ConfigFolder" << endl;
  TFolder* configFolder = Alex::Instance().GetFolder("/FAlex/FConfig");

  //cout << "Add axr ro runFolder" << endl;
  runFolder->Add(axr);

  //cout << "Add axcd to configFolder" << endl;
  configFolder->Add(axcd);

  cout << "Done Parsing options" << endl;
  
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
  s << " --emin (-E): minimum visible energy in KeV " << endl;
  s << " --help (-h): This help message " << endl; 
    
  return s.str();
}
    

