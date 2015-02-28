// ----------------------------------------------------------------------------
///  \file   AEventHeader.h
///  \brief  base class for an event header
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AEEVENTH_H_
#define AEEVENTH_H_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TObject.h>


namespace alex {

  class AEventHeader : public TObject {
    
  public: 
    /// default Constructor
    AEventHeader();

    ///Constructor
    AEventHeader(int evtNumber,
                 double trueEventEnergy, double recEventEnergy);
    /// Destructor
    virtual ~AEventHeader(){};

    AEventHeader(const AEventHeader& bevt);

    double GetTrueEventEnergy() const {return fTrueEventEnergy;}
    double GetRecEventEnergy() const {return fRecEventEnergy;}
    void SetRecEventEnergy(double e) {fRecEventEnergy=e;}
    void SetTrueEventEnergy(double e) {fTrueEventEnergy=e;}

    void SetEvtNum(int sevt) { fEvtNum = sevt; }  
    int GetEvtNum() const { return fEvtNum; }

    std::string PrintInfo() const;

   private:

    int fEvtNum;

    double fTrueEventEnergy;
    double fRecEventEnergy;


    ClassDef(AEventHeader,1);
    
  };

   

} // end namespace irene


#endif // EVENT_H_
