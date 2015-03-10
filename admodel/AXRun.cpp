// ----------------------------------------------------------------------------
///  \file   AXRun

///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------
 
#include <alex/AXRun.h>

ClassImp(alex::AXRun)

namespace alex {


  AXRun::AXRun(const AXRun& axr)
  {
    SetPressure(axr.GetPressure()) ;
    SetBField(axr.GetBField()) ;
    SetEnergyFWHM(axr.GetEnergyFWHM()) ;
    SetXYSigma(axr.GetXYSigma ()) ;
    SetZSigma(axr.GetZSigma ()) ;
    SetEMin(axr.GetEMin ())  ;
  }

  std::string AXRun::PrintInfo() const
  { 
    std::stringstream s;
    s << "------Run level data ------" << std::endl;
    s << " Pressure (atm) =" << GetPressure() << std::endl;
    s << " Bfield (tesla) = " << GetBField() << std::endl;
    s << " Energy FWHM =" << GetEnergyFWHM() << std::endl;
    s << " XY Sigma (mm) = " << GetXYSigma () << std::endl;
    s << " Z Sigma (mm) = " << GetZSigma () << std::endl;
    s << " Emin visible (keV) = " << GetEMin () << std::endl;
    return s.str();
  }  
  
} // end namespace 


