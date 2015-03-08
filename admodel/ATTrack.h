#ifndef ATTRACK_
#define ATTRACK_

#include <alex/ABTrack.h>

namespace alex {

  class ATTrack : public ABTrack {
    
  public:
    
    // Constructors
    ATTrack();
    ATTrack(int id, int particleId);

    ATTrack(const ATTrack& att);

    // Destructor
    virtual ~ATTrack() ; // hits destroyed in the base class

    // Particle ID
    int GetParticleID() const
    {return fParticleID;}

    void SetParticleID(int pID)
    {fParticleID = pID;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 

    
  private:
    int fParticleID;

    ClassDef(ATTrack,1);
  };

std::ostream& operator << (std::ostream& s, const alex::ATTrack& att);
}

#endif
