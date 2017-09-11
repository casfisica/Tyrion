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


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Utilities/interface/StreamID.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//Need to nkow if some of these are not need
#include <map>
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class declaration
//
#ifndef TYRION_H
#define TYRION_H

class Tyrion : public edm::stream::EDFilter<> {
   public:
  /// Constructor
      explicit Tyrion(const edm::ParameterSet&);
  /// Destructor
      ~Tyrion();

  // Operations
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  /*Here declare the tokens*/
  
  /*Trigger*/
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAlone> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  /**/
  edm::EDGetTokenT<edm::View<pat::Jet> > tok_jets_;
  edm::EDGetTokenT<edm::View<pat::MET> >  tok_met_;
  edm::EDGetTokenT<edm::View<pat::Muon> > tok_muons_;

  //Counters
  static int NoCuts; 
  static int TriggerPathCut;
  static int aJetatLessCut;
  static int LeadingMuPtM3;


};

#endif
