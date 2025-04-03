#include "G4ios.hh"
#include "G4RunManager.hh"
#include "QGSP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4UImanager.hh"

#include "ActionInit.hh"
#include "DetConstruction.hh"

using namespace NikhefProject;

int main(){
  int numberPrimaries = 100;

  auto runManager = new G4RunManager();
  G4cout << "Start Geant4 simulation" << G4endl;

  runManager->SetUserInitialization(new QGSP_BERT());
  
  // Add optical physics
  G4VModularPhysicsList* physicsList = new QGSP_BERT();
  physicsList->RegisterPhysics(new G4OpticalPhysics());
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new DetConstruction());
  runManager->SetUserInitialization(new ActionInit());
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");

  runManager->Initialize();
  runManager->BeamOn(numberPrimaries);

  delete runManager;
  G4cout << "End Geant4 simulation" << G4endl;
}