from Gaudi.Configuration import *
from Configurables import ApplicationMgr, HepMCReader, HepMCDumper

reader = HepMCReader("Reader", Filename="/afs/cern.ch/exp/fcc/sw/0.7/testsamples/FCC_minbias_100TeV.dat")
reader.DataOutputs.hepmc.Path = "hepmc"

from Configurables import HepMCConverter
hepmc_converter = HepMCConverter("Converter")
hepmc_converter.DataInputs.hepmc.Path="hepmc"
hepmc_converter.DataOutputs.genparticles.Path="allGenParticles"
hepmc_converter.DataOutputs.genvertices.Path="allGenVertices"

from Configurables import GenParticleFilter
genfilter = GenParticleFilter("StableParticles", accept=[1], OutputLevel=DEBUG)
genfilter.DataInputs.genparticles.Path = "allGenParticles"
genfilter.DataOutputs.genparticles.Path = "stableGenParticles"

from Configurables import GeoSvc
geoservice = GeoSvc("GeoSvc", detectors=['file:Test/TestGeometry/data/Barrel_testCaloSD_phieta.xml'], OutputLevel = ERROR)

from Configurables import SimG4Svc
geantservice = SimG4Svc("SimG4Svc")

from Configurables import SimG4Alg, SimG4SaveCalHits, InspectHitsCollectionsTool, SimG4PrimariesFromEdmTool
inspecttool = InspectHitsCollectionsTool("inspect", readoutNames=["ECalHits"], OutputLevel = ERROR)
savecaltool = SimG4SaveCalHits("saveECalHits", readoutNames = ["ECalHits"], OutputLevel = ERROR)
savecaltool.DataOutputs.positionedCaloHits.Path = "positionedCaloHits"
savecaltool.DataOutputs.caloHits.Path = "caloHits"
particle_converter = SimG4PrimariesFromEdmTool("EdmConverter")
particle_converter.DataInputs.genParticles.Path = "stableGenParticles"
geantsim = SimG4Alg("SimG4Alg",
                    outputs= ["SimG4SaveCalHits/saveECalHits", "InspectHitsCollectionsTool/inspect"],
                    eventProvider=particle_converter)

from Configurables import FCCDataSvc, PodioOutput
podiosvc = FCCDataSvc("EventDataSvc")
out = PodioOutput("out", filename="testPhiEtaSegmentation.root")
out.outputCommands = ["keep *"]

ApplicationMgr(EvtSel='NONE',
               EvtMax=1,
               TopAlg=[reader, hepmc_converter, genfilter, geantsim, out],
               ExtSvc = [podiosvc, geoservice, geantservice],
               OutputLevel=ERROR)
