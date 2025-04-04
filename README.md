# Geant4

GEANT4 is a toolkit for developing detector simulations. Before starting the exercise, create a GitHub repository and work from there. It is good practice to commit your progress whenever you verify that a step is working (e.g., expected output and successful header imports).

## Exercise 0: Hello World

Run a Hello World program (see `main.cc`) to check if you can use GEANT4 (`G4ios`). This requires adding the missing pieces to the `CMakeLists.txt` file. It is recommended to create a directory called `build`, run `cmake ..` from there, and then use `make -j` (`-j` utilizes all CPU cores). You'll then be left with executable which you run like `.NikhefProject` with some input. Geant4 has some prerequisites, if it's telling it can't find EXPAT I'll lend you mine: use `-DEXPAT_LIBRARY=/user/selmorab/libexpat/lib/libexpat.so` while cmake-ing. Also `source /data/the_nikhef_experiment/2020/geant4.10.6/bin/geant4.sh` if it's not finding Geant4. Also also I tarred some starter files to not mess with the Hello world exercise.

Once this step is complete, you can start the detector exercise. It's tedious when things don't work out of the box, but understanding how a compiler language does its thing is worthwhile skill both within physics and elsewhere. Physicists rarely write full GEANT4 simulations in isolation after all. Also, having a `.gitignore` file to exclude extraneous files from your repository is good practice.

---

## Developing the Simulation

Now that you have access to GEANT4, we can start coding! There are many ways to structure a GEANT4 simulation, and in this exercise, we (well you*) will:

- Rewrite `main.cc` to include a `G4RunManager`. After registration and initialization, it should take an integer value set by the user (`runManager->BeamOn(numberPrimaries)`) to run a simulation.
-  Organize the project by setting up an `include` folder for headers and a `src` folder for source files.
-  Implement `ActionInit`, which initializes:
   - `PrimaryGenAction` to spawn particles.
   - `SteppingAction` to print stuff
-  Output results into a ROOT/CSV file or print them to the command line.
-  Implement `DetConstruction` to define the detector's geometry and materials.
-  Ensure that all files communicate with `main.cc`, where the physics list is imported.

### Task Distribution
At a minimum, there are four roles to distribute among team members:

1. **Input/Output:**
   - Ensure useful output from the program. Don't track too much stuff (slows down system) or too little. CSV file or print?
   - Verify that particle spawner inputs and material properties are well-sourced (e.g., where you get that model/measurement?).
   - Visualize data. Can be done via Geant4 or Python.
   - Start by examining `SteppingAction` and `PrimaryGenAction`.

2. **Geometry:**
   - Create a realistic physical model (physics lists) while balancing performance and accuracy.
   - Model both the source and the detector.
   - With Main lead ensure communication with other parts.
   - Start by examining `DetConstruction`.

3. **Material and Physics List:**
   - Associate material properties with the geometry.
   - Input/Output gives you the numbers, you choose how to implement refraction for example.
   - Work closely with the Input/Output role to validate physical accuracy.
   - Start by examining `DetConstruction`.

4. **Main Lead:**
   - Develop `main.cc` and make executive decision on the set up. Maybe separate `.cc` for material and geometry? You'll require a broad perspective of everything.
   - Establish communication between components (e.g., geometry and particle spawning).
   - Ensure consistency and efficiency across the project. Primary gen people aren't printing stuff that Input/Output people can do better?
   - Write the header files.

### Expanding the Scope
Just because I cut things in four does not mean you should, you can for example
   - Split Input and Output tasks to speed things up.
   - Assign additional team members to geometry, materials, and physics implementation to increase simulation detail. Could we use or do we need an electric field?
   
Planning your simulation is part of the exercise. While excessive planning can delay coding, poor planning can lead to inefficient work distribution or difficult-to-maintain code.

### Resources
I am not going to appeal to Plato's anamnesis, especially if you are not too familiar with C++. You can check GEANT4's own documentation for examples and definitions, and GEANT4 is also `open source`. So if you recently discovered that in the photon electric effect, photons are also generated (wait, how?), you can explore how GEANT4 handles this quantum phenomenon in its source code.
- **Mostly Application Developer's Guide & Physics Reference Manual:** [GEANT4 Documentation](https://geant4.web.cern.ch/docs/)
- **GEANT4 Open-Source Repository:** [GEANT4 GitHub](https://github.com/Geant4/geant4)
---

GEANT4 is used in Dark Matter/neutrino experiments, extremely high energy CERN experiments, and even more energetic events in cosmic ray experiments (also medical/biophysics). While there are many other simulation packages in particle physics such as CST studio, COMSOL, or Pythia, this exercise will show you the general considerations involved in developing a particle physics simulation in general, and also the type of group work/organization that is required in real world research.
