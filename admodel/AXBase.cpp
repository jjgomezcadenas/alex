// ----------------------------------------------------------------------------
///  \file   AXBase.cpp
///  \brief  provides ID, properties, parameters Debug and name
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
//
// ----------------------------------------------------------------------------

#include <alex/AXBase.h>

ClassImp(alex::AXBase)

namespace alex {
std::string AXBase::PrintInfo() const
  {
    std::stringstream s;
    s << std::endl;    
    s << "ID = " << fId << std::endl;

    s << std::endl; 
    for (std::map<std::string,std::string>::const_iterator 
          it=fProperties.begin(); 
    			it!=fProperties.end(); ++it)
    	{
    		s << "Property["<<it->first <<"]="<< it->second << std::endl;
    	}

    for (std::map<std::string,double>::const_iterator 
          it=fParam.begin(); 
          it!=fParam.end(); ++it)
      {
        s << "Param["<<it->first <<"]="<< it->second << std::endl;
      }

      return s.str();
  }

  std::string AXBase::PrintProperties() const
    {
      std::stringstream s;   
      for (std::map<std::string,std::string>::const_iterator 
           it=fProperties.begin(); 
           it!=fProperties.end(); ++it)
      {
        s << "    Property["<<it->first <<"] = "<< it->second << std::endl;
      }

      for (std::map<std::string,double>::const_iterator 
          it=fParam.begin(); 
          it!=fParam.end(); ++it)
      {
        s << "Param["<<it->first <<"]="<< it->second << std::endl;
      }
      return s.str();
    }
}

