
#ifndef GENERATION_PARTICLEGRAPHTOOL_H
#define GENERATION_PARTICLEGRAPHTOOL_H
// Gaudi
#include "GaudiAlg/GaudiTool.h"
// FWCore
#include "FWCore/DataHandle.h"
// The abstract interface
#include "Generation/IParticleGraph.h"

namespace fcc {
class MCParticleCollection;
class ParticleGraph;
}

class ParticleGraphTool: public GaudiTool, virtual public IParticleGraph {
public:
  ParticleGraphTool( const std::string& type, const std::string& name,
                     const IInterface* parent) ;
  virtual ~ParticleGraphTool();
  virtual StatusCode initialize();
  virtual StatusCode finalize();

  virtual const fcc::ParticleVector getAllChildParticles(const fcc::ConstMCParticle&) final;
  virtual const fcc::ParticleVector getAllParentParticles(const fcc::ConstMCParticle&) final;
  // virtual const fcc::ParticleVector getImmediateChildParticles(const fcc::ConstMCParticle&) final;
  // virtual const fcc::ParticleVector getImmediateParentParticles(const fcc::ConstMCParticle&) final;

  virtual const fcc::NodeVector& getAllChildNodes(const fcc::ConstMCParticle&) final;
  virtual const fcc::NodeVector& getAllParentNodes(const fcc::ConstMCParticle&) final;
  // virtual const fcc::NodeSet& getImmediateChildNodes(const fcc::ConstMCParticle&) final;
  // virtual const fcc::NodeSet& getImmediateParentNodes(const fcc::ConstMCParticle&) final;

  virtual const fcc::IdNode& getNode(const fcc::ConstMCParticle&) final;
  virtual fcc::ConstMCParticle getParticle(const fcc::IdNode&) final;

private:
  fcc::ParticleVector translate(const fcc::NodeVector& nodes);
  // fcc::ParticleVector translate(const fcc::NodeSet& nodes);
  DataHandle<fcc::MCParticleCollection> m_particleCollHandle;
  DataHandle<fcc::ParticleGraph> m_graphHandle;
  DAG::BFSVisitor<fcc::IdNode> m_visitor;
};

#endif // GENERATION_PARTICLEGRAPHTOOL_H
