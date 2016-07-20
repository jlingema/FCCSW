from Gaudi.Configuration import *

from Configurables import ApplicationMgr, FCCDataSvc, PodioOutput

podioevent   = FCCDataSvc("EventDataSvc")

# reads HepMC text file and write the HepMC::GenEvent to the data service
from Configurables import PodioInput, ReadTestConsumer, BuildParticleGraph, ParticleGraphTool
podioinput = PodioInput("PodioReader", filename="output.root", collections=["allGenVertices", "allGenParticles", "hits"], OutputLevel=DEBUG)
graph_builder = BuildParticleGraph()
graph_builder.DataInputs.generatedParticles.Path = "allGenParticles"
graph_tool = ParticleGraphTool()
checker = ReadTestConsumer("TestConsumer", graphTool=graph_tool, OutputLevel=DEBUG)

out = PodioOutput("out", filename="out2.root",
                   OutputLevel=DEBUG)
out.outputCommands = ["keep *"]

ApplicationMgr(
    TopAlg = [podioinput, graph_builder, checker, out],
    EvtSel = 'NONE',
    EvtMax   = 3,
    ExtSvc = [podioevent],
 )

