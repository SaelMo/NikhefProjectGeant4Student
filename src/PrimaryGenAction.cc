#include "PrimaryGenAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh" // Include for random number generation

namespace NikhefProject {

PrimaryGenAction::PrimaryGenAction(){
  G4double particleEnergy = 2000 * keV;
  G4ThreeVector particlePosition = G4ThreeVector(0.1 * m, 0.1 * m, 0.1 * m);

  fParticleGun = new G4GeneralParticleSource();
  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma")); 

  auto energyDist = fParticleGun->GetCurrentSource()->GetEneDist();
  energyDist->SetMonoEnergy(particleEnergy);

  fParticleGun->SetParticlePosition(particlePosition);
}

void PrimaryGenAction::GeneratePrimaries(G4Event* anEvent){
  G4double theta = CLHEP::pi * G4UniformRand(); // Random angle theta
  G4double phi = 2 * CLHEP::pi * G4UniformRand(); // Random angle phi

  G4ThreeVector randomDirection(std::sin(theta) * std::cos(phi),
                                std::sin(theta) * std::sin(phi),
                                std::cos(theta));

  auto angDist = fParticleGun->GetCurrentSource()->GetAngDist();
  angDist->SetParticleMomentumDirection(randomDirection);

  G4cout << "PRIMARY SHOT: Direction: " << randomDirection << G4endl;
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

}