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
		
		std::vector<std::string> WriteAlgoHeaders();
		std::string WriteAlgoCPP();
		std::string WriteRegisterAlgos() const;
		std::string WriteRegisterAlgosHeader() const;
		std::string WriteAlgoHeaderFile() const;
		std::vector<std::string> AlgoNames() const {return fAlgoNames;}

	private:
		void ParseAlgosConfiguration(std::string xmlPath);
		void ParseAlgos();
		
		std::pair<std::string,std::string> ParseStringPair(const tinyxml2::XMLElement* mom, 
                                             const std::pair<std::string,std::string>& tags);

		std::pair<int,int> ParseIntPair(const tinyxml2::XMLElement* mom, 
                                       const std::pair<std::string,std::string>& tags);

		alex::DParam ParseParamElement(const tinyxml2::XMLElement* param) const;
		alex::DArray  ParseArrayElement(const tinyxml2::XMLElement* array) const;
		alex::DH1 ParseH1DElement(const tinyxml2::XMLElement* h1d) const;
		alex::DH2 ParseH2DElement(const tinyxml2::XMLElement* h2d) const;

		tinyxml2::XMLDocument fDoc;

		std::pair<std::string,std::string> fStags;
	
		std::vector<std::string> fAlgoNames;
    std::vector<std::string> fAlgoPath;


    std::map<std::string, std::string > fAlgoDebug;
    std::map<std::string, std::vector<alex::DParam> > fAlgoParam;
    std::map<std::string, std::vector<alex::DArray> > fAlgoArray;
    std::map<std::string, std::vector<alex::DH1> > fAlgoH1D;
    std::map<std::string, std::vector<alex::DH2> > fAlgoH2D;
			
	};

	typedef SingletonTemplate<AlexConf> AlexConfigure;   // Global declaration

}
#endif