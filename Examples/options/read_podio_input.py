from Gaudi.Configuration import *

from Configurables import ApplicationMgr, FCCDataSvc, PodioOutput

podioevent   = FCCDataSvc("EventDataSvc", input="output.root")

# reads HepMC text file and write the HepMC::GenEvent to the data service
from Configurables import PodioInput, ReadTestConsumer, BuildParticleGraph, ParticleGraphTool
podioinput = PodioInput("PodioReader", collections=["allGenVertices", "stableGenParticles"], OutputLevel=DEBUG)
graph_builder = BuildParticleGraph()
graph_builder.DataInputs.generatedParticles.Path = "stableGenParticles"
checker = ReadTestConsumer("TestConsumer", OutputLevel=DEBUG)
checker.DataInputs.genParticles.Path = "stableGenParticles"

out = PodioOutput("out", filename="out2.root",
                   OutputLevel=DEBUG)
out.outputCommands = ["keep *"]

ApplicationMgr(
    TopAlg = [podioinput, graph_builder, checker, out],
    EvtSel = 'NONE',
    EvtMax   = 3,
    ExtSvc = [podioevent],
 )

