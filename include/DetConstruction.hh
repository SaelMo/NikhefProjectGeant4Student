#ifndef DET_CONSTRUCTION_HH
#define DET_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

namespace NikhefProject {

class DetConstruction : public G4VUserDetectorConstruction {
public:
  DetConstruction();
  virtual ~DetConstruction() override;

  virtual G4VPhysicalVolume* Construct() override;

  static G4LogicalVolume* GetNaILogicalVolume();

private:
  static G4LogicalVolume* fNaILogicalVolume;
};

}

#endif
