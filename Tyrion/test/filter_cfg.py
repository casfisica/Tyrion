process F =
{

  #
  # load input file
  #

  untracked PSet maxEvents = {untracked int32 input = -1}


  process.source = cms.Source("PoolSource",
#   replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
         'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/120000/14473FEF-1ACD-E611-8C84-00266CFFBC60.root'
        )
                            )



  source = PoolSource
  {
    untracked vstring fileNames = {"file:h_zz_4mu.root"}
  }

  # include filter_defaults.cfi
  include "VLF_Fill/Tyrion/data/filter_defaults_cfi.py"
  #replace trackFilter.MinimalNumberOfTracks = 4
  #replace trackFilter.MaximalNumberOfTracks = 4

  #
  # write results out to file
  #
  module Out = PoolOutputModule
  {
    untracked string fileName = "events-filtered.root"
  }

  endpath e =
  {
    VLFFilter,Out
  }
}
