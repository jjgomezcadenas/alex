
// ----------------------------------------------------------------------------
//  $Id: AXParticle.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/AXParticle.h>
#include <alex/VectorOperations.h>
#include <alex/LogUtil.h>


ClassImp(alex::AXParticle)

namespace alex {

  
	AXParticle::AXParticle(int Id, std::string name, 
											bool isPrimary, double charge, 
         							TVector3 vertex, 
         							TLorentzVector p4,
                      int motherID)
  {
 		SetID(Id);
  	SetParticleName(name);
  	SetIsPrimary(isPrimary);
 		SetCharge(charge);
 		SetVertex(vertex);
  	SetP4(p4);
    SetMotherID(motherID);
  }


  AXParticle::AXParticle(const AXParticle& apart)
  {
  	SetID(apart.GetID());
  	SetParticleName(apart.GetParticleName());
  	SetIsPrimary(apart.GetIsPrimary());
  	SetCharge(apart.GetCharge());
  	SetVertex(apart.GetVertex());
  	SetP4(apart.GetP4());
    SetMotherID(apart.GetMotherId());

    std::map <std::string, std::string> props = apart.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
  }


	void AXParticle::DisplayInfo(std::ostream& s) const
  { 
   	s << "  Particle " << GetID() << ": " << GetParticleName();
    s << "  Charge: " << GetCharge() << "  Mass: " << GetMass() << std::endl;
   	s << "  Primary: " << GetIsPrimary() << " -> Mother ID: " << GetMotherId() << std::endl;
   	s << "  Initial Vertex: " << PrintTVector3(GetVertex());
    s << "  Initial 4-Momentum: " << PrintTLorentzVector(GetP4());
    s << "  Initial Kinetic E: " << GetEkin() << std::endl;
   	s << "  Properties: " << std::endl << PrintProperties();
  }


  std::string AXParticle::PrintInfo() const
  {
    std::stringstream s;
    DisplayInfo(s);
    return s.str();
  }
}

std::ostream& operator << (std::ostream& s, const alex::AXParticle& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}
