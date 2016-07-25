#include "GaudiAlg/GaudiAlgorithm.h"
#include "GaudiKernel/ToolHandle.h"

#include "FWCore/DataHandle.h"

#include "Generation/IParticleGraph.h"

#include "datamodel/MCParticleCollection.h"
#include "datamodel/TrackHitCollection.h"
#include "datamodel/GenVertex.h"


class ParticleGraphTestConsumer : public GaudiAlgorithm {

public:
  ParticleGraphTestConsumer(const std::string& name, ISvcLocator* svcLoc) :
    GaudiAlgorithm(name, svcLoc)
  {
    declareInput("genParticles", m_genParticles, "allGenParticles");
    declareProperty("graphTool", m_graphTool);
    declarePrivateTool(m_graphTool, "ParticleGraphTestConsumer/ParticleGraphTool");
  }

  ~ParticleGraphTestConsumer() {};

  StatusCode initialize() {
    if (m_graphTool.retrieve().isFailure()) {
      return StatusCode::FAILURE;
    }
    return GaudiAlgorithm::initialize();
  }

  StatusCode execute() {
    const fcc::MCParticleCollection* mcparticles = m_genParticles.get();

    for (const auto& mcpart : *mcparticles) {
      auto daughters = m_graphTool->childParticles(mcpart, -1);
      for (auto& daughter : daughters) {
        debug() << daughter.getObjectID().index << ", ";
      }
      debug() << endmsg;
    }
    return StatusCode::SUCCESS;
  }

  StatusCode finalize() {
    return GaudiAlgorithm::finalize();
  }

private:
  DataHandle<fcc::MCParticleCollection> m_genParticles;
  ToolHandle<IParticleGraph> m_graphTool;
};
DECLARE_COMPONENT(ParticleGraphTestConsumer)
