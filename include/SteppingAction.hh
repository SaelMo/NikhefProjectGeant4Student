#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"

namespace NikhefProject {

class SteppingAction : public G4UserSteppingAction {
public:
  SteppingAction();
  virtual ~SteppingAction() override;

  virtual void UserSteppingAction(const G4Step*) override;

private:
  static G4double totalEnergyInNaI;
};

}

#endif
