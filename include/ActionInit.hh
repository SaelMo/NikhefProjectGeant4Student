#ifndef ACTION_INIT_HH
#define ACTION_INIT_HH

#include "G4VUserActionInitialization.hh"

namespace NikhefProject {

class PrimaryGenAction;
class RunAction;
class EventAction;
class SteppingAction;

class ActionInit : public G4VUserActionInitialization {
public:
  ActionInit() = default;
  virtual ~ActionInit() = default;

  virtual void Build() const override;
};

}

#endif
