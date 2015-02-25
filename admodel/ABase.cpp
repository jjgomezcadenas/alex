
// ----------------------------------------------------------------------------
//  $Id: ABase.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/ABase.h>

ClassImp(alex::ABase)

namespace alex {
std::string ABase::PrintInfo() const
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

      return s.str();
  }

  std::string ABase::PrintProperties() const
    {
      std::stringstream s;   
      for (std::map<std::string,std::string>::const_iterator 
           it=fProperties.begin(); 
           it!=fProperties.end(); ++it)
      {
        s << "    Property["<<it->first <<"] = "<< it->second << std::endl;
      }
      return s.str();
    }
}

