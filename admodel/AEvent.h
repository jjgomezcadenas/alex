// ----------------------------------------------------------------------------
///  \file   AEvent.h
///  \brief  Used for ALEX persistency
///
///  \author   <paola.ferrario@ific.uv.es> // gomez@mail.cern.ch
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: Event.h 9914 2014-07-13 07:51:27Z gomez $
///
///  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AEEVENT_H_
#define AEEVENT_H_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TObject.h>


namespace alex {

  class AParticle;
  
  /// Persistent class
  
  class AEvent : public TObject {
    
  public: 
    /// Constructor
    AEvent();
    /// Destructor
    virtual ~AEvent();

    AEvent(const AEvent&);

    void SetID(int id) {fEventID = id;} 
    int GetID() const {return fEventID;}

    void SetLevelDebug(std::string debugLevel);

    double GetTrueEventEnergy() const {return fTrueEventEnergy;}
    double GetRecEventEnergy() const {return fRecEventEnergy;}
    void SetRecEventEnergy(double e) {fRecEventEnergy=e;}
    void SetTrueEventEnergy(double e) {fTrueEventEnergy=e;}

    void AddParticle(const AParticle* apart);
    const std::vector <alex::AParticle*> GetParticles() const {return fParticles;}

    void ClearEvent();
   
   private:

    std::string fDebugLevel;

    int fStartEvt;
    int fEvtNum;

    double fTrueEventEnergy;
    double fRecEventEnergy;

    std::vector <alex::AParticle*> fParticles;

    ClassDef(AEvent,1);
    
  };

   

} // end namespace irene


#endif // EVENT_H_
