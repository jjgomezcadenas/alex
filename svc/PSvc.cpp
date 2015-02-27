
// ----------------------------------------------------------------------------
//  $Id: PSvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <TStopwatch.h>
#include <alex/PSvc.h>
#include <alex/LogUtil.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {

  //--------------------------------------------------------------------
  void PaolinaManager::Init(std::string debugLevel,
                            std::vector<std::pair<double,double> > detSize)
  //--------------------------------------------------------------------
  {
    fDebugLevel=debugLevel;
    fDetSize = detSize;

    InitLogger("Psvc");
    SetDebugLevel(fDebugLevel,"Psvc");

    log4cpp::Category& klog  = GetLogger("Psvc");
    klog << log4cpp::Priority::DEBUG << "Paolina Service Initialized" ;

  }


//--------------------------------------------------------------------
  void PaolinaManager::SetLevelDebug(std::string debugLevel)
//--------------------------------------------------------------------
  {

    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel,"Psvc");
    
  }

  //--------------------------------------------------------------------
  std::vector<std::pair<TVector3,double> > 
  PaolinaManager::ComputePaolinaVoxels(std::vector<std::pair<TLorentzVector,double> > hits,
                                       std::vector<double> voxelSize)
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog  = GetLogger("Psvc");

    klog << log4cpp::Priority::DEBUG << "PaolinaManager::ComputePaolinaVoxels()" ;
    klog << log4cpp::Priority::DEBUG << "Voxel size: x = " 
    << voxelSize[0]<< "  y = " << voxelSize[1] << "  z = " << voxelSize[2];

    TStopwatch*  timer = new TStopwatch();
    timer->Start();

    paolina::VoxelBuilder* PVB = new paolina::VoxelBuilder(voxelSize, fDetSize);
    fPvoxels = PVB->FillVoxels(hits);
    delete PVB;

    timer->Stop(); 
    double rtime = timer->RealTime();
    double cctime = timer->CpuTime();
    delete timer;

    klog << log4cpp::Priority::DEBUG << "Paolina finds " 
         << fPvoxels.size() << " voxels" ;

    klog << log4cpp::Priority::DEBUG << "RealTime = " << rtime << " seconds"
         << " CpuTime = " << cctime << " seconds";


    std::vector<std::pair<TVector3,double> > theVoxels;
    for (auto vox : fPvoxels)
    { 
      std::pair<TVector3,double> theVox;
      const paolina::vector3<double> vpos = vox->GetPosition();

      TVector3 theVector;
      theVector[0]= vpos.x();
      theVector[1]= vpos.y();
      theVector[2]= vpos.z();
      theVox.first = theVector;
      theVox.second =   vox->GetEDep(); 
      theVoxels.push_back(theVox);   
    }   

    return theVoxels;
  }


  //--------------------------------------------------------------------
  std::vector<paolina::Track*>  PaolinaManager::ComputePaolinaTracks()
  //--------------------------------------------------------------------  
  {
    log4cpp::Category& klog  = GetLogger("Psvc");
    klog << log4cpp::Priority::DEBUG << "PaolinaManager::ComputePaolinaTracks()" ;
  
    if(fPvoxels.size() == 0)
    {
      klog << log4cpp::Priority::FATAL 
      << "ERROR: size of Voxel vector is cero, have you created voxels?";
      exit(-1);
    }

    TStopwatch*  timer = new TStopwatch();
    timer->Start();
    paolina::TrackBuilder* PTB = new paolina::TrackBuilder();
    fPtracks = PTB->IdentifyTracks(fPvoxels);
    delete PTB;
    timer->Stop(); 
    double rtime = timer->RealTime();
    double cctime = timer->CpuTime();
    delete timer;

    klog << log4cpp::Priority::DEBUG << "Paolina finds " 
         << fPtracks.size() << " paolina tracks";

    klog << log4cpp::Priority::DEBUG << "RealTime =" << rtime << " seconds"
         << " CpuTime = " << cctime << "seconds";

    return fPtracks;
  }


  //--------------------------------------------------------------------
  std::pair<paolina::Blob*, paolina::Blob*> PaolinaManager::ComputePaolinaBlobs(
                                                                          double blobRadius)
  //--------------------------------------------------------------------  
  {
    log4cpp::Category& klog  = GetLogger("Psvc");

    klog << log4cpp::Priority::DEBUG << " PaolinaManager::ComputePaolinaBlobs()";
  
    if(fPtracks.size() == 0)
    {
      klog << log4cpp::Priority::FATAL 
      << "ERROR: size of Track vector is cero, have you created tracks?";
      exit(-1);
    }

    TStopwatch*  timer = new TStopwatch();
    timer->Start();

    paolina::BlobBuilder* PBB = new paolina::BlobBuilder(blobRadius);    
    fPblobs = PBB->MakeBlobs(fPtracks.at(0));
    delete PBB;

    timer->Stop(); 
    double rtime = timer->RealTime();
    double cctime = timer->CpuTime();
    delete timer;

    klog << log4cpp::Priority::INFO << "Found Blobs";
        
    klog << log4cpp::Priority::INFO << "RealTime =" << rtime << " seconds"
         << " CpuTime = " << cctime << "seconds";

    return fPblobs;
  }


  //--------------------------------------------------------------------
  std::string PaolinaManager::PrintVoxels()
  //--------------------------------------------------------------------
  {
    std::ostringstream s;
    s << std::endl;

    s << " Paolina Voxels: " << std::endl;

    std::vector<std::pair<TVector3,double> > theVoxels;
    for (auto vox : fPvoxels)
    { 
      std::pair<TVector3,double> theVox;
      const paolina::vector3<double> vpos = vox->GetPosition();
      double edep =   vox->GetEDep();

      s 
           << " x (mm) = " << vpos.x()
           << " y (mm) = " << vpos.y()
           << " z (mm) = " << vpos.z()
           << " edep (MeV) = " << edep << std::endl;    
    }
    return s.str();   
  }


  //--------------------------------------------------------------------
  std::string PaolinaManager::PrintBlobs()
  //--------------------------------------------------------------------
  {
    std::ostringstream s;
    s << std::endl;

    s << " Paolina Blobs: " << std::endl;

    paolina::Blob* pb1 = fPblobs.first;
    paolina::Blob* pb2 = fPblobs.second;

    s 
           << " Blob 1 radius = " << pb1->GetRadius()
           << " Blob 1 energy = " << pb1->GetEnergy()
           << " Blob 2 radius = " << pb2->GetRadius()
           << " Blob 2 energy = " << pb2->GetEnergy()
           << std::endl;    
    
    return s.str(); 
  }


  //--------------------------------------------------------------------
  std::string PaolinaManager::PrintTracks()
  //--------------------------------------------------------------------
  {
    std::ostringstream s;
    s << std::endl;

    s << " Paolina Tracks: " << std::endl;

    int i=0;
    for (auto trk : fPtracks)
    { 
      
      int nb =trk->NBlobs(); 
      
      s 
           << " Track number " << i
           << " Number of blobs " << nb
           << std::endl;

      for(int ib=0; ib < nb; ib++)
      {
        s 
           << " blob number " << ib
           << std::endl;

        const paolina::Blob* blob =trk-> GetBlob(ib) ;

        s 
           << " Blob radius " << blob->GetRadius()
           << " Blob energy = " << blob->GetEnergy()
           << std::endl;
      }

      int nv = trk->NVoxels() ;

      s 
           << " Number of voxels " << nv
           << std::endl;

      for(int iv=0; iv < nv; iv++)
      {
        s 
           << " voxel number " << iv
           << std::endl;

        const paolina::Voxel* vox = trk->GetVoxel(iv);
        const paolina::vector3<double> vpos = vox->GetPosition();
        double edep =   vox->GetEDep();
        
        s 
           << " x (mm) = " << vpos.x()
           << " y (mm) = " << vpos.y()
           << " z (mm) = " << vpos.z()
           << " edep (MeV) = " << edep << std::endl; 
      
      }
      i++;
    }

    return s.str();   
  }

}
