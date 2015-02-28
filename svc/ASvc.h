#ifndef ASVC_
#define ASVC_
/*
 Alex service: persistency
 
 JJGC, January, 2015.
*/


#include <alex/GDefs.h>
 #include <alex/TDefs.h>
#include <alex/SingletonTemplate.h>


namespace alex {

class AParticle;
//class ATTrack;
//class ARTrack;
class AEvent;

class AlexService {
	public:

		AlexService(){};

		virtual ~AlexService(){};
		
		void Init(std::string debugLevel, int startEvt);

		void SetLevelDebug(std::string debugLevel);
		void SetStartEvent(int sevt) { fStartEvt = sevt; }
    int GetStartEvent() const { return fStartEvt; }

		void LoadEvent(const alex::AEvent* evt);
		void ClearEvent() ;
		//const AEvent& GetEventConst() {return *fEvt;} const 
		AEvent& GetAEvent() {return *fEvt;}  


	private:
	  std::string fDebugLevel;
	  int fStartEvt;
	  AEvent* fEvt;
	
	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif