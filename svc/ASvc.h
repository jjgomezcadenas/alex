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
		//void ClearEvent() ;
		const AEvent& GetEvent() const  {return *fEvt;} 
		//AEvent& GetAEvent() {return *fEvt;}  

	private:
	  std::string fDebugLevel;
	  int fStartEvt;

	  const AEvent* fEvt;
	
	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif