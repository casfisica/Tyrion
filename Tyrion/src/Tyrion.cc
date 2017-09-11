// -*- C++ -*-
//
// Package:    VLF_Fill/Tyrion
// Class:      Tyrion
// 
/**\class Tyrion Tyrion.cc VLF_Fill/Tyrion/plugins/Tyrion.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Salazar Gonzalez
//         Created:  Wed, 06 Sep 2017 09:31:52 GMT
//
//

#include "VLF_Fill/Tyrion/interface/Tyrion.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//
// Counters
int Tyrion::NoCuts; 
int Tyrion::TriggerPathCut;
int Tyrion::aJetatLessCut;
int Tyrion::LeadingMuPtM3;


//
// constructors and destructor
//
Tyrion::Tyrion(const edm::ParameterSet& iConfig):
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAlone>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  tok_jets_(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("objet"))),
  tok_met_(consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag>("obmet"))),
  tok_muons_(consumes<edm::View<pat::Muon> >(iConfig.getParameter<edm::InputTag>("obmuon")))
{
   //now do what ever initialization is needed

}


Tyrion::~Tyrion()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
Tyrion::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  using namespace edm;
  
  
  //Trigger
  edm::Handle<edm::TriggerResults> triggerBits;
  edm::Handle<pat::TriggerObjectStandAlone> triggerObjects;
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
  
  iEvent.getByToken(triggerBits_, triggerBits);
  iEvent.getByToken(triggerObjects_, triggerObjects);
  iEvent.getByToken(triggerPrescales_, triggerPrescales);
  
  
  /*Handling Muons*/
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByToken(tok_muons_, muons);
  /*Handling Jets*/
  edm::Handle<edm::View<pat::Jet> > jets;
  iEvent.getByToken(tok_jets_,jets);
  /*Handling MET*/   
  edm::Handle<edm::View<pat::MET> > mets;
  iEvent.getByToken(tok_met_,mets);
  
  ////////////////////////////
  
  //Cunting events
  Tyrion::NoCuts++;
  /*Flag to the filter*/
  bool filterflag = false;
  
  const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
  //   std::cout << "\n == TRIGGER PATHS= " << std::endl;
  for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i){
    
    /*Cut the version of the trigger path*/
    std::string nameV = names.triggerName(i);
    std::string version ="_v";
    size_t start_pos = nameV.rfind(version);
    std::string TriggerNameVersionOff;
    if (start_pos != std::string::npos){
      TriggerNameVersionOff= nameV.erase(start_pos, version.length()+4);
    }
    
    /*End cut de version*/

     
    /*See if path pass*/
    std::string TriggerWanted="HLT_PFMET110_PFMHT110_IDTight";

    if( TriggerNameVersionOff ==  TriggerWanted ) {
      if(triggerBits->accept(i)){
	//Cunting events pass trigger
	Tyrion::TriggerPathCut++;
	if( jets->size() > 0 ){
	  Tyrion::aJetatLessCut++;
	  if( muons->size() > 0 ){
	    // loop muon collection and fill histograms
	    /* at less a muon Pt>3 GeV*/
	    
	    bool flagLeadingMuPtM3=false;
	    for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
	      if( muon->pt() > 3 )
		flagLeadingMuPtM3=true;
	    }
	    
	    if ( flagLeadingMuPtM3 ){
	      Tyrion::LeadingMuPtM3++;
	      std::cout <<"Number of muons: " << muons->size() <<std::endl;
	      filterflag=true;
	    } 
	  } /*End cut at less a muon Pt>3 GeV*/
	} /*End cut a jet at less*/       
      }
    }/*end See if path pass*/  
        
  }/*End for trigger*/
  if(filterflag){
    return true; 
  }
  
  return false;
  
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
Tyrion::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
Tyrion::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
Tyrion::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
Tyrion::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
Tyrion::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
Tyrion::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Tyrion::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(Tyrion);
