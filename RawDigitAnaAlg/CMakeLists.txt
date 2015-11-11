# basic source code CMakeLists.txt

art_make_library( LIBRARY_NAME  ub_RawDigitAnaAlg
	SOURCE RawDigitAnaAlg.cxx
	LIBRARIES
                 ${ROOT_BASIC_LIB_LIST}
#			Geometry
#		        Utilities
#	                uboone_Geometry
#                      OpticalDetectorData
#			OpticalDetector
                     RawData
#			RecoBase
#			Simulation
#			SimulationBase

)

install_headers()
install_source()
