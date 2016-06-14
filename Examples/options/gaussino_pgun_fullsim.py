from Gaudi.Configuration import *

from Configurables import FCCDataSvc
podioevent = FCCDataSvc("EventDataSvc")
from Configurables import GeoSvc
geoservice = GeoSvc("GeoSvc", detectors=['file:Detector/DetFCChhTrackerSimple/compact/FCChh_TrackerStandalone.xml'],
                    OutputLevel = DEBUG)

from Gaussino import Gaussino
from Configurables import G4SaveTrackerHits
gaussino = Gaussino(geoservice, podioevent)
# gaussino.init_full_sim()
gaussino.add_sim_output(G4SaveTrackerHits,
                        "SaveTrackHits",
                        trackClusters="clusters",
                        trackHits="hits",
                        trackHitsClusters="hitClusterAssociation")

from Configurables import G4PrimariesFromEdmTool
particle_converter = G4PrimariesFromEdmTool("EdmConverter")
particle_converter.DataInputs.genParticles.Path = "allGenParticles"
gaussino._sim.algo.eventGenerator = particle_converter

from Configurables import PodioOutput
out = PodioOutput("out",
                   OutputLevel=DEBUG)
out.outputCommands = ["keep *"]

ApplicationMgr(
    TopAlg=gaussino.algo_sequence()+[out],
    EvtSel='NONE',
    EvtMax=1,
    ExtSvc=gaussino.svc_sequence(),
    OutputLevel=INFO)

