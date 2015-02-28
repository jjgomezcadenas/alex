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

#include <alex/AEventHeader.h>


namespace alex {

  class AParticle;
  
  /// Persistent class
  
  class AEvent : public AEventHeader {
    
  public: 
    /// Constructor
    AEvent();
    AEvent(int evtNumber,
                 double trueEventEnergy, double recEventEnergy);
    /// Destructor
    virtual ~AEvent();

    AEvent(const AEvent& aev);

    void SetLevelDebug(std::string debugLevel);

    void AddParticle(AParticle* apart);
    
    const std::vector <alex::AParticle*> GetParticles() const {return fParticles;}

    void ClearEvent();
   
    std::string PrintInfo() const;


   private:

    std::string fDebugLevel;

    std::vector <alex::AParticle*> fParticles;

    ClassDef(AEvent,1);
    
  };

   

} // end namespace irene


#endif // EVENT_H_
