#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4TouchableHistory.hh"
#include "DetConstruction.hh"

namespace NikhefProject {

G4double SteppingAction::totalEnergyInNaI = 0.0;

SteppingAction::SteppingAction() {}
SteppingAction::~SteppingAction() {
    G4cout << "Total energy deposited in NaI: " << totalEnergyInNaI / keV << " keV" << G4endl;
}

void SteppingAction::UserSteppingAction(const G4Step* aStep) {
    static bool headerPrinted = false;
    if (!headerPrinted) {
        G4cout << "KineticEnergy(keV), Position(mm), Time(ns), Particle, Process, TrackID, ParentID, EnergyDeposit(keV), Material" << G4endl;
        headerPrinted = true;
    }

    G4double kineticEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
    G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
    G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
    G4String particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
    const G4VProcess* process = aStep->GetPostStepPoint()->GetProcessDefinedStep();
    G4String processName = process ? process->GetProcessName() : "Unknown";
    G4int trackID = aStep->GetTrack()->GetTrackID();
    G4int parentID = aStep->GetTrack()->GetParentID();
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();
    
    auto* touchable = (G4TouchableHistory*) aStep->GetPostStepPoint()->GetTouchable();
    G4LogicalVolume* currentVolume = touchable->GetVolume()->GetLogicalVolume();
    G4LogicalVolume* NaI_logic = DetConstruction::GetNaILogicalVolume();

    if (currentVolume == NaI_logic) {
        totalEnergyInNaI += energyDeposit;
    }

    // Get the material the particle is interacting with
    G4Material* material = currentVolume->GetMaterial();
    G4String materialName = material ? material->GetName() : "Unknown";

    G4cout << kineticEnergy / keV << ", " << position << ", " << time / ns << ", " << particleName << ", "
           << processName << ", " << trackID << ", " << parentID << ", " << energyDeposit / keV << ", " 
           << materialName << G4endl;
}

}
