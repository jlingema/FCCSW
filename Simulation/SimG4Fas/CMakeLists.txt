################################################################################
# Package: SimG4Fast
################################################################################
gaudi_subdir(SimG4Fas v1r0)

# this declaration will not be needed in the future
gaudi_depends_on_subdirs(GaudiAlg Simulation/SimG4Comps Simulation/SimG4Com Sim/SimG4Common Sim/SimG4Fast Sim/SimG4Interface)

find_package(Geant4)
include(${Geant4_USE_FILE})
find_package(ROOT)

gaudi_install_headers(SimG4FastFcc)

gaudi_add_library(SimG4FastFcc
                 src/lib/*.cpp
                 INCLUDE_DIRS SimG4ComFcc FWCore SimG4ComponentsFcc  Geant4 ROOT SimG4Common SimG4Fast
                 LINK_LIBRARIES GaudiAlgLib SimG4ComFcc Geant4 ROOT SimG4Common SimG4Fast
                 PUBLIC_HEADERS SimG4FastFcc)

gaudi_add_module(SimG4FastPluginsFcc
                 src/components/*.cpp
                 INCLUDE_DIRS Geant4 SimG4ComFcc SimG4FastFcc SimG4Common SimG4Fast
                 LINK_LIBRARIES GaudiAlgLib Geant4 SimG4FastFcc SimG4ComFcc SimG4Common SimG4Fast)
