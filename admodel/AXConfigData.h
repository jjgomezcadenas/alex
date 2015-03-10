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

#ifndef AXCONFD_
#define AXCONFD_


#include <alex/GDefs.h>
#include <TNamed.h>

using std::string;
namespace alex {

class AXConfigData : public TNamed {
  public:
    AXConfigData() : fLevelDebug("DEBUG"),fMode("IRENE"),fDstFile("")
                     ,fHistoFile(""),fStartEvent(0),fFinalEvent(10),fEventDebug(10)
    {};
    ~AXConfigData(){};
  
    string GetLevelDebug() const {return fLevelDebug;}
    string GetMode() const {return fMode;}
    string GetDstFile() const {return fDstFile;}
    string GetHistoFile() const {return fHistoFile;}
    int GetStartEvent() const {return fStartEvent;}
    int GetFinalEvent() const {return fFinalEvent;}
    int GetEventDebug() const {return fEventDebug;}

    void SetLevelDebug (string alevelDebug) {fLevelDebug = alevelDebug;}
    void SetMode (string aMode) {fMode = aMode;}
    void SetDstFile (string aDstFile) {fDstFile = aDstFile;}
    void SetHistoFile (string aHistoFile) {fHistoFile = aHistoFile;}
    void SetStartEvent (int aStartEvent) {fStartEvent = aStartEvent;}
    void SetFinalEvent (int aFinalEvent) {fFinalEvent = aFinalEvent;}
    void SetEventDebug (int aEventDebug) {fEventDebug = aEventDebug;}

    std::string PrintInfo() const ; 

  protected:
    string fLevelDebug; // follows Log4CPP conventions DEBUG, INFO, WARN
    // running mode: can be IRENE/TALEX/RALEX/ALEX depending of the input DST
    string fMode; 
    string fDstFile; // input DST
    string fHistoFile; //output histogram file
    // configures the number of events to run
    int fStartEvent, fFinalEvent, fEventDebug; 

    ClassDef(AXConfigData,1);
  };
}


#endif
