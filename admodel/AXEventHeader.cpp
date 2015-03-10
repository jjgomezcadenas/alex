// ----------------------------------------------------------------------------
///  \file   AXEventHeader.cpp
///  
// ----------------------------------------------------------------------------
 
#include <alex/AXEventHeader.h>
#include <alex/LogUtil.h>

ClassImp(alex::AXEventHeader)

namespace alex {

  AXEventHeader::AXEventHeader() :  fEvtNum(0),
  fTrueEventEnergy(0.)
  {

  }

    
  AXEventHeader::AXEventHeader(int evtNumber,double trueEventEnergy)
  {
    fEvtNum = evtNumber;
    fTrueEventEnergy = trueEventEnergy;
  }
    

  AXEventHeader::AXEventHeader(const AXEventHeader& bevt)
  {
    SetTrueEventEnergy(bevt.GetTrueEventEnergy()); 
    SetEvtNum(bevt.GetEvtNum());   
  }

  std::string AXEventHeader::PrintInfo() const
  { 
    std::stringstream s;
    s << " Event number " << GetEvtNum() << std::endl;
    s << " Event true energy " << GetTrueEventEnergy() << std::endl;
    return s.str();
  }  
  
} // end namespace 


