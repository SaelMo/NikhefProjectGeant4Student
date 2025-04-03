#include "ActionInit.hh"
#include "PrimaryGenAction.hh"
#include "SteppingAction.hh"

namespace NikhefProject {
void ActionInit::Build() const {
  SetUserAction(new PrimaryGenAction());
  SetUserAction(new SteppingAction());
  }
}