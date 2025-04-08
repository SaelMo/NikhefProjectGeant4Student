#include "DetConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

namespace NikhefProject {

G4LogicalVolume* DetConstruction::fNaILogicalVolume = nullptr;

DetConstruction::DetConstruction() {}
DetConstruction::~DetConstruction() {}

G4VPhysicalVolume* DetConstruction::Construct() {
    // The world is a cube
    G4double worldSize = 2.0 * m;
    G4Box* solidWorld = new G4Box("solidWorld", worldSize / 2, worldSize / 2, worldSize / 2);
    G4Material* defmat = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"); //G4_Galactic

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, defmat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "physWorld", nullptr, false, 0);

    auto worldVis = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    logicWorld->SetVisAttributes(worldVis);

    // Added a ground plane for the sake of visualization
    G4Box* solidGround = new G4Box("solidGround", worldSize / 2, worldSize / 2, 0.01 * m);
    G4LogicalVolume* logicGround = new G4LogicalVolume(solidGround, defmat, "logicGround");  // Kept it simple and made it the same material as the background
    new G4PVPlacement(nullptr, G4ThreeVector(0.0 * m, 0.0 * m, -worldSize / 2 + 0.01 * m), logicGround, "physGround", logicWorld, false, 0);

    auto groundVis = new G4VisAttributes(G4Colour(0.6, 0.3, 0.1, 1.0));
    groundVis->SetForceSolid(true);
    logicGround->SetVisAttributes(groundVis);

    // Our good crystal!
    G4Tubs* solidNaI = new G4Tubs("NaI", 0.0, 10.0 * cm, 20.0 * cm, 0, 360 * deg);
    G4Material* NaI = G4NistManager::Instance()->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4LogicalVolume* logicNaI = new G4LogicalVolume(solidNaI, NaI, "logicNaI");
    fNaILogicalVolume = logicNaI;

    new G4PVPlacement(nullptr, G4ThreeVector(50.0 * cm, 0.0 * m, 0.0 * m), logicNaI, "NaIDetector", logicWorld, false, 0);

    auto NaIVis = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    NaIVis->SetForceSolid(true);
    logicNaI->SetVisAttributes(NaIVis);

    G4Box* solidBox = new G4Box("ParticleSpawnBox", 5.0 * cm, 5.0 * cm, 5.0 * cm);
    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, defmat, "logicBox");  // Kept it simple and made it the same material as the background
    new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.0), logicBox, "ParticleSpawnBox", logicWorld, false, 0);

    auto boxVis = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    boxVis->SetForceWireframe(true);
    logicBox->SetVisAttributes(boxVis);

    return physWorld;
}

G4LogicalVolume* DetConstruction::GetNaILogicalVolume() {
    return fNaILogicalVolume;
}

}