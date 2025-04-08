#include "ActionInit.hh"
#include "PrimaryGenAction.hh"
#include "SteppingAction.hh"

namespace NikhefProject {

void ActionInit::Build() const {
  // Set up the primary particle generator
  SetUserAction(new PrimaryGenAction());

  // Set up the stepping action
  SetUserAction(new SteppingAction());
}

}
