#include "BuildParticleGraph.h"

// fcc-edm
#include "utilities/ParticleGraph.h"
// datamodel
#include "datamodel/MCParticleCollection.h"

DECLARE_COMPONENT(BuildParticleGraph)

BuildParticleGraph::BuildParticleGraph(const std::string& name, ISvcLocator* pSvcLocator) :
    GaudiAlgorithm(name, pSvcLocator) {
  declareInput("generatedParticles", m_inputParticles);
  declareOutput("particleGraph", m_graph, "ParticleGraph");
}

StatusCode BuildParticleGraph::initialize() {
  return GaudiAlgorithm::initialize();
}

StatusCode BuildParticleGraph::finalize() {
  return GaudiAlgorithm::finalize();
}

StatusCode BuildParticleGraph::execute() {
  auto particles = m_inputParticles.get();
  if (nullptr == particles) {
    error() << "Unable to locate the input MCParticleCollection" << endmsg;
    return StatusCode::FAILURE;
  }
  auto graph = m_graph.createAndPut();
  graph->build(*particles);
  return StatusCode::SUCCESS;
}

