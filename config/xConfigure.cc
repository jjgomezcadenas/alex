// exConfigure
// Configures the setup to run the algos in folder example
// August, 2014



#include <alex/GDefs.h>
#include <alex/StringOperations.h>
#include <alex/LogUtil.h>
#include "AlexConfigure.h"

using namespace alex;
using std::stringstream;
using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::ifstream;
using std::vector;


int main(int argc, char **argv)
{
	
  cout << "xConfigure: a program to configure Alex" << endl;

  if( argc != 5)   
  { 
    cout <<" Usage: xConfigure <debugLevel> <pathToXml> <pathToAlgos> <pathToAlex>" << endl;
    return -1;
  }

  string debugLevel;
  string pathToAlgos;
  string pathToXml;
  string pathToAlex;

  {
    stringstream ss;
    ss << argv[1];
    ss>>debugLevel;
  }
  {
    stringstream ss;
    ss << argv[2];
    ss>>pathToXml;
  }
  {
    stringstream ss;
    ss << argv[3];
    ss>>pathToAlgos;
  }
  {
    stringstream ss;
    ss << argv[4];
    ss>>pathToAlex;
  }

  InitLogger("xConfigure");
  SetDebugLevel(debugLevel,"xConfigure");
  log4cpp::Category& klog = GetLogger("xConfigure");

  AlexConfigure::Instance().Init(debugLevel);

  klog << log4cpp::Priority::INFO 
        << " xConfigure: path to Algos (src)=" << pathToAlgos;

  klog << log4cpp::Priority::INFO 
        << " xConfigure: path to xml =" << pathToXml;

  klog << log4cpp::Priority::INFO 
        << " xConfigure: path to xml =" << pathToAlex;
  
  
  
	//Define files
	
	string alexConf="AlexConfig.xml";  //Alex configuration (input) 

  //generated files
	string aConfHeader="AlexConf.hh";  //configuration of alex (main)    
	string aConfCpp="AlexConf.cxx";    //configuration of alex (main)    
	string algoCpp="AlgoAux.cxx";   //configuration of algos    
	string registerAlgos="RegisterAlgos.cxx"; //configuration of algos
  //string registerAlgosHeader="RegisterAlgosHeader.hh";
	string algoHeader="AlgoHeaders.hh";
  
  
  string pathAlexConf = PathFromStrings(pathToXml,alexConf);
  klog << log4cpp::Priority::INFO 
        << " Parse Alex xml configuration files located at=" << pathAlexConf;

	AlexConfigure::Instance().ParseConfiguration(pathAlexConf);
	
	{
  	string pathAConfHeader = PathFromStrings(pathToAlex,aConfHeader);
  	klog << log4cpp::Priority::INFO 
    	    << " Write AlgoConf header file at=" << pathAConfHeader;

		std::ofstream out(pathAConfHeader.c_str());
  	out << AlexConfigure::Instance().WriteAConfHeader();
  	out.close();
	}

	{
  	string pathAConfCpp = PathFromStrings(pathToAlex,aConfCpp);
  	klog << log4cpp::Priority::INFO 
    	    << " Write AlgoConf cpp file at=" << pathAConfCpp;
		std::ofstream out(pathAConfCpp.c_str());
  	out << AlexConfigure::Instance().WriteAConfCPP();
  	out.close();
	}
	{
  	string pathRegisterAlgos = PathFromStrings(pathToAlgos,registerAlgos);
  	klog << log4cpp::Priority::INFO 
    	    << " Write registerAlgo file at=" << pathRegisterAlgos;
		std::ofstream out(pathRegisterAlgos.c_str());
  	out << AlexConfigure::Instance().WriteRegisterAlgos();
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
  // {
  //   string pathRegisterAlgoHeader = PathFromStrings(pathToAlgos,registerAlgosHeader);
  //   klog << log4cpp::Priority::INFO 
  //         << " Write Register algoHeader file at=" << pathRegisterAlgoHeader;
  //   std::ofstream out(pathRegisterAlgoHeader.c_str());
  //   out << AlexConfigure::Instance().WriteRegisterAlgosHeader();
  //   out.close();
  // }


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