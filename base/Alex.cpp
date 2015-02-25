
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
  void AlexManager::Init(string debugLevel)
//--------------------------------------------------------------------
  {
    InitLogger("Alex");
    SetDebugLevel(debugLevel,"Alex");
    fDebugLevel = debugLevel;

    log4cpp::Category& klog = GetLogger("Alex");
    klog << log4cpp::Priority::DEBUG << " Alex::Init() " ;

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
}

