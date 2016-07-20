#include "ParticleGraphTool.h"

// fcc-edm
#include "utilities/GraphBuilder.h"
// datamodel
#include "datamodel/MCParticleCollection.h"
#include "datamodel/MCParticle.h"

DECLARE_COMPONENT(ParticleGraphTool)

ParticleGraphTool::ParticleGraphTool( const std::string& type, const std::string& name,
                                      const IInterface* parent) :
    GaudiTool(type, name, parent) {
  declareInput("generatedParticles", m_particleCollHandle, "allGenParticles");
  declareInput("particleGraph", m_graphHandle, "ParticleGraph");
}

ParticleGraphTool::~ParticleGraphTool() {

}

StatusCode ParticleGraphTool::initialize() {
  return GaudiTool::initialize();
}

StatusCode ParticleGraphTool::finalize() {
  return GaudiTool::finalize();
}

const fcc::ParticleVector ParticleGraphTool::getAllChildParticles(const fcc::ConstMCParticle& particle) {
  return translate(getAllChildNodes(particle));
}

const fcc::ParticleVector ParticleGraphTool::getAllParentParticles(const fcc::ConstMCParticle& particle) {
  return translate(getAllParentNodes(particle));
}

// const fcc::ParticleVector ParticleGraphTool::getImmediateChildParticles(const fcc::ConstMCParticle& particle) {
//   return translate(getImmediateChildNodes(particle));
// }

// const fcc::ParticleVector ParticleGraphTool::getImmediateParentParticles(const fcc::ConstMCParticle& particle) {
//   return translate(getImmediateParentNodes(particle));
// }


const fcc::NodeVector& ParticleGraphTool::getAllChildNodes(const fcc::ConstMCParticle& particle) {
  auto graph = m_graphHandle.get();
  const auto& node = graph->getNode(particle);
  return m_visitor.traverseChildren(node);
}

const fcc::NodeVector& ParticleGraphTool::getAllParentNodes(const fcc::ConstMCParticle& particle) {
  auto graph = m_graphHandle.get();
  const auto& node = graph->getNode(particle);
  return m_visitor.traverseParents(node);
}

// const fcc::NodeSet& ParticleGraphTool::getImmediateChildNodes(const fcc::ConstMCParticle& particle) {
//   auto graph = m_graphHandle.get();
//   const auto& node = graph->getNode(particle);
//   return node.children();
// }

// const fcc::NodeSet& ParticleGraphTool::getImmediateParentNodes(const fcc::ConstMCParticle& particle) {
//   auto graph = m_graphHandle.get();
//   const auto& node = graph->getNode(particle);
//   return node.parents();
// }

fcc::ParticleVector ParticleGraphTool::translate(const fcc::NodeVector& nodes) {
  auto particles = m_particleCollHandle.get();
  fcc::ParticleVector result;
  for (auto n : nodes) {
    result.push_back(particles->at(n->value().index));
  }
  return result;
}

// fcc::ParticleVector ParticleGraphTool::translate(const fcc::NodeSet& nodes) {
//   auto particles = m_particleCollHandle.get();
//   fcc::ParticleVector result;
//   for (auto n : node.parents()) {
//     result.push_back(m_particles->at(n.value().index));
//   }
//   return result;
// }

const fcc::IdNode& ParticleGraphTool::getNode(const fcc::ConstMCParticle& particle) {
  auto graph = m_graphHandle.get();
  return graph->getNode(particle);
}

fcc::ConstMCParticle ParticleGraphTool::getParticle(const fcc::IdNode& node) {
  auto particles = m_particleCollHandle.get();
  return particles->at(node.value().index);
}

