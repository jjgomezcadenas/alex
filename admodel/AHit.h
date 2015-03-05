#ifndef AHIT_
#define AHIT_

#include <alex/ABase.h>


namespace alex {

  class AHit : public ABase {
    
  public:
    
    // Constructors
    AHit(){};
    AHit(int Id, double x, double y, double z, double E); 
    AHit(int Id, TVector3 pos, double E);
    
    AHit(const AHit& ahit);

    // Destructor
    virtual ~AHit() {};
    
    // Position
    void SetPosition(TVector3 pos)
    {fPos = pos;}

    TVector3 GetPosition() const
    {return fPos;}

    // Energy Deposited
    void SetEdep(double E)
    {fE = E;}
    
    double GetEdep() const
    {return fE;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 
    
    
  private:
    double fE; // Hit Edep
    TVector3 fPos; // Hit position

    ClassDef(AHit,1);
    
  };

std::ostream& operator << (std::ostream& s, const alex::AHit& ah);
}

#endif
