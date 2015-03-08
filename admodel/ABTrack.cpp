// ----------------------------------------------------------------------------
//  $Id: ABTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/ABTrack.h>
#include <alex/AHit.h>
#include <alex/VectorOperations.h>
#include <alex/LogUtil.h>

ClassImp(alex::ABTrack)

namespace alex {

  ABTrack::ABTrack() 
  {
    SetID(-1);
    fEdep = 0.;
    fSetExtreme1=false;
    fSetExtreme2=false;

    InitLogger("ABTrack");
    fDebug = "WARN";
    SetDebugLevel(fDebug,"ABTrack");
  }


	ABTrack::ABTrack(int id) 
  {
  	SetID(id);
    fEdep = 0.;
    fSetExtreme1=false;
    fSetExtreme2=false;
    fDebug = "WARN";
    SetDebugLevel(fDebug,"ABTrack");
  }

  void ABTrack::SetLevelDebug(std::string debugLevel)
  {
    fDebug = debugLevel;
    SetDebugLevel(fDebug,"ABTrack");
  }

  ABTrack::~ABTrack()
  {
    log4cpp::Category& klog = GetLogger("ABTrack");
    klog << log4cpp::Priority::DEBUG << " ABTrack::~ABTrack() " ;

    klog << log4cpp::Priority::DEBUG << "Deleting hits" ;
    VDelete(fHits);

    klog << log4cpp::Priority::DEBUG << "clearing hit vector" ;

    fHits.clear();

    klog << log4cpp::Priority::DEBUG << "Deleting extremes" ;
    
    if (fSetExtreme1 ==true) delete fExtremes.first;
    if (fSetExtreme2 ==true) delete fExtremes.second;
  }
  

  ABTrack::ABTrack(const ABTrack& abt)
  {
 		SetID(abt.GetID());

 		VDelete(fHits);
    fHits.clear();
    const std::vector<AHit*> hits = abt.GetHits();
    for (auto hit : hits) AddHit(hit);

    if (abt.fSetExtreme1 ==true) SetExtreme1(abt.GetExtreme1());
    if (abt.fSetExtreme2 ==true) SetExtreme2(abt.GetExtreme2());
    fEdep = abt.GetEdep();

    std::map <std::string, std::string> props = abt.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
  }


  void ABTrack::AddHit(AHit* ahit)
  {
    fHits.push_back(ahit);
    fEdep += ahit->GetEdep();
  }
	  

  // Extremes
  void ABTrack::SetExtreme1(AHit* ahit) 
  {
    fExtremes.first = ahit;
    fSetExtreme1=true;
  }


  void ABTrack::SetExtreme2(AHit* ahit) 
  {
    fExtremes.second = ahit;
    fSetExtreme2=true;
  }


  AHit* ABTrack::GetHit(int id) const 
  {
    const std::vector<AHit*> hits = GetHits();
    for (auto hit : hits)
    {
      if (hit->GetID() == id) return hit;
    }
    std::cout << "ABTrack::ERROR: Hit ID "  << id << " does NOT EXIST !!" << std::endl;
    exit(-1);
  }


  void ABTrack::DisplayInfo(std::ostream& s) const
  {
    s << "* EnergyDep: " << GetEdep() << std::endl;

    if (fSetExtreme1 ==true) {
      TVector3 pos1 = GetExtreme1()->GetPosition();
      s << "* Extreme1:" << PrintTVector3(pos1);
    }

    if (fSetExtreme2 ==true) {
      TVector3 pos2 = GetExtreme2()->GetPosition();
      s << "* Extreme2:" << PrintTVector3(pos2);
    }
      
   	s << "* Hits Collection: " <<  std::endl;
    const std::vector<AHit*> hits = GetHits();
    for (auto hit : hits) hit->DisplayInfo(s);

  	s << "* Properties: " << std::endl << PrintProperties();
  }


	std::string ABTrack::PrintInfo() const
	{
  	std::stringstream s;
	 	DisplayInfo(s);
  	return s.str();
	}

}


std::ostream& operator << (std::ostream& s, const alex::ABTrack& abt) 
{
  abt.DisplayInfo(s);
  return s;
}
