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
#include <TRandom.h>
#include "IDefs.h"
#include <alex/AParticle.h>
 #include <alex/ATTrack.h>
 



namespace alex {

class IreneManager {
	public:
		IreneManager(){};
		virtual ~IreneManager(){};
		void Init(std::string debugLevel, double energyResolution);
		void SetLevelDebug(std::string debugLevel);
		void LoadEvent(const irene::Event* ievt);

		const irene::Event& GetEvent();
		void SetStartEvent(int sevt) { fStartEvt = sevt; }
    int GetStartEvent() const { return fStartEvt; }

    void SetEvtNum(int sevt) { fEvtNum = sevt; }	
    int GetEvtNum() const { return fEvtNum; }

		TVector3 TrueVertex(){return fVertex;}
		
		std::vector<const irene::Particle*> GetParticles() const 
		{return fIreneParticles;}

		std::vector<const irene::Track*> GetTracks() const 
		{return fIreneTracks;}

		std::vector<std::pair<TLorentzVector,double> > GetTrueHits() const 
		{return fTrueHits;}

		std::vector<alex::AParticle*> GetAlexParticles();
		std::vector<alex::ATTrack*> 	GetAlexTTracks();

		double GetTrueEventEnergy() const {return fTrueEventEnergy;}
    double GetRecEventEnergy() const {return fRecEventEnergy;}
    double ResolutionFWHM() const {return fFWHM; }
    double ResolutionSigma() const {return fSigma; }
    

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
  	std::vector<const irene::Particle*>  fIreneParticles;
  	double fFWHM;
  	double fSigma;
  	double fTrueEventEnergy;
  	double fRecEventEnergy;
  	TRandom* fRandom;


	};

	typedef alex::SingletonTemplate<IreneManager> ISvc;   // Global declaration

}
#endif
