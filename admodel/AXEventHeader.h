// ----------------------------------------------------------------------------
///  \file   AXEventHeader.h
///  \brief  Event header for Alex
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AXEVENTH_H_
#define AXEVENTH_H_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TNamed.h>

namespace alex {

  class AXEventHeader : public TNamed {
    
  public: 
    /// default Constructor
    AXEventHeader();

    ///Constructor
    AXEventHeader(int evtNumber,double trueEventEnergy);
    /// Destructor
    virtual ~AXEventHeader(){};

    AXEventHeader(const AXEventHeader& bevt);

    double GetTrueEventEnergy() const {return fTrueEventEnergy;}
    void SetTrueEventEnergy(double e) {fTrueEventEnergy=e;}

    void SetEvtNum(int sevt) { fEvtNum = sevt; }  
    int GetEvtNum() const { return fEvtNum; }


    std::string PrintInfo() const;

   private:

    int fEvtNum;
    double fTrueEventEnergy;
    

    ClassDef(AXEventHeader,1);
    
  };

   

} // end namespace 


#endif // 
