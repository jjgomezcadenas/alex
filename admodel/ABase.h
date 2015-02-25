#ifndef ABASE_
#define ABASE_

#include <alex/TDefs.h>
#include <alex/GDefs.h>
#include <TObject.h>

// Base class: provides ID, properties, Debug and root dicionary

namespace alex {

  class ABase : public TObject   {
    
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

    std::string PrintInfo() const ; 
    std::string PrintProperties() const;
    
  protected:
    int fId; // Unique identification number
    std::map <std::string, std::string> fProperties; // Properties if needed 
    std::string fDebug;
    
    ClassDef(ABase,1);

  };

  
}


#endif
