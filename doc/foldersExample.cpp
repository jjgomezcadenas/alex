void AddClones (Int_t n, TClonesArray * clones, const char *classname)
{
    //add n objects of classname to clones
    TClonesArray & c = *clones;
    for (Int_t i = 0; i < n; i++)
    {
	new (c[i]) TNamed (classname, classname);
    }
}

void AddArray (Int_t n, TObjArray * array, const char *classname)
{
    //add n objects of classname to array

    for (Int_t i = 0; i < n; i++)
    {
	array->Add (new TNamed (classname, classname));
    }
}

void AddDetectors (TFolder * detectors)
{
    TFolder *CASTOR = detectors->AddFolder ("CASTOR", "CASTOR event data");
    TFolder *CPV = detectors->AddFolder ("CPV", "CPV event data");
    TFolder *FMD = detectors->AddFolder ("FMD", "FMD event data");
    TFolder *ITS = detectors->AddFolder ("ITS", "ITS event data");
    TFolder *MUON = detectors->AddFolder ("MUON", "MUON event data");
    TFolder *PHOS = detectors->AddFolder ("PHOS", "PHOS event data");
    TFolder *PMD = detectors->AddFolder ("PMD", "PMD event data");
    TFolder *RICH = detectors->AddFolder ("RICH", "RICH event data");
    TFolder *START = detectors->AddFolder ("START", "START event data");
    TFolder *TOF = detectors->AddFolder ("TOF", "TOF event data");
    TFolder *TPC = detectors->AddFolder ("TPC", "TPC event data");
    TFolder *TRD = detectors->AddFolder ("TRD", "TRD event data");
    TFolder *ZDC = detectors->AddFolder ("ZDC", "ZDC event data");
}

void AddTrees (TFolder * aliroot)
{
    TFolder *Trees = aliroot->AddFolder ("Trees", "AliRoot Trees");

    Trees->Add (new TTree ("TreeR", "Run Tree"));
    Trees->Add (new TTree ("TreeH", "Hits Tree"));
    Trees->Add (new TTree ("TreeD", "Digits Tree"));
    Trees->Add (new TTree ("TreeE", "Event Summary Tree"));
    Trees->Add (new TTree ("TreeK", "Event Kinematics Tree"));
}


void folders ()
{
    //script to prototype AliRoot folders

    gSystem->Load ("libEG");
    TFolder *aliroot =
	gROOT->GetRootFolder ()->AddFolder ("aliroot",

					    "aliroot top level folders");
    gROOT->GetListOfBrowsables ()->Add (aliroot, "aliroot");

    TFolder *constants = 
        aliroot->AddFolder ("Constants", "Detector constants");

    TFolder *pdg = constants->AddFolder ("DatabasePDG", "PDG database");

    pdg->Add (new TNamed ("TDatabasePDG", "PDG data base"));

    TFolder *run = aliroot->AddFolder ("Run", "Run dependent folders");

    run->Add (new TNamed ("header", "AliRunHeader"));

    TFolder *configuration =
	run->AddFolder ("Configuration", "Run configuration");

    TFolder *run_mc =
	aliroot->AddFolder ("RunMC", "MonteCarlo run dependent folders");

    run->Add (new TNamed ("header", "AliRunMCHeader"));

    TFolder *configuration_mc =
	run_mc->AddFolder ("Configuration", "MonteCarlo run configuration");

    TFolder *modules =
	configuration->AddFolder ("Modules", "Pointers to detector objects");

    modules->Add (new TNamed ("BODY",
		     "AliBODY (ALICE envelop) geometry and constants"));
    modules->Add (new TNamed ("MAG", "AliMAGGeometry and constants"));
    modules->Add (new TNamed ("ABSO", "AliABSOGeometry and constants"));
    modules->Add (new TNamed ("DIPO", "AliDIPOGeometry and constants"));
    modules->Add (new TNamed ("HALL", "AliHALLGeometry and constants"));
    modules->Add (new TNamed ("FRAME", "AliFRAMEGeometry and constants"));
    modules->Add (new TNamed ("SHIL", "AliSHILGeometry and constants"));
    modules->Add (new TNamed ("PIPE", "AliPIPEGeometry and constants"));
    modules->Add (new TNamed ("CASTOR", "AliCASTORGeometry and constants"));
    modules->Add (new TNamed ("CPV", "AliCPVGeometry and constants"));
    modules->Add (new TNamed ("FMD", "AliFMDGeometry and constants"));
    modules->Add (new TNamed ("ITS", "AliITSGeometry and constants"));
    modules->Add (new TNamed ("MUON", "AliMUONGeometry and constants"));
    modules->Add (new TNamed ("PHOS", "AliPHOSGeometry and constants"));
    modules->Add (new TNamed ("PMD", "AliPMDGeometry and constants"));
    modules->Add (new TNamed ("RICH", "AliRICHGeometry and constants"));
    modules->Add (new TNamed ("START", "AliSTARTGeometry and constants"));
    modules->Add (new TNamed ("TOF", "AliTOFGeometry and constants"));
    modules->Add (new TNamed ("TPC", "AliTPCGeometry and constants"));
    modules->Add (new TNamed ("TRD", "AliTRDGeometry and constants"));
    modules->Add (new TNamed ("ZDC", "AliZDCGeometry and constants"));

    TFolder *Field = configuration->AddFolder ("Field", "Magnetic field maps");

    Field->Add (new TNamed ("Central", "AliMagFcentral mag field object"));
    Field->Add (new TNamed ("Dipole", "AliMagFdipole mag field object"));

    TFolder *conditions = run->AddFolder ("Conditions", "Run conditions");
    TFolder *calibration =
	conditions->AddFolder ("Calibration", "Detector calibration data");

    AddDetectors (calibration);

    TFolder *aligment =
	conditions->AddFolder ("Aligment", "Detector aligment");

    TFolder *generators =
	configuration_mc->AddFolder ("Generators",
				     "list of generator objects");
    generators->
	Add (new TNamed ("Hijing", "AliHijingGenerator event generator"));
    generators->
	Add (new TNamed ("Cocktail", "AliCocktailGenerator generator"));

    TFolder *virtualMC =
	configuration_mc->AddFolder ("VirtualMC", "the Virtual MC");

    virtualMC->Add (new TNamed ("Geant3", "the TGeant3 object"));


    TFolder *event_mc =
	run_mc->AddFolder ("EventMC", "MonteCarlo event folders");

    event_mc->Add (new TNamed ("EventMCHeader", "AliEventMCHeader"));

    TClonesArray *kine = new TClonesArray ("TParticle");
    kine->SetName ("EventKinematics");
    event_mc->Add (kine);
    AddClones (100, kine, "TParticle");

    TFolder *event_mc_hits = event_mc->AddFolder ("Hits", "MonteCarlo hits");

    AddDetectors (event_mc_hits);


    TFolder *event = run->AddFolder ("Event", "Event folders");

    event->Add (new TNamed ("Header", "AliEventHeader"));
    TFolder *event_digits = event->AddFolder ("Digits", "Detector raw data");

    AddDetectors (event_digits);

    TFolder *event_rec =
	event->AddFolder ("RecData", "Detectors reconstucted data");

    AddDetectors (event_rec);

    TFolder *central =
	event_rec->AddFolder ("CentralTracker", "ITS+TPC common tracking");

    TFolder *central_its = central->AddFolder ("ITS", "ITS tracks");
    TClonesArray *itsTracks = new TClonesArray ("TNamed");

    itsTracks->SetName ("ItsTracks");
    central_its->Add (itsTracks);
    AddClones (100, itsTracks, "ItsLocalTrack");

    TFolder *central_tpc = central->AddFolder ("TPC", "TPC tracks");
    TClonesArray *tpcTracks = new TClonesArray ("TNamed");

    tpcTracks->SetName ("TPCTracks");
    central_tpc->Add (tpcTracks);
    AddClones (100, tpcTracks, "TPCLocalTrack");

    TClonesArray *centralTracks = new TClonesArray ("TNamed");

    centralTracks->SetName ("CentralTracks");
    central->Add (centralTracks);
    AddClones (100, centralTracks, "CentralGlobalTrack");

    new     TBrowser ();
}