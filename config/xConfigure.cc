// exConfigure
// Configures the setup to run the algos in folder example
// JJ March, 2015



#include <alex/GDefs.h>
#include <alex/StringOperations.h>
#include <alex/LogUtil.h>
#include "AlexConfigure.h"

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

using namespace alex;
using std::stringstream;
using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::ifstream;
using std::vector;

class XConfData {
  public:
    XConfData() : aAlgoConfigPath(""), aSrcDirPath(""),aLevelDebug("DEBUG")
    {};
    ~XConfData(){};
  
    std::string aAlgoConfigPath; // path to AlgoConfig file
    std::string aSrcDirPath; // path to src directory (where the algo.cpp code sits)
    string aLevelDebug; // follows Log4CPP conventions DEBUG, INFO, WARN
  };

XConfData ParseXConfCommandLine(int argc, char **argv);
string PrintXConfUsage();
string PrintXConfData(const XConfData& xcd);

int main(int argc, char **argv)
{
	
  cout << "xConfigure: a program to configure Alex" << endl;

  XConfData xcd = ParseXConfCommandLine(argc,argv);
  cout << PrintXConfData(xcd);


  string debugLevel = xcd.aLevelDebug;
  string pathToAlgos = xcd.aSrcDirPath;
  string pathAlgoConf = xcd.aAlgoConfigPath;
  string registerAlgos="RegisterAlgos.cxx";
  string registerAlgosHeader="RegisterAlgosHeader.hh";
  string algoHeader="AlgoHeaders.hh";
  string algoCpp="AlgoAux.cxx";   //configuration of algos 
 
  InitLogger("xConfigure");
  SetDebugLevel(debugLevel,"xConfigure");
  log4cpp::Category& klog = GetLogger("xConfigure");

  AlexConfigure::Instance().Init(debugLevel);

  klog << log4cpp::Priority::INFO 
        << " xConfigure: path to Algos (src)=" << pathToAlgos;

  klog << log4cpp::Priority::INFO 
        << " xConfigure: path to AlgoConfig.xml =" << pathAlgoConf;


  AlexConfigure::Instance().ParseConfiguration(pathAlgoConf);
	
	{
  	string pathRegisterAlgos = PathFromStrings(pathToAlgos,registerAlgos);
  	klog << log4cpp::Priority::INFO 
    	    << " Write registerAlgo file at=" << pathRegisterAlgos;
		std::ofstream out(pathRegisterAlgos.c_str());
  	out << AlexConfigure::Instance().WriteRegisterAlgos();
  	out.close();
	}
  {
    string pathRegisterAlgoHeader = PathFromStrings(pathToAlgos,registerAlgosHeader);
    klog << log4cpp::Priority::INFO 
          << " Write Register algoHeader file at=" << pathRegisterAlgoHeader;
    std::ofstream out(pathRegisterAlgoHeader.c_str());
    out << AlexConfigure::Instance().WriteRegisterAlgosHeader();
    out.close();
  }
	{
  	string pathAlgoHeader = PathFromStrings(pathToAlgos,algoHeader);
  	klog << log4cpp::Priority::INFO 
    	    << " Write algoHeader file at=" << pathAlgoHeader;
		std::ofstream out(pathAlgoHeader.c_str());
  	out << AlexConfigure::Instance().WriteAlgoHeaderFile();
  	out.close();
	}
  
	std::vector<std::string> ah = AlexConfigure::Instance().WriteAlgoHeaders();
	size_t i=0;
	for (auto algoName : AlexConfigure::Instance().AlgoNames()) 
	{
		string algoHeader = MergeStrings(algoName,".hh");
  	string pathAlgoHeader = PathFromStrings(pathToAlgos,algoHeader);
  	klog << log4cpp::Priority::INFO 
    	    << " Write Algo header file at=" << pathAlgoHeader;
		std::ofstream out(pathAlgoHeader.c_str());
  	out << ah.at(i);
  	out.close();
  	i++;
	}
	{
  	string pathAlgoCpp = PathFromStrings(pathToAlgos,algoCpp);
  	klog << log4cpp::Priority::INFO 
    	    << " Write Algo cpp file at=" << pathAlgoCpp;
		std::ofstream out(pathAlgoCpp.c_str());
  	out << AlexConfigure::Instance().WriteAlgoCPP() ;
  	out.close();
	}

  return 0;
 }
 
//--------------------------------------------------------------------
 XConfData ParseXConfCommandLine(int argc, char **argv)
//--------------------------------------------------------------------
{
  static const char *optString = "l:a:s:H?";
  int opt = 0;
  int longIndex = 0;
  auto xcd = XConfData();

  static struct option long_options[] = 
    {
      {"levelDebug",    required_argument, 0,  'l' },
      {"algoConfigPath",    required_argument, 0,  'a' },
      {"SrcDirPath",    required_argument, 0,  's' },
      {"help",    no_argument, 0,  'H' },
      {0,         0,                 0,  0 }
    };

    
  opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  while( opt != -1 ) 
  {
    switch( opt ) 
    {
      case 'a':
        {
          stringstream ss;
          ss << optarg;
          ss >> xcd.aAlgoConfigPath;
        }
      break;
      case 'l':
        {
          stringstream ss;
          ss << optarg;
          ss >> xcd.aLevelDebug;
        }
      break;
      case 's':
        {
          stringstream ss;
          ss << optarg;
          ss >> xcd.aSrcDirPath;
        }
      break; 
      
      case 'H':   /* fall-through is intentional */
      case '?':
        cout << PrintXConfUsage() << endl;
        exit(-1);
      break;         
      default:
        /* You won't actually get here. */
      break;
    }
        
    opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  }
  return xcd;
}
//--------------------------------------------------------------------
string PrintXConfUsage()
//--------------------------------------------------------------------
{
  std::stringstream s;
  s << std::endl;    
  s << " usage: xConfigure -o (--lo) " << endl;
  s << " where -o denotes a short option and --lo denotes a long option " << endl;
  s << " available long (short) options are:" << endl;
  s << " --algoConfigPath (-a): Full Path to AlgoConf.xml" << endl;
  s << " --srcDirPath (-s): Path to source directory (algo.cpp files) " << endl;
  s << " --levelDebug (-l): debug level (DEBUG, INFO, WARN, etc)" << endl;
     
  return s.str();
}

//--------------------------------------------------------------------
  string PrintXConfData(const XConfData& xcd)
//--------------------------------------------------------------------
  {
    std::stringstream s;
    s << std::endl;    
   
    s << "++++++Alex Config Data++++++\n";
    s << "Path to AlgoConf.xml = " 
          << xcd.aAlgoConfigPath << endl;
    s << "Path to Alex src (source directory where algo.cpp is found) = " 
          << xcd.aSrcDirPath << endl;
    s  << " levelDebug (l) debug level (DEBUG, INFO, WARN, etc) = " 
         << xcd.aLevelDebug << endl;
 
    return s.str();
  }