#include "G4VUserDetectorConstruction.hh"

namespace docker_g4 {

class DetConstruction : public G4VUserDetectorConstruction {
public:
  G4VPhysicalVolume* Construct();
};

}