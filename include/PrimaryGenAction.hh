#ifndef PRIMARY_GEN_ACTION_HH
#define PRIMARY_GEN_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"

namespace NikhefProject {

class PrimaryGenAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGenAction();
  virtual ~PrimaryGenAction() override = default;

  virtual void GeneratePrimaries(G4Event* anEvent) override;

private:
  G4GeneralParticleSource* fParticleGun;
};

}

#endif
