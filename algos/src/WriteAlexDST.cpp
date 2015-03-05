#include "WriteAlexDST.hh"
#include <alex/LogUtil.h>
#include <alex/ISvc.h>
#include <alex/AEvent.h>

namespace alex {

  //--------------------------------------------------------------------
  bool WriteAlexDST::Init()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    klog << log4cpp::Priority::INFO << "WriteAlexDST::Init()" ;

    klog << log4cpp::Priority::INFO << "Instantiate AEvent" ;

    fAevent = new AEvent();
    std::stringstream s;

    s << fDstPath << "/" << fDstName;
    std::string filename = s.str();

    klog << log4cpp::Priority::INFO << " Alex DST file " 
    << filename;

    klog << log4cpp::Priority::DEBUG << " new TFile " ;

    fFile = new TFile(filename.c_str(), "RECREATE");

    klog << log4cpp::Priority::DEBUG << " Create Tree " ;

    fAevtTree = new TTree("AEVENT","Alex event tree");

    klog << log4cpp::Priority::DEBUG << " Set Branch to event " ;

    fAevtTree->Branch("ABRANCH", "alex::AEvent",&fAevent);
    
    return true;
  }
  //--------------------------------------------------------------------
  bool WriteAlexDST::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    
    klog << log4cpp::Priority::DEBUG << " WriteAlexDST::Execute";
    klog << log4cpp::Priority::DEBUG 
    << " Instantiate TEvent for event number " 
    << ISvc::Instance().GetEvtNum();

    fAevent->SetEvtNum(ISvc::Instance().GetEvtNum());

    klog << log4cpp::Priority::DEBUG 
    << " Set Event true energy to = " 
    << ISvc::Instance().GetTrueEventEnergy();

    fAevent->SetTrueEventEnergy(
      ISvc::Instance().GetTrueEventEnergy());

    klog << log4cpp::Priority::DEBUG 
    << " Set Event rec energy to = " 
    << ISvc::Instance().GetRecEventEnergy();

    fAevent->SetRecEventEnergy(
      ISvc::Instance().GetRecEventEnergy());

    fAevent->SetEnergyResolution(ISvc::Instance().ResolutionFWHM());

    
    klog << log4cpp::Priority::DEBUG 
    << " ---Adding Particles to event--- ";

    // Getting Alex Particles
    klog << log4cpp::Priority::DEBUG << "+++Getting Alex particles";

    std::vector<alex::AParticle*> 
    aParticles = ISvc::Instance().GetAlexParticles();
    
    klog << log4cpp::Priority::DEBUG << "-->number of aParticles =" 
    << aParticles.size();
  
    int t=0;
    for (auto aPart : aParticles) 
    {
      t++;
      klog << log4cpp::Priority::DEBUG 
           << "Adding particle " << t << " to AEvent";
      fAevent->AddParticle(aPart);
      fEnergyOfParticles_h1->Fill(aPart->GetEkin());
      fTrackLength_h1->Fill(aPart->GetParam("TrackLength"));
    }

    fNumberOfParticles_h1->Fill(aParticles.size()); 
    
    fAevent->SetRecEventEnergy(ISvc::Instance().GetRecEventEnergy());
    fAevent->SetTrueEventEnergy(ISvc::Instance().GetTrueEventEnergy());
    fRecEnergyOfEvent_h1->Fill(fAevent->GetRecEventEnergy());
    fTrueEnergyOfEvent_h1->Fill(fAevent->GetTrueEventEnergy());

    klog << log4cpp::Priority::DEBUG << "-------Print AEvent------" ;
    klog << log4cpp::Priority::DEBUG <<fAevent->PrintInfo();


// Fill Tree
    
    klog << log4cpp::Priority::DEBUG 
    << " Fill Tree ";
    
    fAevtTree->Fill();

    klog << log4cpp::Priority::DEBUG 
    << " Print Tree ";

    fAevtTree->Print();

    klog << log4cpp::Priority::DEBUG << " Clear event " ;

    // char userInput;
    // std::cout << "type any character and return to continue" << std::endl;
    // std::cin >> userInput;

    fAevent->ClearEvent();


    return true;
  }
  //--------------------------------------------------------------------
  bool WriteAlexDST::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = GetLogger(fName);
    klog << log4cpp::Priority::DEBUG << " WriteDST::END";

    klog << log4cpp::Priority::DEBUG << " Write and close";
    fFile = fAevtTree->GetCurrentFile();

    fFile->Write();
    fFile->Close();

    klog << log4cpp::Priority::DEBUG << " delete TEvent";
    delete fAevent;

    return true;
  }
}
