################################################################################
# Package: DetCommon
################################################################################
gaudi_subdir(DetCommon v1r0)

gaudi_depends_on_subdirs(GaudiKernel Detector/DetSegmentation)

find_package(DD4hep COMPONENTS DDG4 DDSegmentation REQUIRED)
find_package(Geant4)
include(${Geant4_USE_FILE})

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}  ${DD4hep_ROOT}/cmake )
include( DD4hep )

find_package(ROOT COMPONENTS MathCore GenVector Geom REQUIRED)

gaudi_install_headers(DetCommon)
gaudi_add_library(DetCommon
                 src/*.cpp
                 INCLUDE_DIRS DD4hep ROOT Geant4 DetSegmentation
                 LINK_LIBRARIES GaudiKernel DD4hep ROOT Geant4 DetSegmentation ${DD4hep_COMPONENT_LIBRARIES}
                 PUBLIC_HEADERS DetCommon)

set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(STATUS "LIBRARY_OUTPUT_PATH -> ${LIBRARY_OUTPUT_PATH}")
dd4hep_generate_rootmap(DetCommon)

include(CTest)
gaudi_add_test(DumpSimpleBox
               WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
               FRAMEWORK tests/dumpSimpleBox.py)
gaudi_add_test(PrintOverlaps_Extrusions
               WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
               ENVIRONMENT LD_PRELOAD+=build.$BINARY_TAG/lib/libDetSegmentation.so 
               COMMAND python ${DD4hep_ROOT}/python/checkOverlaps.py -c Detector/DetFCChhBaseline1/compact/FCChh_DectMaster.xml
               PASSREGEX "Number of illegal overlaps/extrusions : 0" )
gaudi_add_test(PrintOverlaps_Sampling
               WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
               ENVIRONMENT LD_PRELOAD+=build.$BINARY_TAG/lib/libDetSegmentation.so 
               COMMAND python ${DD4hep_ROOT}/python/checkOverlaps.py -c Detector/DetFCChhBaseline1/compact/FCChh_DectMaster.xml -o s
               PASSREGEX "Number of illegal overlaps/extrusions : 0" )
