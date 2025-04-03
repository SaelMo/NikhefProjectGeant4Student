#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

namespace NikhefProject {

void SteppingAction::UserSteppingAction(const G4Step *aStep) {
    static bool headerPrinted = false;

    // Print header only once
    if (!headerPrinted) {
        G4cout << "KineticEnergy(keV), Position(mm), Time(ns), Particle, Process, TrackID, ParentID, EnergyDeposit(keV)" << G4endl;
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

    // Skip steps with no defined process or energy deposit less than or equal to 1 keV
    if (processName == "NoProcess" || energyDeposit <= 2 * eV) {
        return;
    }

    G4cout << kineticEnergy / keV << ", " << position << ", " << time / ns << ", " << particleName << ", " << processName << ", " << trackID << ", " << parentID << ", " << energyDeposit / keV << G4endl;
}

}