#include "DetConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

namespace docker_g4 {

G4VPhysicalVolume* DetConstruction::Construct(){
  // solid, then logic, then phys
  G4Box *solidWorld = new G4Box("solidWorld", 1 * m, 1 * m, 1 * m);

  G4Material *vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume *logicWorld = new G4LogicalVolume(
    solidWorld,
    vacuum,
    "logicWorld");

  G4VPhysicalVolume *physWorld = new G4PVPlacement(
    nullptr,              // rotation
    G4ThreeVector(),      // position
    logicWorld,           // logical volume
    "physWorld",          // name
    nullptr,              // mother
    false,                // many?
    0                     // copy number
  );


  // add a water detector
  G4Material *water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");

  G4Box *solidDetector = new G4Box("solidDetector", 10 * cm, 10 * cm, 1 * cm);

  G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, water, "logicDetector");

  new G4PVPlacement(
    nullptr,
    G4ThreeVector(),
    logicDetector,
    "physDetector",
    logicWorld,
    false,
    0
  );

  return physWorld;
}

}