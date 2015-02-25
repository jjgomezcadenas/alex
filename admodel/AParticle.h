#ifndef APART_
#define APART_

#include <alex/ABase.h>


namespace alex {


  class AParticle : public ABase {
    
  public:
    
    // Constructors
    AParticle();
    AParticle(int Id, std::string name, bool isPrimary, double charge, 
              TVector3 vertex, TLorentzVector p4, int motherId);

    AParticle(const AParticle& apart);

    // Destructor
    virtual ~AParticle() {};

    void SetLevelDebug(std::string debugLevel);
    
    // Name
    std::string GetParticleName() const
    {return fName;}

    void SetParticleName(std::string name)
    {fName = name;}

    // Charge
    double GetCharge() const
    {return fCharge;}

    void SetCharge(double charge)
    {fCharge = charge;}

    // Primary
    bool GetIsPrimary() const
    {return fPrimary;}

    void SetIsPrimary(bool primary) 
    {fPrimary=primary;}
    
    // Vertex
    void SetVertex(TVector3 vertex)
    {fVertex = vertex;}

    TVector3 GetVertex() const
    {return fVertex;}

    // P4
    void SetP4(TLorentzVector p4)
    {fP4 = p4;}
    
    TLorentzVector GetP4() const
    {return fP4;}

    // Mother ID
    int GetMotherId() const
    {return fMotherId;}

    void SetMotherID(int motherId)
    {fMotherId = motherId;}

    // Mass
    double GetMass() const
    {return fP4.M();}

    // P3
    TVector3 GetMomentum() const
    {return fP4.Vect();}

    // EKin
    double GetEkin() const
    {return fP4.Energy()-fP4.M();}

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 

    
  private:
    int fMotherId;
    std::string fName; // Particle name
    double fCharge; // Particle charge
    TLorentzVector fP4; // Particle four momentum
    TVector3 fVertex; // vertex
    bool fPrimary; // Primary

    ClassDef(AParticle,1);
    
  };

std::ostream& operator << (std::ostream& s, const alex::AParticle& p);
}

#endif
