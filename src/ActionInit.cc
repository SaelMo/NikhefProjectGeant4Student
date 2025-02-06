#include "ActionInit.hh"
#include "PrimaryGenAction.hh"
#include "SteppingAction.hh"

namespace docker_g4 {
void ActionInit::Build() const {
  SetUserAction(new PrimaryGenAction());
  SetUserAction(new SteppingAction());
  }
}