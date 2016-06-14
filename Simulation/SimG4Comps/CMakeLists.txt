################################################################################
# Package: SimG4Components
################################################################################
gaudi_subdir(SimG4Comps v1r0)

# this declaration will not be needed in the future
gaudi_depends_on_subdirs(GaudiAlg FWCore Detector/DetInterface Simulation/SimG4Com Sim/SimG4Common)

find_package(Geant4)
include(${Geant4_USE_FILE})
find_package(DD4hep COMPONENTS DDG4)
find_package(ROOT COMPONENTS MathCore GenVector Geom REQUIRED)

gaudi_add_module(SimG4ComponentsFcc
                 src/*.cpp
                 INCLUDE_DIRS Geant4 FWCore DD4hep ROOT SimG4Common SimG4ComFcc
                 LINK_LIBRARIES GaudiAlgLib Geant4 FWCore DD4hep ROOT SimG4Common SimG4ComFcc)


# include(CTest)
# gaudi_add_test(GeantFullSimHCal
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#                FRAMEWORK tests/options/geant_fullsim_hcal.py)
# gaudi_add_test(GeantFullSimECal
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#                FRAMEWORK tests/options/geant_fullsim_ecal.py)
# gaudi_add_test(GeantFullSimGdml
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#                FRAMEWORK tests/options/geant_fullsim_gdml.py)
# gaudi_add_test(GeantFullSimMoreEvents
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                FRAMEWORK tests/options/geant_fullsim_moreEvents.py)
# gaudi_add_test(GeantFullSimMoreEventsCheckNoEvents
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                COMMAND python ./scripts/geant_fullsim_moreEvents_checkNoEvents.py
#                DEPENDS GeantFullSimMoreEvents)
# gaudi_add_test(GeantFullSimMoreEventsCheckNoParticles
#                ENVIRONMENT PYTHONPATH+=$ENV{PODIO}/python
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                COMMAND python ./scripts/geant_fullsim_moreEvents_checkNoParticles.py
#                DEPENDS GeantFullSimMoreEvents)
# gaudi_add_test(GeantFastSimSimpleSmearing
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                FRAMEWORK tests/options/geant_fastsim_simple.py)
# gaudi_add_test(GeantFastSimSimpleSmearingCheckSigma
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                COMMAND python ./scripts/geant_fastsim_simple_checkSigma.py
#                DEPENDS GeantFastSimSimpleSmearing)
# gaudi_add_test(GeantFastSimSimpleSmearingCheckNoParticles
#                ENVIRONMENT PYTHONPATH+=$ENV{PODIO}/python
#                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Sim/SimG4Components/tests/
#                COMMAND python ./scripts/geant_fastsim_checkNoParticles.py
#                DEPENDS GeantFastSimSimpleSmearing)

