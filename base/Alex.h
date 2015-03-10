#ifndef ACONFIG_
#define ACONFIG_
/*
 ACONFIG: Alex Configuration
 

 JJGC, July, 2014.
*/

#include <alex/GDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/IAlgorithm.h>
#include <alex/IData.h>

#include <TROOT.h>
#include <TFolder.h>
#include <TFile.h>
#include <TChain.h>
 #include <TTree.h>
#include <TCollection.h>
#include <TObject.h>

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {


class AlexManager {
	public:
		AlexManager(){};
		virtual ~AlexManager(){};
		void Init();
		void SetHistoFile(TFile* histoFile) {fHistoFile = histoFile;}
		void SetDstTree(TTree* tree) 
		{
			fTree = tree;
		}
		
		void RegisterAlgorithm(IAlgorithm* algo );
		void InitAlgorithms();
		bool ExecuteAlgorithms();
		void EndAlgorithms();
		void ClearAlgorithms();

		// void RegisterData(std::string name, IData* data )
		// {fIData[name]=data;}
		// IData* RetrieveData(std::string name){return fIData[name]; }
		void ClearData();
		
		void SetLevelDebug(std::string debugLevel);
		
		TFile& GetHistoFile() {return *fHistoFile; }
		TTree& SetDstTree() {return *fTree; }
		
		TFolder* GetFolder(string folderPath);
		TObject* GetObject(string objectPath);

	private:
		std::vector<IAlgorithm*> fIAlgo;
		//std::map<std::string,IData*> fIData;
		std::string fDebugLevel;
		TFile* fHistoFile;
		TTree* fTree;

	};

	typedef SingletonTemplate<AlexManager> Alex;   // Global declaration

}
#endif