#include "PrimaryGenAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"

namespace NikhefProject {

PrimaryGenAction::PrimaryGenAction() {
  G4double particleEnergy = 2000 * keV;
  G4ThreeVector particlePosition(0.0 * m, 0.0 * m, 0.0 * m);
  G4ThreeVector particleDirection(1.0, 0.0, 0.0);
  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  fParticleGun = new G4GeneralParticleSource();
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(particleEnergy);
  fParticleGun->SetParticlePosition(particlePosition);
  fParticleGun->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(particleDirection);
}

void PrimaryGenAction::GeneratePrimaries(G4Event* anEvent) {
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

}