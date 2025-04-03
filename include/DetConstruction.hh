#include "G4VUserDetectorConstruction.hh"

namespace NikhefProject {

class DetConstruction : public G4VUserDetectorConstruction {
public:
  G4VPhysicalVolume* Construct();
};

}