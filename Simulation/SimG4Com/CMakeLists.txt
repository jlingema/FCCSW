################################################################################
# Package: SimG4Com
################################################################################
gaudi_subdir(SimG4Com v1r0)

# this declaration will not be needed in the future
gaudi_depends_on_subdirs(GaudiAlg Sim/SimG4Common)

find_package(Geant4)
include(${Geant4_USE_FILE})
find_package(ROOT)
find_package(FCCEDM)
find_package(PODIO)

gaudi_install_headers(SimG4Com)

gaudi_add_library(SimG4ComFcc
                 src/*.cpp
                 INCLUDE_DIRS FWCore Geant4 ROOT FCCEDM PODIO SimG4Common
                 LINK_LIBRARIES GaudiAlgLib Geant4 ROOT FCCEDM PODIO SimG4Common
                 PUBLIC_HEADERS SimG4Com)
