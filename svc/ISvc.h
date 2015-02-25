#ifndef ISVC_
#define ISVC_
/*
 Irene Svc to provide access to irene (eg DST) to algos
 JJGC, July, 2014.
 New version, December 2014
*/

#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>
#include "IDefs.h"



namespace alex {

class IreneManager {
	public:
		IreneManager(){};
		virtual ~IreneManager(){};
		void Init(std::string debugLevel);
		void SetLevelDebug(std::string debugLevel);
		void LoadEvent(const irene::Event* ievt);

		const irene::Event& GetEvent();
		void SetStartEvent(int sevt) { fStartEvt = sevt; }
    int GetStartEvent() const { return fStartEvt; }

    void SetEvtNum(int sevt) { fEvtNum = sevt; }	
    int GetEvtNum() const { return fEvtNum; }

		TVector3 TrueVertex(){return fVertex;}
		
		IParticles GetParticles() const {return fIreneParticles;}
		ITracks GetTracks() const {return fIreneTracks;}
		IHits GetTrueHits() const {return fTrueHits;}

		void PrintHits();
		void PrintTrueEvent();
		

	private:
		
		void GetTrueVertex();
    
    int fStartEvt;
    int fEvtNum;

    std::string fDebugLevel;
        
  	const irene::Event* fIevt;

  	IHits fTrueHits;
  	TVector3 fVertex;
  	std::vector<const irene::Track*> fIreneTracks ;
  	IParticles fIreneParticles;

	};

	typedef alex::SingletonTemplate<IreneManager> ISvc;   // Global declaration

}
#endif
