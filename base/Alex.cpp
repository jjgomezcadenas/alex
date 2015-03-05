
// ----------------------------------------------------------------------------
//  $Id: Alex.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/Alex.h>
#include <alex/LogUtil.h>
#include <alex/GDefs.h>


using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {


//--------------------------------------------------------------------
  void AlexManager::Init()
//--------------------------------------------------------------------
  {
    fAlexConfigData = new AlexConfigData();
  }
//--------------------------------------------------------------------
  void AlexManager::SetLevelDebug(string debugLevel)
//--------------------------------------------------------------------
  {
    InitLogger("Alex");
    SetDebugLevel(debugLevel,"Alex");
    log4cpp::Category& klog = GetLogger("Alex");
    klog << log4cpp::Priority::DEBUG << " Alex::Init() " ;
    
    fDebugLevel = debugLevel;

  }
//--------------------------------------------------------------------
  void AlexManager::RegisterAlgorithm(IAlgorithm* algo )
//--------------------------------------------------------------------
  {
    fIAlgo.push_back(algo);
  }
//--------------------------------------------------------------------
  void AlexManager::InitAlgorithms()
//--------------------------------------------------------------------
  {
    for (auto algo : fIAlgo)
      algo->Init();
  }
//--------------------------------------------------------------------  
  bool AlexManager::ExecuteAlgorithms()
//--------------------------------------------------------------------
  {
    for (auto algo : fIAlgo)
    {
      bool test = algo->Execute();
      if (test == false)
      {
        return false;
      }
    }
    return true;
  }
//--------------------------------------------------------------------
  void AlexManager::EndAlgorithms()
//--------------------------------------------------------------------
  {
    for (auto algo : fIAlgo)
      algo->End();
  }
//--------------------------------------------------------------------
  void AlexManager::ClearAlgorithms()
//--------------------------------------------------------------------
  {
    for (auto algo : fIAlgo)
      delete algo;
  }

//--------------------------------------------------------------------
  void AlexManager::ClearData()
//--------------------------------------------------------------------
  {
    for (auto& kv : fIData) 
    delete kv.second ;
  }
//--------------------------------------------------------------------
  string AlexManager::PrintConfigData()
//--------------------------------------------------------------------
  {
    std::stringstream s;
    s << std::endl;    
   
    s << "++++++Alex Config Data++++++\n";
    s  << " levelDebug (l) debug level (DEBUG, INFO, WARN, etc) = " 
         << fAlexConfigData->aLevelDebug << endl;
    s  << " mode (m) IRENE or ALEX depending of the input DST =" 
         << fAlexConfigData->aMode <<endl; 
    s  << " dst (d) path to IRENE or ALEX input DST = " 
         << fAlexConfigData->aDST <<endl;
    s  << " histo (h) path to output histo = " 
         << fAlexConfigData->aHisto << endl;
    s  << " startEvent (s) initial event number = " 
         << fAlexConfigData->aStartEvent << endl;
    s  << " finalEvent (f) final  event number = " 
         << fAlexConfigData->aFinalEvent << endl;
    s  << " events to debug (d)  = " 
         << fAlexConfigData->aEventDebug << endl;
    s  << " pressure (p) pressure in atms = " 
          << fAlexConfigData->aPressure << endl;
    s  << " bfield (b) magnetic field in tesla = " 
          << fAlexConfigData->aBField << endl;
    s  << " energyFWHM (e) energy resolution FWHM in fraction (0.005 = 5 percent) = " 
          << fAlexConfigData->aEnergyFWHM << endl; 
    s  << " xySigma (x) XY sigma resolution  in mm = " 
          << fAlexConfigData->aXYSigma << endl;
    s  << " zSigma (z) Z sigma resolution (or sparsing) in mm = " 
          << fAlexConfigData->aZSigma << endl; 

  return s.str();
  }
}

