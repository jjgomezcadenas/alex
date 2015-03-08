#ifndef ACONFD_
#define ACONFD_


#include <alex/GDefs.h>

using std::string;
namespace alex {

class AlexConfigData {
  public:
    AlexConfigData() : aLevelDebug("DEBUG"),aMode("IRENE"),
    aDST(""),aHisto(""),aStartEvent(0),aFinalEvent(10),aEventDebug(10),
    aPressure(10.),aBField(0.5),aEnergyFWHM(0.005),aXYSigma(1.),
    aZSigma(1.)
    {};
    ~AlexConfigData(){};
  
    string aLevelDebug; // follows Log4CPP conventions DEBUG, INFO, WARN
    string aMode; // running mode: can be IRENE/TALEX/RALEX/ALEX depending of the input DST
    string aDST; // input DST
    string aHisto; //output histogram file
    int aStartEvent, aFinalEvent, aEventDebug; // configures the number of events to run
    double aPressure, aBField, aEnergyFWHM, aXYSigma, aZSigma; //various param
    /*
    pressure in atms, b field in tesla, Energy resolution  FWHM in fraction, 
    aXYResolution and aZResolution in mm. 
    */

  };
}


#endif
