// ----------------------------------------------------------------------------
///  \file   AXBase.h
///  \brief  provides ID, properties, parameters Debug and name
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
//
// ----------------------------------------------------------------------------

#ifndef ABASE_
#define ABASE_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TNamed.h>


namespace alex {

  class ABase : public TNamed   {
    
  public:

    // Constructors
    ABase(){};
    
    // Destructor
    virtual ~ABase(){};

    // ID
    int GetID() const
    {return fId;}

    void SetID(int id)
    {fId = id;}

    // ID
    std::string GetDebug() const
    {return fDebug;}

    void SetDebug(std::string debug)
    {fDebug = debug;}

    // Properties
    std::map <std::string, std::string> GetProperties() const
    {return fProperties;}
    
    std::string GetProperty(std::string name) 
    {return fProperties[name];}
    
    void SetProperty(std::string name, std::string value)
    {fProperties[name]=value;}

    // Params
    std::map <std::string, double> GetParams() const
    {return fParam;}
    
    double GetParam(std::string name) 
    {return fParam[name];}
    
    void SetParam(std::string name, double value)
    {fParam[name]=value;}

    std::string PrintInfo() const ; 
    std::string PrintProperties() const;
    
  protected:
    int fId; // Unique identification number
    std::map <std::string, std::string> fProperties; // Properties if needed 
    std::map <std::string, double> fParam; // Properties if needed 
    std::string fDebug;
    
    ClassDef(ABase,1);

  };

  
}


#endif
