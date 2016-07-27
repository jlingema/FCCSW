#include "GenParticleFilter.h"

#include "datamodel/LorentzVector.h"
#include "datamodel/GenVertex.h"

DECLARE_COMPONENT(GenParticleFilter)

GenParticleFilter::GenParticleFilter(const std::string& name, ISvcLocator* svcLoc):
  GaudiAlgorithm(name, svcLoc)
{
  declareInput("genparticles", m_igenphandle);
  declareOutput("genparticles", m_ogenphandle);
}

StatusCode GenParticleFilter::initialize() {
  return GaudiAlgorithm::initialize();
}

StatusCode GenParticleFilter::execute() {
  auto inparticles = m_igenphandle.get();
  fcc::MCParticleCollection* particles = new fcc::MCParticleCollection();
  for(const auto& ptc : (*inparticles)) {
    if(ptc.Core().Status == 1) {
      particles->push_back(ptc.clone());
    }
  }
  m_ogenphandle.put(particles);
  return StatusCode::SUCCESS;
}

StatusCode GenParticleFilter::finalize() {
  return GaudiAlgorithm::finalize();
}
