
### \file
### \ingroup BasicExamples
### | **input (alg)**                                      | other algorithms                   |                                       | **output (alg)**                                 |
### | ---------------------------------------------------- | ---------------------------------- | ------------------------------------- | ------------------------------------------------ |
### | generate Pythia events and save them to HepMC format | convert `HepMC::GenEvent` to EDM   | generate graph from EDM MCParticles   |  write the EDM output to ROOT file using PODIO   |

from Gaudi.Configuration import *

from Configurables import FCCDataSvc
# needed for gen step:
from Configurables import PythiaInterface, HepMCConverter
# for building and accessing the traversable MCParticle graph:
from Configurables import ParticleGraphTestConsumer, BuildParticleGraph, ParticleGraphTool


### Example of pythia configuration file to generate events
pythiafile="Generation/data/Pythia_standard.cmd"
# Example of pythia configuration file to read LH event file
#pythiafile="options/Pythia_LHEinput.cmd"

#### Data service
podioevent = FCCDataSvc("EventDataSvc")

### PYTHIA algorithm
pythia8gen = PythiaInterface("Pythia8Interface", Filename=pythiafile)
pythia8gen.DataOutputs.hepmc.Path = "HepmcEvent"

### Reads an HepMC::GenEvent from the data service and writes a collection of EDM Particles
hepmc_converter = HepMCConverter("Converter")
hepmc_converter.DataInputs.hepmc.Path="HepmcEvent"
hepmc_converter.DataOutputs.genparticles.Path="allGenParticles"
hepmc_converter.DataOutputs.genvertices.Path="allGenVertices"


graph_builder = BuildParticleGraph(OutputLevel=VERBOSE)
graph_builder.DataInputs.generatedParticles.Path = "allGenParticles"

graph_tool = ParticleGraphTool(OutputLevel=DEBUG)
checker = ParticleGraphTestConsumer("TestConsumer", graphTool=graph_tool, OutputLevel=DEBUG)

from Configurables import PodioOutput
### PODIO algorithm
out = PodioOutput("out",OutputLevel=DEBUG)
out.outputCommands = ["keep *"]
out.filename = "pythia_graph.root"

from Configurables import ApplicationMgr
ApplicationMgr( TopAlg=[ pythia8gen, hepmc_converter, graph_builder, checker, out ],
                EvtSel='NONE',
                EvtMax=10,
                ExtSvc=[podioevent],
                OutputLevel=INFO
)

