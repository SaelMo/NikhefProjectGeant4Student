#include "DetConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhysics.hh"

namespace NikhefProject {

G4VPhysicalVolume* DetConstruction::Construct() {
    // Add a background material
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * m, 0.5 * m, 0.5 * m);
    G4Material *air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");

    G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld,
        "physWorld", nullptr, false, 0);

    // Add a NaI solid
    G4double outerRadius = 5.0 * cm;
    G4double height = 15.0 * cm;
    G4Material *nai = G4NistManager::Instance()->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    // Define scintillation properties for NaI(Tl)
    G4double energy[] = {2.00 * eV, 3.47 * eV}; // Example energy range
    const G4int nEntries = sizeof(energy) / sizeof(G4double);

    G4double scintillationYield = 38. / keV; // Scintillation yield
    G4double scintillationSpectrum[] = {1.0, 1.0}; // Example spectrum

    G4double refractiveIndex[] = {1.85, 1.85}; // Refractive index of NaI(Tl)
    G4double absorptionLength[] = {1.0 * m, 1.0 * m}; // Absorption length

    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintillationSpectrum, nEntries);
    MPT->AddConstProperty("SCINTILLATIONYIELD", scintillationYield);
    MPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
    MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 230. * ns); // Decay time constant
    MPT->AddProperty("RINDEX", energy, refractiveIndex, nEntries);
    MPT->AddProperty("ABSLENGTH", energy, absorptionLength, nEntries);

    nai->SetMaterialPropertiesTable(MPT);

    G4Tubs *solidDetector = new G4Tubs("solidDetector", 0.0 * cm, outerRadius, height / 2, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, nai, "logicDetector");

    // Center NaI in the world
    new G4PVPlacement(nullptr, G4ThreeVector(), logicDetector, "physDetector", logicWorld, false, 0);

    return physWorld;
}

}