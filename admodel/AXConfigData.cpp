// ----------------------------------------------------------------------------
///  \file   AXConfigData.h
///  \brief  provides Configuration data for Alex
///
///  \author    gomez@mail.cern.ch
///  \date     March 2015
///  
///  Copyright (c) 2015 NEXT Collaboration
//
// ----------------------------------------------------------------------------

#include <alex/AXConfigData.h>



using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

ClassImp(alex::AXConfigData)

namespace alex {


//--------------------------------------------------------------------
  string AXConfigData::PrintInfo() const
//--------------------------------------------------------------------
  {
    cout << "PrintInfo: GetLevelDebug =" << GetLevelDebug() << endl;
    std::stringstream s;
    s << std::endl;    
   
    s << "++++++Alex Config Data++++++\n";
    s  << " levelDebug (DEBUG, INFO, WARN, etc) = " 
         << GetLevelDebug() << endl;
    s  << " mode ( IRENE or ALEX depending of the input DST =" 
         << GetMode() <<endl; 
    s  << " dst path to IRENE or ALEX input DST = " 
         << GetDstFile() <<endl;
    s  << " histo path to output histo = " 
         << GetHistoFile() << endl;
    s  << " initial event number = " 
         << GetStartEvent() << endl;
    s  << " final  event number = " 
         << GetFinalEvent() << endl;
    s  << " events to debug (d)  = " 
         << GetEventDebug() << endl;

  return s.str();
  }
}

