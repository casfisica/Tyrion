# Tyrion
EDMFilter

To run the code:

export SCRAM_ARCH=slc6_amd64_gcc530

scram p -n VLF_Fill CMSSW CMSSW_8_1_0 #The first time

cd VLF_Fill/src

cmsenv

git clone git@github.com:casfisica/Tyrion.git

scram b
