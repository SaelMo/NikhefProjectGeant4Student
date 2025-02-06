#include "G4UserSteppingAction.hh"

namespace docker_g4 {

class SteppingAction : public G4UserSteppingAction {
public:
  void UserSteppingAction(const G4Step*) override;
};

}