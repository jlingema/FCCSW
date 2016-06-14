#ifndef SIMG4COMMON_PARTICLEINFORMATIONEDM_H
#define SIMG4COMMON_PARTICLEINFORMATIONEDM_H

// datamodel
#include "datamodel/MCParticle.h"
#include "datamodel/Particle.h"

// Gaussino
#include "SimG4Common/ParticleInformation.h"

// CLHEP
#include "CLHEP/Vector/ThreeVector.h"

/** @class FastSimParticleInformation SimG4Common/SimG4Common/FastSimParticleInformation.h FastSimParticleInformation.h
 *
 *  Describes the information that can be assosiated with a G4PrimaryParticle class object.
 *  It contains handles to the EDM Monte Carlo object.
 *  It is used for the fast simulation in Geant to associate MC particle with a 'reconstructed' particle.
 *  MCParticle information is filled when EDM event is translated to G4Event.
 *  Momentum, status and vertex info is filled at the end of Geant's track processing
 *  (SaveParticlesTrackingAction::PostUserTrackingAction).
 *
 *  @author Anna Zaborowska
 */

namespace sim {
class ParticleInformationEdm: public ParticleInformation {
public:
  /** A constructor.
   *  @param[in] aMCpart EDM MCParticle.
   */
  explicit ParticleInformationEdm(const fcc::MCParticle& aMCpart);
  /// A destructor
  virtual ~ParticleInformationEdm();
  /** Getter of the MCParticle.
   *  @returns EDM MCParticle.
   */
  const fcc::MCParticle& mcParticle() const;

private:
  /// EDM MC particle
  const fcc::MCParticle m_mcParticle;
};
}

#endif /* SIMG4COMMON_PARTICLEINFORMATIONEDM_H */
