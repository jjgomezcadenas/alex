#ifndef ACONFIG_
#define ACONFIG_
/*
 ACONFIG: Alex Configuration
 

 JJGC, July, 2014.
*/

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <alex/SingletonTemplate.h>
#include <alex/IAlgorithm.h>
#include <alex/IData.h>
 #include <alex/AlexConfigData.h>


namespace alex {


class AlexManager {
	public:
		AlexManager(){};
		virtual ~AlexManager(){};
		void Init();

		void RegisterAlgorithm(IAlgorithm* algo );
		void InitAlgorithms();
		bool ExecuteAlgorithms();
		void EndAlgorithms();
		void ClearAlgorithms();

		void RegisterData(std::string name, IData* data )
		{fIData[name]=data;}
		IData* RetrieveData(std::string name){return fIData[name]; }
		void ClearData();
		// const IData* RetrieveData(std::string name) const
		// {return fIData[name];} 

		AlexConfigData& ConfigData() {return *fAlexConfigData;}
		void SetLevelDebug(std::string debugLevel);
		std::string PrintConfigData();

	private:
		std::vector<IAlgorithm*> fIAlgo;
		std::map<std::string,IData*> fIData;
		std::string fDebugLevel;
		AlexConfigData* fAlexConfigData;	
	};

	typedef SingletonTemplate<AlexManager> Alex;   // Global declaration

}
#endif