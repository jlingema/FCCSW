#include "SimG4Com/ParticleInformationEdm.h"

namespace sim {
ParticleInformationEdm::ParticleInformationEdm(const fcc::MCParticle& aMCpart):
  ParticleInformation(-1), m_mcParticle(aMCpart) {}

ParticleInformationEdm::~ParticleInformationEdm() {}

const fcc::MCParticle& ParticleInformationEdm::mcParticle() const {
  return m_mcParticle;
}
}
