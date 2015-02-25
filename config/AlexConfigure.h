#ifndef ACONFIG_
#define ACONFIG_
/*
 ACONFIG: Alex Configuration
 

 JJGC, July, 2014.
*/

#include <alex/Gdefs.h>
#include <alex/SingletonTemplate.h>
#include <tinyxml2.h>

#include "DArray.h"
#include "DParam.h"
#include "DHistos.h"


namespace alex {

class AlexConf {
	public:
		AlexConf(){};
		virtual ~AlexConf(){};
		void Init(std::string debugLevel);
		void ParseConfiguration(std::string configFile);
		void ParseGalexConfiguration(std::string configFile);
		
		std::string WriteAConfHeader() const;
		std::string WriteAConfCPP() const;
		std::string WriteAlgoHeader();

		std::string WriteGalexHeader() const; 

		std::vector<std::string> WriteAlgoHeaders();
		std::string WriteAlgoCPP();
		std::string WriteRegisterAlgos() const;
		std::string WriteRegisterAlgosHeader() const;
		std::string WriteAlgoHeaderFile() const;
		std::vector<std::string> AlgoNames() const {return fAlgoNames;}
		std::string SerializeAlgoNames() const;
		std::string SerializeAlgoPaths() const;
		std::string SerializeAlgoParam() const;
		std::string SerializeAlgoArray() const;
		std::string SerializeAlgoH1D() const;
		std::string SerializeAlgoH2D() const;

	private:
		void ParseAlgosConfiguration();
		void ParseAlgos();
		//tinyxml2::XMLElement* ParseRoot() ;
		std::pair<std::string,std::string> ParseStringPair(const tinyxml2::XMLElement* mom, 
                                             const std::pair<std::string,std::string>& tags);

		std::pair<int,int> ParseIntPair(const tinyxml2::XMLElement* mom, 
                                       const std::pair<std::string,std::string>& tags);

		alex::DParam ParseParamElement(const tinyxml2::XMLElement* param) const;
		alex::DArray  ParseArrayElement(const tinyxml2::XMLElement* array) const;
		alex::DH1 ParseH1DElement(const tinyxml2::XMLElement* h1d) const;
		alex::DH2 ParseH2DElement(const tinyxml2::XMLElement* h2d) const;

		tinyxml2::XMLDocument fDoc;

		std::string fDebugLevel;
		std::pair<std::string,std::string> fStags;
		std::pair<std::string,std::string> fAlgosPathName;
		std::pair<std::string,std::string> fDstPathName;
		std::pair<std::string,std::string> fHistoPathName;
		std::pair<int,int> fEvents;
		std::string fDebug;

		std::vector<std::string> fAlgoNames;
    std::vector<std::string> fAlgoPath;

    std::vector<alex::DParam> fGalexParam;

    std::map<std::string, std::vector<alex::DParam> > fAlgoParam;
    std::map<std::string, std::vector<alex::DArray> > fAlgoArray;
    std::map<std::string, std::vector<alex::DH1> > fAlgoH1D;
    std::map<std::string, std::vector<alex::DH2> > fAlgoH2D;
			
	};

	typedef SingletonTemplate<AlexConf> AlexConfigure;   // Global declaration

}
#endif