#ifndef GENERATION_BUILDPARTICLEGRAPH_H
#define GENERATION_BUILDPARTICLEGRAPH_H

// Gaudi
#include "GaudiAlg/GaudiAlgorithm.h"
// FWCore
#include "FWCore/DataHandle.h"

// forward declarations:
// FCC-EDM
namespace fcc {
class ParticleGraph;
class MCParticleCollection;
}

/** @class BuildParticleGraph Generation/Generation/BuildParticleGraph.h BuildParticleGraph.h
 *
 *  Algorithm that creates an acyclic directed graph for easy traversal of MCParticles and puts it in the TES
 *
 *  @author J. Lingemann
 *  @date 19.07.2016
 */

class BuildParticleGraph : public GaudiAlgorithm {
public:
  friend class AlgFactory<BuildParticleGraph>;
  /// Default constructor
  BuildParticleGraph(const std::string& name, ISvcLocator* pSvcLocator);

  /// Destructor
  virtual ~BuildParticleGraph() = default;

  virtual StatusCode initialize();
  virtual StatusCode finalize();
  virtual StatusCode execute();

private:
  DataHandle<fcc::MCParticleCollection> m_inputParticles;
  DataHandle<fcc::ParticleGraph> m_graph;

};

#endif /* define GENERATION_BUILDPARTICLEGRAPH_H */
