
// ----------------------------------------------------------------------------
//  $Id: ISvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 


#include <alex/ISvc.h>
#include <alex/LogUtil.h>
#include <alex/VectorOperations.h>


using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {

  //--------------------------------------------------------------------
  void IreneManager::Init(std::string debugLevel)
  //--------------------------------------------------------------------
  {
    fDebugLevel = debugLevel;

    InitLogger("Isvc");
    SetDebugLevel(fDebugLevel,"Isvc");

    log4cpp::Category& klog  = GetLogger("Isvc");
    klog << log4cpp::Priority::DEBUG << "IreneManager::Init()" ;
   
  }

//--------------------------------------------------------------------
  void IreneManager::SetLevelDebug(std::string debugLevel)
  //--------------------------------------------------------------------
  {

    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel,"Isvc");
    
  }
  //--------------------------------------------------------------------
  void IreneManager::LoadEvent(const irene::Event* ievt)
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog  = GetLogger("Isvc");
    klog << log4cpp::Priority::DEBUG << "***** IreneManager::LoadEvent " 
    << ievt->GetID();

    fIevt = ievt;
    fTrueHits.clear();
    fIevt->FillHitVector(fTrueHits, "ACTIVE");

    klog << log4cpp::Priority::DEBUG 
    << "IreneManager::Size of hit vector: " << fTrueHits.size(); 

    klog << log4cpp::Priority::DEBUG << "IreneManager:: Fill tracks" ;

    fIreneTracks = fIevt->Tracks();
    klog << log4cpp::Priority::DEBUG 
    << "IreneManager::Size of tracks vector: " << fIreneTracks.size();

    klog << log4cpp::Priority::DEBUG << "IreneManager:: Fill particles" ;
    fIreneParticles= fIevt->Particles();
    klog << log4cpp::Priority::DEBUG 
    << "IreneManager::Size of particles vector: " << fIreneParticles.size();

  }


  //--------------------------------------------------------------------
  const irene::Event& IreneManager::GetEvent()
  //--------------------------------------------------------------------
  {
    return *fIevt;
  }


  //--------------------------------------------------------------------
  void IreneManager::GetTrueVertex()
  //--------------------------------------------------------------------
  { 
    log4cpp::Category& klog  = GetLogger("Isvc");
    klog.debug("In IreneManager::GetTrueVertex(): Fill true vertex");

    bool found=false;
    TLorentzVector Vertex;
  
    for (size_t it = 0; it < fIreneTracks.size(); it++)
    { 
      const irene::Track* itrk = fIreneTracks.at(it) ; 
      const irene::Particle* ipart= itrk->GetParticle();

      klog.debug("++++Irene particle associated to track number %lu\n",it);
    
      if (ipart->IsPrimary()) 
      {
        Vertex = ipart->GetInitialVertex();
        found = true;
        break;
      } 
    } 
  
    if (found==false)
      klog.error("Error! vertex not found!");


    for (int i=0; i< 3; i++)
        fVertex[i]= Vertex[i];
      
  }


  //--------------------------------------------------------------------
  void IreneManager::PrintHits()
  //--------------------------------------------------------------------
  {
    std::cout << " Irene Hits: " << std::endl;

    for(auto ihit : fTrueHits)
    {
      TLorentzVector vl = ihit.first;
      double e = ihit.second;
      std::cout 
           << " x (mm) = " << vl[0]
           << " y (mm) = " << vl[1]
           << " z (mm) = " << vl[2]
           << " edep (MeV) = " << e << std::endl;    
    }
  }


  //--------------------------------------------------------------------
  void IreneManager::PrintTrueEvent()
  //--------------------------------------------------------------------
  {
    std::cout << "***** TRUE EVENT " << fIevt->GetID() << " *****" << std::endl;

    int numParts = fIreneTracks.size();
    for (size_t it = 0; it < numParts; it++) { 
      const irene::Track* itrk = fIreneTracks.at(it) ; 
      const irene::Particle* ipart= itrk->GetParticle();

      std::cout << "* Particle " << ipart->GetParticleID();
      if (ipart->IsPrimary()) std::cout << ": Primary " << ipart->Name() << std::endl;
      else {
        std::cout << ": Secondary " << ipart->Name()
                  << "     from Particle " << ipart->GetMother()->GetParticleID()
                  << std::endl;
      }

      TLorentzVector fIniP = ipart->GetInitialMomentum();
      std::cout << "  Init:  Vertex: " << PrintTVector3(ipart->GetInitialVertex().Vect())
                << "  Process: " << ipart->GetCreatorProcess()
                << "  EKin: " << fIniP.Energy() - fIniP.M() << std::endl;

      TLorentzVector fDecP = ipart->GetDecayMomentum();
      std::cout << "  Decay: Vertex: " << PrintTVector3(ipart->GetDecayVertex().Vect())
                << "  EKin: " << fDecP.Energy() - fDecP.M() << std::endl;

      const TRefArray& daughters = ipart->GetDaughters();
      std::cout << "  Daughters: ";
      for (int d=0; d<daughters.GetLast()+1; d++) {
        irene::Particle* daughter = (irene::Particle*) daughters.At(d);
        std::cout << daughter->GetParticleID() << ", ";
      }
      std::cout << std::endl;

      std::cout << std::endl;
    }
  }

}
