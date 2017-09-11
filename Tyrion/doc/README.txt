----------------------------------------------------------------------
			Parts of the Filter
----------------------------------------------------------------------
BuildFile.xml			Tell the scram where to find the source code 
				(i.e. ###.cc), of the includes you use in 
				the code source or headers.

interface/Tyrion.h		Heder of the src/Tyrion.cc, functions and class
				declarations.

src/Tyrion.cc			Source code, for the filter 

data/filter_defaults_cfi.py	Default configurations for the filter, can be
				overload in de filter.cfg

test/filter_cfg.py			cms executable.
