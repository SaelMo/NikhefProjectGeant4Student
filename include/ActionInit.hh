#pragma once

#include "G4VUserActionInitialization.hh"

namespace NikhefProject {

class ActionInit : public G4VUserActionInitialization {
public:
  void Build() const override;
  };
}