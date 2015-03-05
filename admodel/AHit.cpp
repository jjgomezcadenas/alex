
// ----------------------------------------------------------------------------
//  $Id: AHit.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 10 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/AHit.h>
#include <alex/LogUtil.h>
#include <alex/TUtil.h>

ClassImp(alex::AHit)

namespace alex {

	AHit::AHit(int Id, double x, double y, double z, double E) 												
  {
  	SetID(Id);
  	SetPosition(TVector3(x,y,z));
  	SetEdep(E);
  }


  AHit::AHit(int Id, TVector3 pos, double E)            
  {
    SetID(Id);
    SetPosition(pos);
    SetEdep(E);
  }


 	AHit::AHit(const AHit& ahit)
 	{
 		SetID(ahit.GetID());
 		SetPosition(ahit.GetPosition());
    SetEdep(ahit.GetEdep());

    std::map <std::string, std::string> props = ahit.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
 	}


  void AHit::DisplayInfo(std::ostream& s) const
 	{
   	s << "  Hit ID: " << GetID();
   	s << "  Edep: " << GetEdep();
   	s << "  Position: " << PrintTVector3(GetPosition());
 	}

  std::string AHit::PrintInfo() const
  {
    std::stringstream s;
    DisplayInfo(s);
    return s.str();
  }

}

std::ostream& operator << (std::ostream& s, const alex::AHit& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}