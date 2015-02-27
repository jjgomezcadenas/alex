
#ifndef AACONF_
#define AACONF_

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
namespace alex {
  class AlgoConf {
    public:
      AlgoConf();
      ~AlgoConf(){};
      
      void RegisterAlgos();
      std::string AlgosPath() const {return fAlgoPathName.first;}
      std::string AlgosName() const {return fAlgoPathName.second;}
      std::string DstPath() const {return fDstPathName.first;}
      std::string DstName() const {return fDstPathName.second;}
      std::string HistoPath() const {return fHistoPathName.first;}
      std::string HistoName() const {return fHistoPathName.second;}
      int EventsToRun()const {return fEvents.first;}
      int EventsToDebug()const {return fEvents.second;}
      std::string DebugLevel()const {return fDebug;}
    private:
      std::pair<std::string,std::string> fAlgoPathName;
      std::pair<std::string,std::string> fDstPathName;
      std::pair<std::string,std::string> fHistoPathName;
      std::pair<int,int> fEvents;
      std::string fDebug;
  };
}
#endif
