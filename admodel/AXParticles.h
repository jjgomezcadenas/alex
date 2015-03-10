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

#ifndef AXPART_H_
#define AXPART_H_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TNamed.h>


namespace alex {

  class AParticle;
  

  class AXParticles : public TNamed {
    
  public: 
    /// Constructor
    AXParticles();
    
    /// Destructor
    virtual ~AXParticles();

    AXParticles(const AXParticles& aev);

    void SetLevelDebug(std::string debugLevel);

    void AddParticle(AParticle* apart);
    const std::vector <AParticle*> GetParticles() const {return fParticles;}

    AParticle* GetParticle(size_t i) const {return fParticles.at(i);}

    size_t Size() const {return fParticles.size();}

    void ClearParticles();
   
    std::string PrintInfo() const;


   private:

    std::vector <alex::AParticle*> fParticles;
    std::string fDebugLevel;
    
    ClassDef(AXParticles,1);
    
  };

   

} 


#endif 
