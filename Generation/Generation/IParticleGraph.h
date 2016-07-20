#ifndef GENERATION_IPARTICLEGRAPH_H
#define GENERATION_IPARTICLEGRAPH_H

#include "GaudiKernel/IAlgTool.h"
#include "GaudiKernel/Vector4DTypes.h"

#include "utilities/ParticleGraph.h"

/** @class IParticleGraph IParticleGraph.h "Generation/IParticleGraph.h"
 *
 *  Interface to a tool that retrieves a ParticleGraph from TES and offers functionality to access traverse the graph
 *
 *  @author J. Lingemann
 *  @date   2008-05-18
 */

namespace fcc {
class ConstMCParticle;
}

// typedefs:
namespace fcc {
typedef std::vector<ConstMCParticle> ParticleVector;
typedef std::vector<const IdNode*> NodeVector;
// typedef std::set<const IdNode*> NodeSet;
}

class IParticleGraph : virtual public IAlgTool {
 public:
  DeclareInterfaceID(IParticleGraph, 1, 0);

  virtual const fcc::ParticleVector getAllChildParticles(const fcc::ConstMCParticle&) = 0;
  virtual const fcc::ParticleVector getAllParentParticles(const fcc::ConstMCParticle&) = 0;
  // virtual const fcc::ParticleVector getImmediateChildParticles(const fcc::ConstMCParticle&) = 0;
  // virtual const fcc::ParticleVector getImmediateParentParticles(const fcc::ConstMCParticle&) = 0;

  virtual const fcc::NodeVector& getAllChildNodes(const fcc::ConstMCParticle&) = 0;
  virtual const fcc::NodeVector& getAllParentNodes(const fcc::ConstMCParticle&) = 0;
  // virtual const fcc::NodeSet& getImmediateChildNodes(const fcc::ConstMCParticle&) = 0;
  // virtual const fcc::NodeSet& getImmediateParentNodes(const fcc::ConstMCParticle&) = 0;

  virtual const fcc::IdNode& getNode(const fcc::ConstMCParticle&) = 0;
  virtual fcc::ConstMCParticle getParticle(const fcc::IdNode&) = 0;
};

#endif
