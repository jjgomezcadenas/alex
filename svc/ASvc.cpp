
// ----------------------------------------------------------------------------
//  $Id: ASvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/ASvc.h>
#include <alex/VectorOperations.h>
#include <alex/LogUtil.h>
#include <alex/AEvent.h>

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {

//--------------------------------------------------------------------
  void AlexService::Init(std::string debugLevel)
//--------------------------------------------------------------------
  {
    fDebugLevel = debugLevel;
    InitLogger("Asvc");
    SetDebugLevel(fDebugLevel,"Asvc");

    
    log4cpp::Category& klog = GetLogger("Asvc");
    klog << log4cpp::Priority::INFO << "AlexService Initialized" ;

    fEvt= new AEvent();
    
  }


  //--------------------------------------------------------------------
  void AlexService::SetLevelDebug(std::string debugLevel)
  //--------------------------------------------------------------------
  {

    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel,"Asvc");
    
  }


//--------------------------------------------------------------------
  void AlexService::LoadEvent(const AEvent* ievt)
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("Asvc");
    klog << log4cpp::Priority::DEBUG << "***** AlexManager::Load Event "

    fEvt = new AEvent(*ievt); 
  }

//--------------------------------------------------------------------
  void AlexService::ClearEvent()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("Asvc");
    klog << log4cpp::Priority::DEBUG << "***** AlexManager::Clear Event "

    delete fEvt ; 
    
  }
}
