#ifndef ACONFD_
#define ACONFD_


#include <alex/GDefs.h>

using std::string;
namespace alex {

class AlexConfigData {
  public:
    AlexConfigData() : aLevelDebug("DEBUG"),aMode("IRENE"),
    aDST(""),aHisto(""),aStartEvent(0),aFinalEvent(10),aEventDebug(10),
    {};
    ~AlexConfigData(){};
  
    string aLevelDebug; // follows Log4CPP conventions DEBUG, INFO, WARN
    string aMode; // running mode: can be IRENE/TALEX/RALEX/ALEX depending of the input DST
    string aDST; // input DST
    string aHisto; //output histogram file
    int aStartEvent, aFinalEvent, aEventDebug; // configures the number of events to run

  };
}


#endif
