#include "ReadAlexDST.hh"
#include <alex/LogUtil.h>
#include <alex/ASvc.h>
#include <alex/AEvent.h>
#include <alex/AParticle.h>

namespace alex {

  //--------------------------------------------------------------------
  bool ReadAlexDST::Init()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    klog << log4cpp::Priority::INFO << "ReadAlexDST::Init()" ;

    klog << log4cpp::Priority::INFO << "Instantiate AEvent" ;

    
    return true;
  }
  //--------------------------------------------------------------------
  bool ReadAlexDST::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    
    klog << log4cpp::Priority::DEBUG << " ReadAlexDST::Execute";
    klog << log4cpp::Priority::DEBUG 
    << " Instantiate AEvent for event number " 
    << ASvc::Instance().GetEvent().GetEvtNum();

    

    klog << log4cpp::Priority::DEBUG 
    << " ---Reading Particles from AEvent--- ";


    const std::vector <alex::AParticle*>
    aParticles = ASvc::Instance().GetEvent().GetParticles();
    
    klog << log4cpp::Priority::DEBUG << "-->number of aParticles =" 
    << aParticles.size();
  
    for (auto aPart : aParticles) 
    {
      fEnergyOfParticles_h1->Fill(aPart->GetEkin());
      fTrackLength_h1->Fill(aPart->GetParam("TrackLength"));
    }

    fNumberOfParticles_h1->Fill(aParticles.size()); 
    
    fRecEnergyOfEvent_h1->Fill(ASvc::Instance().GetEvent().GetRecEventEnergy());
    fTrueEnergyOfEvent_h1->Fill(ASvc::Instance().GetEvent().GetTrueEventEnergy());

    klog << log4cpp::Priority::DEBUG << "-------Print AEvent------" ;
    klog << log4cpp::Priority::DEBUG <<ASvc::Instance().GetEvent().PrintInfo();

    return true;
  }
  //--------------------------------------------------------------------
  bool ReadAlexDST::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    klog << log4cpp::Priority::DEBUG << " ReadAlexDST::END()";

    return true;
  }
}
