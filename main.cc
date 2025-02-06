// Entrypoint for docker-g4-app

#include "G4ios.hh"
#include "G4RunManagerFactory.hh"
#include "QGSP_BERT.hh"
#include "G4UImanager.hh"

#include "ActionInit.hh"
#include "DetConstruction.hh"

using namespace docker_g4;

int main(){

  // run manager
  auto runManager = G4RunManagerFactory::CreateRunManager();

  G4cout << "Hello from the Geant4 world!" << G4endl;

  // physics list
  runManager->SetUserInitialization(new QGSP_BERT());

  // detector construction
  runManager->SetUserInitialization(new DetConstruction());

  // action initialization w/ primary gen action & stepping action
  runManager->SetUserInitialization(new ActionInit());

  // initialize G4 kernel
  runManager->Initialize();

  // run a couple of particles
  int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);

  // job termination
  delete runManager;

  return 0;
}