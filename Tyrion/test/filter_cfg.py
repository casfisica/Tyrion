import FWCore.ParameterSet.Config as cms

#set up a process named FILTER
processName = "FILTER"
process = cms.Process(processName)

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.load('VLF_Fill.Tyrion.data.filter_defaults_cfi')


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            #   replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/120000/14473FEF-1ACD-E611-8C84-00266CFFBC60.root'
        )
                            )
    
# loads your EDFilter
process.Filter = cms.EDFilter('Tyrion')



# talk to output module
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("test2.root")
                               )



# Defines which modules and sequences to run
process.mypath = cms.Path(process.Filter)



# A list of analyzers or output modules to be run after all paths have been run.
process.outpath = cms.EndPath(process.out)





#process F =
#{
    
    #
    # load input file
    #
    
#    untracked PSet maxEvents = {untracked int32 input = 10}
    
    
    
    
#    source = PoolSource
#    {
#        untracked vstring fileNames = {"file:h_zz_4mu.root"}
#        }
    
    # include filter_defaults.cfi
#    include "VLF_Fill/Tyrion/data/filter_defaults_cfi.py"
    #replace trackFilter.MinimalNumberOfTracks = 4
    #replace trackFilter.MaximalNumberOfTracks = 4
    
    #
    # write results out to file
    #
#   module Out = PoolOutputModule
#   {
#       untracked string fileName = "events-filtered.root"
#       }
#   
#   endpath e =
#   {
#       VLFFilter,Out
#       }
#   }
