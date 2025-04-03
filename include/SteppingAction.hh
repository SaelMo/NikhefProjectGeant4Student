#include "G4UserSteppingAction.hh"

namespace NikhefProject {

class SteppingAction : public G4UserSteppingAction {
public:
  void UserSteppingAction(const G4Step*) override;
};

}