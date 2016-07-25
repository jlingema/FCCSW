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
 *  @date   2016-07-19
 */

namespace fcc {
class ConstMCParticle;
}

// typedefs:
namespace fcc {
typedef std::vector<ConstMCParticle> ParticleVector;
typedef std::vector<const IdNode*> NodeVector;
}

class IParticleGraph : virtual public IAlgTool {
 public:
  DeclareInterfaceID(IParticleGraph, 1, 0);

  /** Get children of a MC particle
   * @param[in] the MC particle
   * @param[in] number of generations (-1 for all children)
   */
  virtual const fcc::ParticleVector childParticles(const fcc::ConstMCParticle&, int numGenerations = -1) = 0;
  /** Get parents of a MC particle
   * @param[in] the MC particle
   * @param[in] number of generations (-1 for all parents)
   */
  virtual const fcc::ParticleVector parentParticles(const fcc::ConstMCParticle&, int numGenerations = -1) = 0;
  /** Get child nodes of the node corresponding to a MC particle
   * @param[in] the MC particle
   * @param[in] number of generations (-1 for all children)
   */
  virtual const fcc::NodeVector& childNodes(const fcc::ConstMCParticle&, int numGenerations = -1) = 0;
  /** Get parent nodes of the node corresponding to a MC particle
   * @param[in] the MC particle
   * @param[in] number of generations (-1 for all parents)
   */
  virtual const fcc::NodeVector& parentNodes(const fcc::ConstMCParticle&, int numGenerations = -1) = 0;
  /// Get the node corrsponding to a MC particle
  virtual const fcc::IdNode& node(const fcc::ConstMCParticle&) = 0;
  /// Get the particle corresponding to a node
  virtual fcc::ConstMCParticle particle(const fcc::IdNode&) = 0;
};

#endif
