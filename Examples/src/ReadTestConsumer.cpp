#include "GaudiAlg/GaudiAlgorithm.h"
#include "GaudiKernel/ToolHandle.h"

#include "FWCore/DataHandle.h"

#include "Generation/IParticleGraph.h"

#include "datamodel/MCParticleCollection.h"
#include "datamodel/TrackHitCollection.h"
#include "datamodel/GenVertex.h"


class ReadTestConsumer : public GaudiAlgorithm {

public:
  ReadTestConsumer(const std::string& name, ISvcLocator* svcLoc) :
    GaudiAlgorithm(name, svcLoc)
  {
    declareInput("genParticles", m_genParticles, "allGenParticles");
    declareInput("hits", m_trkHits, "hits");
    declareProperty("graphTool", m_graphTool);
    declarePrivateTool(m_graphTool, "ReadTestConsumer/ParticleGraphTool");
  }

  ~ReadTestConsumer() {};

  StatusCode initialize() {
    if (m_graphTool.retrieve().isFailure()) {
      return StatusCode::FAILURE;
    }
    return GaudiAlgorithm::initialize();
  }

  StatusCode execute() {
    const fcc::MCParticleCollection* mcparticles = m_genParticles.get();
    const fcc::TrackHitCollection* trkhits = m_trkHits.get();
    info() << mcparticles << endmsg;

    info() << "MCParticle size: " << mcparticles->size() << endmsg;
    int cntr = 0;
    for (const auto& mcpart : *mcparticles) {
      if (10 < cntr++) {
        info() << "vertex x: " << mcpart.StartVertex().Position().X << endmsg;
        auto daughters = m_graphTool->childParticles(mcpart, 1);
        for (auto& daughter : daughters) {
          info() << daughter.getObjectID().index << " ";
        }
        info() << endmsg;
      }
    }
    info() << "hits size: " << trkhits->size() << endmsg;
    return StatusCode::SUCCESS;
  }

  StatusCode finalize() {
    return GaudiAlgorithm::finalize();
  }

private:
  DataHandle<fcc::MCParticleCollection> m_genParticles;
  DataHandle<fcc::TrackHitCollection> m_trkHits;
  ToolHandle<IParticleGraph> m_graphTool;
};
DECLARE_COMPONENT(ReadTestConsumer)
