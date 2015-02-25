
// ----------------------------------------------------------------------------
//  $Id: ToyData.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 


#include <alex/StringOperations.h>
#include <alex/Gdefs.h>
#include "DArray.h"


using std::string; 
using std::cout;
using std::cin; 
using std::endl; 
using std::ostream;
using std::ostringstream;
using std::vector;

namespace alex {


//--------------------------------------------------------------------
  std::string DArray::Serialize() const
//--------------------------------------------------------------------
  {
    ostringstream s;
    
    s << "{Array: name = " << Name() << " Type = " << DataType()
        << " Dim = "<< Dim() <<  " Value = " << Value() <<"}"<<endl <<std::ends;
    return s.str();
  }

//--------------------------------------------------------------------
  std::vector<std::string>  DArray::Split() 
//--------------------------------------------------------------------
  {
  	return SplitString(Value());
  }

}

