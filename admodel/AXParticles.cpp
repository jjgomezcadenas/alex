
// ----------------------------------------------------------------------------
///  \file   AXParticles
///  \brief  A container of Alex Particles
///
///  \author   gomez@mail.cern.ch
///  \date     March 2015
/// 
///
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#include <alex/AXParticles.h>
#include <alex/AParticle.h>
#include <alex/LogUtil.h>
#include <alex/VectorOperations.h>

ClassImp(alex::AXParticles)

namespace alex {

//--------------------------------------------------------------------
  AXParticles::AXParticles() 
//--------------------------------------------------------------------
  { 
  	fDebugLevel = "WARN"; 
    InitLogger("AXParticles");
    SetDebugLevel(fDebugLevel,"AXParticles");
  }

//--------------------------------------------------------------------
  AXParticles::AXParticles(const AXParticles& aev)
//--------------------------------------------------------------------
  {
    
    ClearParticles();

    for (auto part : aev.GetParticles())
    {
      AddParticle(part);
    }
    
  }
//--------------------------------------------------------------------
  AXParticles::~AXParticles() 
//--------------------------------------------------------------------
  {
  	ClearParticles();
  }

//--------------------------------------------------------------------
  void AXParticles::SetLevelDebug(std::string debugLevel)
//--------------------------------------------------------------------
  {

    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel,"AXParticles");  
  }

//--------------------------------------------------------------------
  void AXParticles::AddParticle(AParticle* apart)
//--------------------------------------------------------------------
  {
    fParticles.push_back(apart);
  }


//--------------------------------------------------------------------
  void AXParticles::ClearParticles()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AXParticles");
    klog << log4cpp::Priority::DEBUG << " AXParticles::ClearEvent() " ;

    klog << log4cpp::Priority::DEBUG << " Deleting particles " ;
    VDelete(fParticles); 
    fParticles.clear();

  }

//--------------------------------------------------------------------
  std::string AXParticles::PrintInfo() const
//--------------------------------------------------------------------
  { 
    std::stringstream s;

    s << " number of particles = " << Size() << std::endl;
    s << " +++list of particles+++++ " << std::endl;

    for (auto particle : GetParticles()) 
      s << particle->PrintInfo() << std::endl;

    return s.str();
  }

} // end namespace 


