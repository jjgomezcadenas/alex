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
		
		void Init(std::string debugLevel);

		void SetLevelDebug(std::string debugLevel);

		void LoadEvent(const alex::AEvent* evt);
		void ClearEvent() ;
		const AEvent& GetEvent() {return *fEvt;} const 


	private:
	  std::string fDebugLevel;
	  AEvent* fEvt;
	
	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif