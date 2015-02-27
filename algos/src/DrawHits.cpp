#include "DrawHits.hh"
#include <alex/ISvc.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TApplication.h>
namespace alex {

  //--------------------------------------------------------------------
  bool DrawHits::Init()
  //--------------------------------------------------------------------
  {
    
    char * ch ;
    int argc = 0;
    TApplication * gApplication = new TApplication("DrawHits", &argc, &ch);
    gApplication->SetReturnFromRun(true);

    //log4cpp::Category& klog = log4cpp::Category::getRoot(); 
    //app->Run(kTRUE);

    return true;
  }
  //--------------------------------------------------------------------
  bool DrawHits::Execute()
  //--------------------------------------------------------------------
  {
  
    log4cpp::Category& klog = GetLogger(fName);

    klog << log4cpp::Priority::DEBUG << " DrawHits::Execute";
    klog << log4cpp::Priority::DEBUG << " Debug level " << fDebug;
    

    IHits allHits = ISvc::Instance().GetTrueHits();
    klog << log4cpp::Priority::DEBUG << " true hits = " << allHits.size();

  
    char userInput;
    TCanvas * c1 = new TCanvas("c1", "Hits", 10, 10, 600, 600);
    TH2F* h2_xyAll = new TH2F("h2_xy","xy hits",200,-100.,100.,200,-100.,100.);

    for(auto hit : allHits)
      h2_xyAll->Fill(hit.first.X(),hit.first.Y());  
    
    // Draw the histogram.
      
    klog << log4cpp::Priority::INFO << " Drawing histogram..." ;
  
    h2_xyAll->GetXaxis()->SetTitle("x");
    h2_xyAll->GetYaxis()->SetTitle("y");
    h2_xyAll->Draw("colz");
      //h2_xyAll->SetMarkerStyle(6);

      // h2_xyAll->Draw("SAME");
    c1->Update();

      // Process ROOT events allowing for the drawing of the histogram.
      //gSystem->ProcessEvents();

      // Await input from the user before continuing.
    std::cout << "type any character and return to continue" << std::endl;
    std::cin >> userInput;

      // Close the plot and delete the histogram.
    c1->Close();
    delete h2_xyAll;
    delete c1;
  
    return true;
  }
  //--------------------------------------------------------------------
  bool DrawHits::End()
  //--------------------------------------------------------------------
  {
    return true;
  }
}
