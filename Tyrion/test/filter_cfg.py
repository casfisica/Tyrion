import FWCore.ParameterSet.Config as cms

#set up a process named FILTER
processName = "FILTER"
process = cms.Process(processName)

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.load('VLF_Fill.Tyrion.data.filter_defaults_cfi')


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
                            #   replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/120000/14473FEF-1ACD-E611-8C84-00266CFFBC60.root'
        )
                            )
    
# loads your EDFilter
process.Filter = cms.EDFilter('Tyrion',
                              bits = cms.InputTag("TriggerResults","","HLT"),
                              prescales = cms.InputTag("patTrigger"),
                              objects = cms.InputTag("selectedPatTrigger"),
                              obmuon=cms.InputTag("slimmedMuons"),
                              objet=cms.InputTag("slimmedJets"),
                              obmet=cms.InputTag("slimmedMETs"),
                              
                              )

# Defines which modules and sequences to run
process.mypath = cms.Path(process.Filter)


# talk to output module
# To output all events

#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string("test2.root")
#                               )

#To select only that pass Filter
process.out = cms.OutputModule("PoolOutputModule",
        fileName = cms.untracked.string('savep1.root'),
        SelectEvents = cms.untracked.PSet(
                SelectEvents = cms.vstring('mypath&noexception')
                )
        )


# A list of analyzers or output modules to be run after all paths have been run.
process.outpath = cms.EndPath(process.out)

