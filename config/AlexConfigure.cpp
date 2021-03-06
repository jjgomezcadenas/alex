
// ----------------------------------------------------------------------------
//  $Id: AXml.cc 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "AlexConfigure.h"
#include <alex/LogUtil.h>
#include <alex/StringOperations.h>
#include <alex/GDefs.h>


using std::string;
using std::pair; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;
using std::pair;
using std::ostringstream;

using namespace tinyxml2;
namespace alex {

//--------------------------------------------------------------------
  void AlexConf::Init(std::string debugLevel)  
//--------------------------------------------------------------------
  {
    InitLogger("AlexConfigure");
    SetDebugLevel(debugLevel,"AlexConfigure");
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " AlexConf::Init() " ;
    fStags.first ="path";
    fStags.second="name";


  }
//--------------------------------------------------------------------
  void AlexConf::ParseConfiguration(string pathToAlgoConfig)
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");

    klog << log4cpp::Priority::DEBUG << " AlexConf::ParseConfiguration() " ;
    klog << log4cpp::Priority::DEBUG << " ParseAlgosConfiguration file =" 
          << pathToAlgoConfig;
   
    ParseAlgosConfiguration(pathToAlgoConfig);

    klog << log4cpp::Priority::DEBUG << " ParseAlgos" ;
    ParseAlgos();

  }
//--------------------------------------------------------------------
  void AlexConf::ParseAlgosConfiguration(string xmlPath)
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseAlgosConfiguration() " ;
    
    klog << log4cpp::Priority::DEBUG << " Opening file ="
         << xmlPath;
    
    //tinyxml2::XMLDocument doc;

    fDoc.LoadFile( xmlPath.c_str() );
    if (fDoc.ErrorID()!=0) 
    {
      klog << log4cpp::Priority::ERROR 
      << "ParseAlgosConfiguration::Failed loading config file error = " 
      << fDoc.ErrorID();
      exit (EXIT_FAILURE);
    }

    XMLElement* rootElement = fDoc.RootElement();
    string rootName = rootElement->Name();

    if (rootName !="AlgoConfig")
    {
      klog << log4cpp::Priority::ERROR 
      << "ParseConfiguration::expected root name AlgoConfig, found = " 
      << rootName;
      exit (EXIT_FAILURE);
    }

    const XMLElement* algoElement = rootElement->FirstChildElement ("Algo") ;
    
    if (algoElement != NULL)
    {
      pair<string,string> algoPathName = ParseStringPair(algoElement,fStags);
      string algoPath = PathFromStrings(algoPathName.first,algoPathName.second);
      klog << log4cpp::Priority::DEBUG << " algoPath " << algoPath;
      fAlgoNames.push_back(algoPathName.second);
      algoPath = MergeStrings(algoPath,".xml");
      fAlgoPath.push_back(algoPath);

      const XMLElement*  nextAlgo = algoElement->NextSiblingElement ("Algo") ;

      while (nextAlgo != NULL)
      {
        algoPathName = ParseStringPair(nextAlgo,fStags);
        algoPath = PathFromStrings(algoPathName.first,algoPathName.second);
        algoPath = MergeStrings(algoPath,".xml");
        fAlgoNames.push_back(algoPathName.second);
        fAlgoPath.push_back(algoPath);
        nextAlgo = nextAlgo->NextSiblingElement ("Algo") ;
      }
    }
  }
//--------------------------------------------------------------------
  void AlexConf::ParseAlgos()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseAlgos() " ;

    klog << log4cpp::Priority::DEBUG << " Number of algos registered = " 
    << fAlgoNames.size();
    
    for (auto i=0; i < fAlgoNames.size(); ++i)
    {
      string algoPath = fAlgoPath[i];
      string algoName = fAlgoNames[i];
      
      klog << log4cpp::Priority::DEBUG << " for algo number = " << i;
      klog << log4cpp::Priority::DEBUG << " algoPath =" << algoPath;
      klog << log4cpp::Priority::DEBUG << " algoName =" << algoName;

      fDoc.LoadFile( algoPath.c_str() );
      if (fDoc.ErrorID()!=0) 
      {
        klog << log4cpp::Priority::ERROR 
        << "ParseConfiguration::Failed loading config file error = " 
        << fDoc.ErrorID();
        exit (EXIT_FAILURE);
      }
      XMLElement* rootElement = fDoc.RootElement(); 

      //Parse Debug
      klog << log4cpp::Priority::DEBUG << "++Parse Debug+++ " ;
      const XMLElement* debugElement = rootElement->FirstChildElement ("Debug") ;
      const XMLElement* elem = debugElement->FirstChildElement ("level") ;
      std::string debug = elem->GetText();
      
      fAlgoDebug[algoName]=debug;
      
      //Parse Param
       klog << log4cpp::Priority::DEBUG << "++Parse Param+++ " ;
      const XMLElement* param = rootElement->FirstChildElement ("Param") ;
      if (param != NULL)
      {
        vector<DParam> paramVector;

        DParam par = ParseParamElement(param);
        paramVector.push_back(par);
        param = param->NextSiblingElement ("Param") ;
        while (param != NULL)
        {
          DParam par = ParseParamElement(param);
          paramVector.push_back(par);
          param = param->NextSiblingElement ("Param") ;
        }
        fAlgoParam[algoName]=paramVector;
      }

      //Parse Array
      const XMLElement* array = rootElement->FirstChildElement ("Array") ;
      if (array != NULL)
      {
        vector<DArray> arrayVector;
        DArray ar = ParseArrayElement(array);
        arrayVector.push_back(ar);
        array = array->NextSiblingElement ("Array") ;
        while (array != NULL)
        {
          DArray ar = ParseArrayElement(array);
          arrayVector.push_back(ar);
          array = array->NextSiblingElement ("Array") ;
        }
        fAlgoArray[algoName]=arrayVector;
      }
    
      //Parse H1D
      const XMLElement* h1d = rootElement->FirstChildElement ("H1D") ;
      if (h1d != NULL)
      {
        vector<DH1> h1Vector;
        DH1 h1 = ParseH1DElement(h1d);
        h1Vector.push_back(h1);
        h1d = h1d->NextSiblingElement ("H1D") ;
        while (h1d != NULL)
        {
          DH1 h1 = ParseH1DElement(h1d);
          h1Vector.push_back(h1);
          h1d = h1d->NextSiblingElement ("H1D") ;
        }
        fAlgoH1D[algoName]=h1Vector;
      }

      //Parse H2D
      const XMLElement* h2d = rootElement->FirstChildElement ("H2D") ;
      if (h2d != NULL)
      {
        vector<DH2> h2Vector;
        DH2 h2 = ParseH2DElement(h2d);
        h2Vector.push_back(h2);
        h2d = h2d->NextSiblingElement ("H2D") ;
        while (h2d != NULL)
        {
          DH2 h2 = ParseH2DElement(h2d);
          h2Vector.push_back(h2);
          h2d = h2d->NextSiblingElement ("H2D") ;
        }
        fAlgoH2D[algoName]=h2Vector;
      }
    }
  }


//--------------------------------------------------------------------
  vector<string> AlexConf::WriteAlgoHeaders()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " WriteAlgoHeaders() " ;
    vector<string> algoHeaders;
    for (auto algoName : fAlgoNames) 
    {
      ostringstream s;

      s<<"\n#ifndef ALGO"<<algoName<<"_" << endl;
      s<<"#define ALGO"<<algoName<<"_" << endl;
      s<<"// Generated by AlexConf: do not edit" << endl;

      s<<"#include <string>" << endl;
      s<<"#include <vector>" << endl;
      s<<"#include <utility>" << endl;
      s<<"#include <memory>" << endl;
      s<<"#include <map>" << endl;
      s<<"#include <TH1F.h>" << endl;
      s<<"#include <TH2F.h>" << endl;
      s<<"#include <alex/IAlgorithm.h>" << endl;
      s<<"#include " << '"' << "P" <<algoName  <<".h" << '"' << endl;

      s<<"namespace alex {" << endl;
      s << "  class " << algoName << ": public IAlgorithm," << "P"<<algoName << "{" << endl;
      s << "  public:" << endl;
      s << "    "<< algoName << "();" << endl;
      s << "    ~"<< algoName << "(){}" << endl;
      s << "    bool Init() ;"<< endl;
      s << "    bool Execute() ;"<< endl;
      s << "    bool End() ;"<< endl;
      s << "  private:"<< endl;
      s << "    std::string fName ;"<< endl;
      s << "    std::string fDebug ;"<< endl;
      std::vector<alex::DParam> vparam = fAlgoParam[algoName];
      for (auto param : vparam)
      {
        if(param.DataType()=="double")
          s << "    double "<< param.Name() << ";" <<endl;
        else if(param.DataType()=="int")
          s << "    int "<< param.Name() << ";" <<endl;
        else
          s << "    std::string "<< param.Name() <<";" <<endl;
      }

      std::vector<alex::DArray> varray = fAlgoArray[algoName];
      for (auto array : varray)
      {
        if(array.DataType()=="double")
          s << "    std::vector<double> "<< array.Name() << ";" <<endl;
        else if(array.DataType()=="int")
          s << "    std::vector<int> "<< array.Name() << ";" <<endl;
        else
          s << "    std::vector<std::string> "<< array.Name() << ";" <<endl;
      }
      std::vector<alex::DH1> vh1 = fAlgoH1D[algoName];
      for (auto h1 : vh1)
      {
        s << "    TH1F* "<< h1.Name() << ";" <<endl;
      }

      std::vector<alex::DH2> vh2 = fAlgoH2D[algoName];
      for (auto h2 : vh2)
      {
        s << "    TH2F* "<< h2.Name() << ";" <<endl;
      }

      s << "  };"<< endl;
      s << "}"<< endl;
      s << "#endif "<< endl;
      algoHeaders.push_back(s.str());
    }
    return algoHeaders;
  }

//--------------------------------------------------------------------
  std::string AlexConf::WriteAlgoCPP()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " WriteAlgoCPP() " ;
    ostringstream s;

    s<<"// Generated by AlexConf: do not edit" << endl;
    s<<"#include <alex/LogUtil.h>" <<endl;
    s<<"#include <alex/Alex.h>" <<endl;
    s<<"#include <TFile.h>" <<endl;

    for (auto algoName : fAlgoNames) 
    {
      s<<"#include "<< '"'<<algoName<<".hh"<< '"'<< endl;
    }

    s<<"namespace alex {" << endl;

    for (auto algoName : fAlgoNames) 
    {
      s << "\n\n  "<<algoName<<"::"<<algoName<<"()"<<endl;
      s << "  {" << endl;
      s << "   fName =" << '"' << algoName  << '"' << ";"<< endl;
      s << "   fDebug =" << '"'<<fAlgoDebug[algoName] << '"' << ";" << endl;
      s << "   InitLogger(fName);" << endl;
      s << "   SetDebugLevel(fDebug,fName);" << endl;
      s << "   TDirectory* adir = Alex::Instance().HistoFile().mkdir(fName.c_str());" 
                << endl;
    
      std::vector<alex::DParam> vparam = fAlgoParam[algoName];
      for (auto param : vparam)
        if(param.DataType()=="string")
          s << "   "<< param.Name() << " = " <<'"' <<param.Value() <<'"'<< ";" << endl;
        else
          s << "   "<< param.Name() << " = " <<param.Value() << ";" << endl;
          
      std::vector<alex::DArray> varray = fAlgoArray[algoName];
      for (auto array : varray)
      {
        std::vector<std::string> values = array.Split() ;
        s << "   "<< array.Name() << ".reserve(" <<array.Dim() << ");" << endl;
        for (auto value: values)
          s << "   "<< array.Name() << ".push_back(" <<value << ");" << endl;
      }

      std::vector<alex::DH1> vh1 = fAlgoH1D[algoName];
      for (auto h1 : vh1)
      {
        s << "    "<< h1.Name() << "= new TH1F("<<'"'<<h1.Name() <<'"' <<"," <<
          '"'<<h1.Title() <<'"' <<"," <<
          h1.Nbinsx() <<"," <<
          h1.Xlow() <<"," <<
          h1.Xup() << ");" << endl;
        s << "    "<< h1.Name() << "->SetDirectory(adir);" <<endl; 
      }

      std::vector<alex::DH2> vh2 = fAlgoH2D[algoName];
      for (auto h2 : vh2)
      {
        s << "    "<< h2.Name() << "= new TH2F("<<'"'<<h2.Name() <<'"' <<"," <<
          '"'<<h2.Title() <<'"' <<"," <<
          h2.Nbinsx() <<"," <<
          h2.Xlow() <<"," <<
          h2.Xup() <<"," <<
          h2.Nbinsy() <<"," <<
          h2.Ylow() <<"," <<
          h2.Yup()  << ");" << endl;
        s << "    "<< h2.Name() << "->SetDirectory(adir);" <<endl;
      }
      
      s << "  }" << endl;
    }
    s << "}" << endl;
    //s << std::ends;
    return s.str();
  }


//--------------------------------------------------------------------
  std::string AlexConf::WriteRegisterAlgos() const
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " WriteRegisterAlgos() " ;
    ostringstream s;

    s<<"// Generated by AlexConf: do not edit" << endl;
    s<<"#include <alex/Alex.h>" << endl;
    s<<"#include "<<'"'<<"RegisterAlgosHeader.hh"<<'"' << endl;
    
    for (auto algoName : fAlgoNames) 
    {
      s<<"#include " <<'"' <<algoName<<".hh" <<'"'<< endl;
    }

    //s<<"using namespace alex ;" << endl;
    s<<"void alex::RegisterAlgos()" << endl;
    s<<"{" << endl;
    for (auto algoName : fAlgoNames) 
      {
        s<<"  auto algo_"<<algoName<<"=new "<<algoName<<"();"<<endl;
        s<<"  Alex::Instance().RegisterAlgorithm(algo_"<<algoName<<");"<<endl;
      }
    s<<" }" << endl;
  
    return s.str();
  }

//--------------------------------------------------------------------
  std::string AlexConf::WriteRegisterAlgosHeader() const
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " WriteRegisterAlgosHeader() " ;
    ostringstream s;
    s<<"\n#ifndef ALGOREGISTER_"<< endl;
    s<<"#define ALGOREGISTER_"<< endl;
    s<<"// Generated by AlexConf: do not edit" << endl;
    s<<"namespace alex {" << endl;
    s<<" void RegisterAlgos();" << endl;
    s<<"}" << endl;
    s << "#endif "<< endl;
    return s.str();
  }

//--------------------------------------------------------------------
  std::string AlexConf::WriteAlgoHeaderFile() const
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " WriteAlgoHeaderFile() " ;
    ostringstream s;

    s<<"\n#ifndef ALGOHEADERFILE_" << endl;
    s<<"#define ALGOHEADERFILE_" << endl;
    s<<"// Generated by AlexConf: do not edit" << endl;
    for (auto algoName : fAlgoNames) 
    {
      s<<"#include " <<'"' <<algoName<<".hh" <<'"'<< endl;
    }
    s << "#endif "<< endl;
    return s.str();
  }

//--------------------------------------------------------------------
  std::pair<string,string> AlexConf::ParseStringPair(const XMLElement* mom, 
                                                    const std::pair<string,string>& tags) 
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseStringPair() " ;

    klog << log4cpp::Priority::DEBUG << " ParseStringPair:: tags.first=" << tags.first;
    const XMLElement* elem = mom->FirstChildElement (tags.first.c_str()) ;
    string first = elem->GetText();
    klog << log4cpp::Priority::DEBUG << " first=" << first;


    klog << log4cpp::Priority::DEBUG << " ParseStringPair:: tags.second=" << tags.second;
    const XMLElement*  nextElem = mom->FirstChildElement (tags.second.c_str());
    string second = nextElem->GetText();
    klog << log4cpp::Priority::DEBUG << " second=" << second;

    std::pair<string,string> pathName;
    pathName.first = first;
    pathName.second = second;
    return pathName;

  }

//--------------------------------------------------------------------
  std::pair<int,int> AlexConf::ParseIntPair(const XMLElement* mom, 
                                               const std::pair<string,string>& tags) 
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseIntPair() " ;

    const XMLElement* elem = mom->FirstChildElement (tags.first.c_str()) ;
    string first = elem->GetText();
    klog << log4cpp::Priority::DEBUG << " first = " << first;

    const XMLElement*  nextElem = mom->FirstChildElement (tags.second.c_str());
    //const XMLElement*  nextElem = elem->NextSiblingElement (tags.second.c_str()) ;
    string second = nextElem->GetText();
    klog << log4cpp::Priority::DEBUG << " second = " << second;

    std::pair<int,int> intPair;
    intPair.first = atoi(first.c_str());
    intPair.second = atoi(second.c_str());
    return intPair;

  }

//--------------------------------------------------------------------
  DParam AlexConf::ParseParamElement(const XMLElement* param) const
//--------------------------------------------------------------------
  {
    //   <Param>
    //   <name>dataPath</name>
    //   <dataType>string</dataType>
    //   <value>/Users/jjgomezcadenas/Development/NEXT/DATA</value>
    // </Param>
    
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseParamElement() " ;

    const XMLElement* nameParam = param->FirstChildElement ("name") ;
    string textNameParam = nameParam->GetText();
    klog << log4cpp::Priority::DEBUG << " Param name text = " << textNameParam;

    const XMLElement* dataTypeParam = param->FirstChildElement ("dataType") ;
    string dataTypeParamText= dataTypeParam->GetText();
    klog << log4cpp::Priority::DEBUG << "Param data type text =" << dataTypeParamText;

    const XMLElement* ValueParam = param->FirstChildElement ("value") ;
    string ValueParamText= ValueParam->GetText();
    klog << log4cpp::Priority::DEBUG << "Param value text =" << ValueParamText;

    auto par = DParam();
    par.SetData(textNameParam,dataTypeParamText,ValueParamText);
    return par;
  }
//--------------------------------------------------------------------
  DArray  AlexConf::ParseArrayElement(const XMLElement* array) const
//--------------------------------------------------------------------
  {
    //   <Array>
    //   <name>P</name>
    //   <dataType>double</dataType>
    //   <dim>3</dim>
    //   <value>0.1 1.0 3</value>
    // </Array>

    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseArrayElement() " ;

    const XMLElement* name = array->FirstChildElement ("name") ;
    string textName = name->GetText();
    klog << log4cpp::Priority::DEBUG << " Array name text = " << textName;

    const XMLElement* dataType = array->FirstChildElement ("dataType") ;
    string textDataType= dataType->GetText();
    klog << log4cpp::Priority::DEBUG << "Array data type text =" << textDataType;

    const XMLElement* dim = array->FirstChildElement ("dim") ;
    string textDim= dim->GetText();
    klog << log4cpp::Priority::DEBUG << "Array dim text =" << textDim;

    const XMLElement* value = array->FirstChildElement ("value") ;
    string textValue= value->GetText();
    klog << log4cpp::Priority::DEBUG << "Array value text =" << textValue;

    auto ar = DArray();
    ar.SetData(textName,textDataType,textDim,textValue);
    return ar;
  }

//--------------------------------------------------------------------
  DH1 AlexConf::ParseH1DElement(const XMLElement* h1d) const
//--------------------------------------------------------------------
  {
    //   <H1D>
    //     <name>fHY</name>
    //     <title>Y distribution</title>
    //     <nbinsx>50</nbinsx>
    //     <xlow>-10.0</xlow>
    //     <xup>10.0</xup>
    //   </H1D>
    
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseH1DElement() " ;

    const XMLElement* name = h1d->FirstChildElement ("name") ;
    string textName = name->GetText();
    klog << log4cpp::Priority::DEBUG << " H1D name text = " << textName;

    const XMLElement* title = h1d->FirstChildElement ("title") ;
    string textTitle= title->GetText();
    klog << log4cpp::Priority::DEBUG << "H1D title text =" << textTitle;

    const XMLElement* nbinsx = h1d->FirstChildElement ("nbinsx") ;
    string textNbinsx= nbinsx->GetText();
    klog << log4cpp::Priority::DEBUG << "nbinsx text =" << textNbinsx;

    const XMLElement* xlow = h1d->FirstChildElement ("xlow") ;
    string textXlow= xlow->GetText();
    klog << log4cpp::Priority::DEBUG << "xlow text =" << textXlow;

    const XMLElement* xup = h1d->FirstChildElement ("xup") ;
    string textXup= xup->GetText();
    klog << log4cpp::Priority::DEBUG << "xup text =" << textXup;

    auto h1 = DH1();
    h1.SetData(textName,textTitle,textNbinsx,textXlow,textXup);
    return h1;
  }
//--------------------------------------------------------------------
  DH2 AlexConf::ParseH2DElement(const XMLElement* h2d) const
//--------------------------------------------------------------------
  {
    //   <H2D>
    //     <name>fHYZ</name>
    //     <title>Y vs Z distribution</title>
    //     <nbinsx>10</nbinsx>
    //     <nbinsy>10</nbinsy>
    //     <xlow>-10.0</xlow>
    //     <xup>10.0</xup>
    //     <ylow>-10.</ylow>
    //     <yup>10.0</yup>
    //   </H2D>
    // </ToyAnalysis2>
    log4cpp::Category& klog = GetLogger("AlexConfigure");
    klog << log4cpp::Priority::DEBUG << " ParseH2DElement " ;

    const XMLElement* name = h2d->FirstChildElement ("name") ;
    string textName = name->GetText();
    klog << log4cpp::Priority::DEBUG << " H2D name text = " << textName;

    const XMLElement* title = h2d->FirstChildElement ("title") ;
    string textTitle= title->GetText();
    klog << log4cpp::Priority::DEBUG << "H2D title text =" << textTitle;

    const XMLElement* nbinsx = h2d->FirstChildElement ("nbinsx") ;
    string textNbinsx= nbinsx->GetText();
    klog << log4cpp::Priority::DEBUG << "nbinsx text =" << textNbinsx;

    const XMLElement* nbinsy = h2d->FirstChildElement ("nbinsy") ;
    string textNbinsy= nbinsy->GetText();
    klog << log4cpp::Priority::DEBUG << "nbinsy text =" << textNbinsy;

    const XMLElement* xlow = h2d->FirstChildElement ("xlow") ;
    string textXlow= xlow->GetText();
    klog << log4cpp::Priority::DEBUG << "xlow text =" << textXlow;

    const XMLElement* xup = h2d->FirstChildElement ("xup") ;
    string textXup= xup->GetText();
    klog << log4cpp::Priority::DEBUG << "xup text =" << textXup;

    const XMLElement* ylow = h2d->FirstChildElement ("ylow") ;
    string textYlow= ylow->GetText();
    klog << log4cpp::Priority::DEBUG << "ylow text =" << textYlow;

    const XMLElement* yup = h2d->FirstChildElement ("yup") ;
    string textYup= yup->GetText();
    klog << log4cpp::Priority::DEBUG << "yup text =" << textYup;

    auto h2 = DH2();
    h2.SetData(textName,textTitle,textNbinsx,textXlow,textXup,
      textNbinsy,textYlow,textYup);

    return h2;

  }
}

