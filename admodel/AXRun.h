// ----------------------------------------------------------------------------
///  \file   AXRun.h
///  \brief  describes run level data
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AXRUN_H_
#define AXRUN_H_

#include <alex/GDefs.h>
#include <TNamed.h>


namespace alex {

  class AXRun : public TNamed {
    /*
    Run level data:
    Pressure in atm
    Bfield in Tesla
    EnergyFWHM in per unit (0.005 = 0.5 %)
    XYSigma and ZSigma in mm
    EMin (minimum visible energy) in keV
    */
    
  public: 
    /// default Constructor
    AXRun(): fPressure(10.0), fBField(0.), fEnergyFWHM(0.005),
    fXYSigma(1.), fZSigma(1.), fEMin(10.) {}; 
    
    AXRun(double aPressure, double aBField, double aEnergyFWHM, 
          double aXYSigma, double aZSigma, double aEMin) : 
    fPressure(aPressure), fBField(aBField), fEnergyFWHM(aEnergyFWHM),
    fXYSigma(aXYSigma), fZSigma(aZSigma), fEMin(aEMin) {};

    
    /// Destructor
    virtual ~AXRun(){};

    AXRun(const AXRun& axr);

    double GetPressure() const {return fPressure;}
    double GetBField() const {return fBField;}
    double GetEnergyFWHM() const {return fEnergyFWHM;}
    double GetXYSigma () const {return fXYSigma;}
    double GetZSigma () const {return fZSigma;}
    double GetEMin () const {return fEMin;}
    void SetPressure(double aPressure) {fPressure=aPressure;}
    void SetBField(double aBField) {fBField=aBField;}
    void SetEnergyFWHM(double aEnergyFWHM) {fEnergyFWHM=aEnergyFWHM;}
    void SetXYSigma(double aXYSigma) {fXYSigma=aXYSigma;}
    void SetZSigma(double aZSigma) {fZSigma=aZSigma;}
    void SetEMin(double aEMin) {fEMin=aEMin;}
    
    std::string PrintInfo() const;
   protected:

    double fPressure;
    double fBField;
    double fEnergyFWHM;
    double fXYSigma;
    double fZSigma;
    double fEMin;


    ClassDef(AXRun,1);
    
  };

   

} // end namespace 


#endif 
