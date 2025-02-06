#include "PrimaryGenAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

namespace docker_g4 {

PrimaryGenAction::PrimaryGenAction(){
  fParticleGun = new G4ParticleGun();

  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("proton"));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  fParticleGun->SetParticleEnergy(200 * MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -0.5 * m));
}

void PrimaryGenAction::GeneratePrimaries(G4Event* anEvent){
  G4cout << "Pew Pew!" << G4endl;
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

}