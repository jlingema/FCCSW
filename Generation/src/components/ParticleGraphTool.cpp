#include "ParticleGraphTool.h"

// fcc-edm
#include "utilities/ParticleGraph.h"
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

const fcc::ParticleVector ParticleGraphTool::childParticles(const fcc::ConstMCParticle& particle, int numGenerations) {
  return translate(childNodes(particle, numGenerations));
}

const fcc::ParticleVector ParticleGraphTool::parentParticles(const fcc::ConstMCParticle& particle, int numGenerations) {
  return translate(parentNodes(particle, numGenerations));
}

const fcc::NodeVector& ParticleGraphTool::childNodes(const fcc::ConstMCParticle& particle, int numGenerations) {
  auto graph = m_graphHandle.get();
  const auto& node = graph->getNode(particle);
  return m_visitor.traverseChildren(node, numGenerations);
}

const fcc::NodeVector& ParticleGraphTool::parentNodes(const fcc::ConstMCParticle& particle, int numGenerations) {
  auto graph = m_graphHandle.get();
  const auto& node = graph->getNode(particle);
  return m_visitor.traverseParents(node, numGenerations);
}

fcc::ParticleVector ParticleGraphTool::translate(const fcc::NodeVector& nodes) {
  auto particles = m_particleCollHandle.get();
  fcc::ParticleVector result;
  for (auto n : nodes) {
    result.push_back(particles->at(n->value().index));
  }
  return result;
}

const fcc::IdNode& ParticleGraphTool::node(const fcc::ConstMCParticle& particle) {
  auto graph = m_graphHandle.get();
  return graph->getNode(particle);
}

fcc::ConstMCParticle ParticleGraphTool::particle(const fcc::IdNode& node) {
  auto particles = m_particleCollHandle.get();
  return particles->at(node.value().index);
}

