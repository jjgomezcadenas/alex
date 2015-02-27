
// ----------------------------------------------------------------------------
///  \file   AEvent.cpp
///  \brief  Used for persistency
///
///  \author   <JJ>
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: Event.h 9914 2014-07-13 07:51:27Z gomez $
///
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#include <alex/AEvent.h>
#include <alex/AParticle.h>
#include <alex/LogUtil.h>
#include <alex/VectorOperations.h>

ClassImp(alex::AEvent)

namespace alex {


  AEvent::AEvent() : fEventID(0), 
  fTrueEventEnergy(0),fRecEventEnergy(0)
  { 
  	fDebugLevel = "DEBUG"; ///< particles
    InitLogger("AEvent");
    SetDebugLevel(fDebugLevel,"AEvent");
  }

  AEvent::AEvent(const AEvent& aev)
  {
    SetID(aev.GetID()) ;
    SetTrueEventEnergy(aev.GetTrueEventEnergy());
    SetRecEventEnergy(aev.GetRecEventEnergy());

    for (auto part : aev.GetParticles())
    {
      AddParticle(new AParticle(*apart));
    }
    
  }
  AEvent::~AEvent() 
  {
  	ClearEvent();
  }

  void AEvent::SetLevelDebug(std::string debugLevel)
  {

    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel,"AEvent");  
  }

  void AEvent::AddParticle(const AParticle* apart)
  {
    fParticles.push_back(new AParticle(*apart));
  }

  void AEvent::ClearEvent()
  {
    VDelete(fParticles); 
    fParticles.clear();
  }

  
} // end namespace 


