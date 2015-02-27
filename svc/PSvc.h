#ifndef PSVC_
#define PSVC_
/*
 Paolina Svc to provide access to Paolina
 JJGC, July, 2014.
 New version, December 2014
*/

#include <alex/GDefs.h>
#include <alex/TDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>
#include "PDefs.h"



namespace alex {

//typedef std::vector<std::pair<TLorentzVector,double> > IHits ;
  
class PaolinaManager {
	public:
		PaolinaManager(){};
		virtual ~PaolinaManager(){};

    void Init(std::string debugLevel,
              std::vector<std::pair<double,double> > detSize);

    void SetLevelDebug(std::string debugLevel);
  
    std::vector<std::pair<TVector3,double> > 
    ComputePaolinaVoxels(std::vector<std::pair<TLorentzVector,double> > hits,
                         std::vector<double> voxelSize);

    std::vector<paolina::Track*>  ComputePaolinaTracks();
    std::pair<paolina::Blob*, paolina::Blob*> ComputePaolinaBlobs(double blobRadius);

    std::string PrintVoxels();
    std::string PrintBlobs();
    std::string PrintTracks();

	private:
		
    std::string fDebugLevel;
    
    std::vector<std::pair<double,double> > fDetSize;
    //voxels
		std::vector<paolina::Voxel*> fPvoxels;	
  	//paolina tracks
  	std::vector<paolina::Track*> fPtracks;
  	//paolina blobs
  	std::pair<paolina::Blob*, paolina::Blob*> fPblobs;

	};

  // Global declaration
	typedef alex::SingletonTemplate<PaolinaManager> PSvc; 

}
#endif
