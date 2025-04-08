#include "G4ios.hh"
#include "G4RunManager.hh"
#include "QGSP_BERT.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "ActionInit.hh"
#include "DetConstruction.hh"

using namespace NikhefProject;

int main(int argc, char** argv) {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    auto runManager = new G4RunManager();
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserInitialization(new DetConstruction());
    runManager->SetUserInitialization(new ActionInit());
    runManager->Initialize();

    UI->ApplyCommand("/tracking/storeTrajectory 1");
    UI->ApplyCommand("/run/verbose 0");
    UI->ApplyCommand("/event/verbose 0");
    UI->ApplyCommand("/tracking/verbose 0");
    UI->ApplyCommand("/process/verbose 0");
    UI->ApplyCommand("/step/verbose 0");

    // If no argument is given, use TSG_QT_GLES engine to visualize, else just run the sim with x particles
    if (argc == 1) {
        auto visManager = new G4VisExecutive();
        visManager->Initialize();
        auto ui = new G4UIExecutive(argc, argv);

        UI->ApplyCommand("/vis/open TSG_QT_GLES");
        UI->ApplyCommand("/vis/sceneHandler/create");
        UI->ApplyCommand("/vis/scene/create");
        UI->ApplyCommand("/vis/sceneHandler/attach");
        UI->ApplyCommand("/vis/scene/add/volume");
        UI->ApplyCommand("/vis/scene/add/trajectories smooth");
        UI->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
        UI->ApplyCommand("/vis/viewer/set/style surface");
        UI->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 45 45");
        UI->ApplyCommand("/vis/viewer/set/autoRefresh true");
        UI->ApplyCommand("/vis/viewer/create");
        UI->ApplyCommand("/vis/viewer/update");
        UI->ApplyCommand("/vis/enable");
        ui->SessionStart();
        delete ui;
    } else {
        int nPrimaries = 10;
        std::istringstream( argv[1] ) >> nPrimaries;
        runManager->BeamOn(nPrimaries);
    }

    delete runManager;
}
