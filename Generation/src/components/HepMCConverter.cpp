#include "HepMCConverter.h"

#include "GaudiKernel/PhysicalConstants.h"

#include "datamodel/MCParticleCollection.h"
#include "datamodel/GenVertexCollection.h"

#include "Generation/Units.h"

DECLARE_COMPONENT(HepMCConverter)

HepMCConverter::HepMCConverter(const std::string& name, ISvcLocator* svcLoc):
GaudiAlgorithm(name, svcLoc) {
  declareInput("hepmc", m_hepmchandle);
  declareOutput("genparticles", m_genphandle);
  declareOutput("genvertices", m_genvhandle);
  }

StatusCode HepMCConverter::initialize() {
  return GaudiAlgorithm::initialize();
}

StatusCode HepMCConverter::execute() {
  const HepMC::GenEvent* event = m_hepmchandle.get();
  fcc::MCParticleCollection* particles = new fcc::MCParticleCollection();
  fcc::GenVertexCollection* vertices = new fcc::GenVertexCollection();

  // conversion of units to EDM standard units:
  // First cover the case that hepMC file is not in expected units and then convert to EDM default
  double hepmc2EdmLength = HepMC::Units::conversion_factor(event->length_unit(),
                                                           gen::hepmcdefault::length) * gen::hepmc2edm::length;
  double hepmc2EdmEnergy = HepMC::Units::conversion_factor(event->momentum_unit(),
                                                           gen::hepmcdefault::energy) * gen::hepmc2edm::energy;

  // currently only final state particles converted (no EndVertex as they didn't decay)
  // TODO add translation of decayed particles
  HepMC::FourVector tmp;
  std::unordered_map<HepMC::GenVertex*, unsigned> vertexMap;
  for(auto vertex_i = event->vertices_begin();
      vertex_i != event->vertices_end(); ++vertex_i ) {
    tmp = (*vertex_i)->position();
    auto vertex = vertices->create();
    auto& position = vertex.position();
    position.x = tmp.x()*hepmc2EdmLength;
    position.y = tmp.y()*hepmc2EdmLength;
    position.z = tmp.z()*hepmc2EdmLength;
    vertex.ctau(tmp.t()*Gaudi::Units::c_light*hepmc2EdmLength); // is ctau like this?
    vertexMap[*vertex_i] = vertex.getObjectID().index;
  }
  for (auto particle_i = event->particles_begin();
       particle_i != event->particles_end(); ++particle_i) {
    tmp = (*particle_i)->momentum();
    fcc::MCParticle particle = particles->create();
    fcc::BareParticle& core = particle.core();
    core.pdgId = (*particle_i)->pdg_id();
    core.status = (*particle_i)->status();
    core.p4.px = tmp.px()*hepmc2EdmEnergy;
    core.p4.py = tmp.py()*hepmc2EdmEnergy;
    core.p4.pz = tmp.pz()*hepmc2EdmEnergy;
    core.p4.mass = (*particle_i)->generated_mass()*hepmc2EdmEnergy;

    auto prodVtxIdx = vertexMap.find((*particle_i)->production_vertex());
    if (prodVtxIdx != end(vertexMap)) {
      particle.startVertex(vertices->at(prodVtxIdx->second));
    }
    auto endVtxIdx = vertexMap.find((*particle_i)->end_vertex());
    if (endVtxIdx != end(vertexMap)) {
      particle.endVertex(vertices->at(endVtxIdx->second));
    }
  }
  m_genphandle.put(particles);
  m_genvhandle.put(vertices);
  return StatusCode::SUCCESS;
}

StatusCode HepMCConverter::finalize() {
  return GaudiAlgorithm::finalize();
}

