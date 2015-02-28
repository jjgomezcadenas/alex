// ----------------------------------------------------------------------------
///  \file   AEventHeader.h
///  \brief  base class for an event header
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------
 
#include <alex/AEventHeader.h>
#include <alex/LogUtil.h>

ClassImp(alex::AEventHeader)

namespace alex {

  AEventHeader::AEventHeader() :  fEvtNum(0),
  fTrueEventEnergy(0.),fRecEventEnergy(0)
  {

  }

    
  AEventHeader::AEventHeader(int evtNumber,
                 double trueEventEnergy, double recEventEnergy)
  {
    fEvtNum = evtNumber;
    fTrueEventEnergy = trueEventEnergy;
    fRecEventEnergy = recEventEnergy;
  }
    

  AEventHeader::AEventHeader(const AEventHeader& bevt)
  {
    SetTrueEventEnergy(bevt.GetTrueEventEnergy());
    SetRecEventEnergy(bevt.GetRecEventEnergy()); 
    SetEvtNum(bevt.GetEvtNum());   
  }

  std::string AEventHeader::PrintInfo() const
  { 
    std::stringstream s;
    s << " Event number " << GetEvtNum() << std::endl;
    s << " Event true energy " << GetTrueEventEnergy() << std::endl;
    s << " Event reco energy " << GetRecEventEnergy() << std::endl;
    return s.str();
  }  
  
} // end namespace 


