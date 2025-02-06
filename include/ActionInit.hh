#pragma once

#include "G4VUserActionInitialization.hh"

namespace docker_g4 {

class ActionInit : public G4VUserActionInitialization {
public:
  void Build() const override;
  };
}