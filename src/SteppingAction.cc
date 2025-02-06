#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4ios.hh"

namespace docker_g4 {

void SteppingAction::UserSteppingAction(const G4Step *aStep){
  if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "physDetector"){
    G4cout << "Hit detector!" << G4endl;
  }
}

}