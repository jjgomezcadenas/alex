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

#ifndef AXBASE_
#define AXBASE_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TNamed.h>


namespace alex {

  class AXBase : public TNamed   {
    
  public:

    // Constructors
    AXBase(){};
    
    // Destructor
    virtual ~AXBase(){};

    // ID
    int GetID() const
    {return fId;}

    void SetID(int id)
    {fId = id;}

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
    
    ClassDef(AXBase,1);

  };

  
}


#endif
