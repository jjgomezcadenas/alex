
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


  AEvent::AEvent() : AEventHeader()
  { 
  	fDebugLevel = "DEBUG"; 
    InitLogger("AEvent");
    SetDebugLevel(fDebugLevel,"AEvent");
  }

  AEvent::AEvent(int evtNumber,
                 double trueEventEnergy, double recEventEnergy)
  {
    AEventHeader(evtNumber,trueEventEnergy,recEventEnergy);
    fDebugLevel = "DEBUG"; 
    InitLogger("AEvent");
    SetDebugLevel(fDebugLevel,"AEvent");
  }

  AEvent::AEvent(const AEvent& aev)
  {
    AEventHeader(aev.GetEvtNum(),aev.GetTrueEventEnergy(),aev.GetRecEventEnergy());
    // SetTrueEventEnergy(aev.GetTrueEventEnergy());
    // SetRecEventEnergy(aev.GetRecEventEnergy());
    // SetEvtNum(aev.GetEvtNum());

    ClearEvent();

    for (auto part : aev.GetParticles())
    {
      AddParticle(part);
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

  void AEvent::AddParticle(AParticle* apart)
  {
    fParticles.push_back(apart);
  }

  void AEvent::ClearEvent()
  {
    VDelete(fParticles); 
    fParticles.clear();
  }

  std::string AEvent::PrintInfo() const
  { 
    std::stringstream s;
    s << " Event number " << GetEvtNum() << std::endl;
    s << " Event true energy " << GetTrueEventEnergy() << std::endl;
    s << " Event reco energy " << GetRecEventEnergy() << std::endl;
    s << " number of particles in event " << GetParticles().size() << std::endl;
    s << " +++list of particles+++++ " << std::endl;

    for (auto particle : GetParticles()) 
      s << particle->PrintInfo() << std::endl;

    return s.str();
  }

  
} // end namespace 


