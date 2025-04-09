Geant4 is a toolkit for developing particle detector simulations. Before starting the exercise, make sure you have cloned this repository and set your own branch so you can save your work and have it reviewed. Include a PDF of your answers. Pushing doesn’t need to be done only once — it’s good practice to commit your progress whenever you verify that a step is working, and to leave a comment describing what you did. This becomes especially important as your code grows in size and you start working with other people.

## Exercise 0: Hello World, I Found the Libraries!

While building a detector simulation from scratch (including CMake) builds character, we’ve decided to give you a minimal plug-and-play detector to get you to the good bits more quickly. You’ll see a `CMakeLists.txt` file that handles details like where your files are and what should be used to compile your program. There’s also an `include/` folder full of headers (who talks to who) and a `src/` folder with source files (the meat). The main star is the `main.cc` file, where all the source files are combined with Geant4 to generate a run.

You’ll notice much of main.cc is devoted to visualization. The visualization just helps you confirm your setup is correct. The real substance is in the output, which is just printed to the command line rather than saved to, say, a ROOT file. Here’s a step-by-step:

- Run the shell script:  
  `source /cvmfs/sft.cern.ch/lcg/releases/LCG_106/Geant4/11.2.1/x86_64-el8-gcc11-opt/Geant4-env.sh`  
  CVMFS contains Geant4, its prerequisites, and other useful tools. Running this should set you up to start running your own Geant4 simulations.

- Git clone this repo with `git clone https://github.com/SaelMo/NikhefProjectGeant4Student.git`, `cd` into `NikhefProjectGeant4Student` (ls should show you `main.cc`). Then  
  `mkdir build` then `cd build`
  To keep our build stuff in one place rather than strewn around. We want to cmake the stuff one folder up (what `..` is for) while staying inside build so we will run
  `cmake ..`
  If this step works it has found the libraries the CMakeLists asked for, if these are correct or not we will find out next step..
  
- Inside the build directory run  
  `make -j`  
  The `-j` flag uses all available CPU cores to speed things up. You’ll need to re-run this command everytime you change source files. In big collaborations, `.mac` files are used to avoid redundant recompilation, but we won't cover those here.

- You now have an executable (this isn’t Python!). Run it inside the build directory using:
  `./NikhefProject`  
  First, try running it without any arguments to check out the visualization (`/vis/open TSG_QT_GLES` if it doesn't render automatically). Hit the green button to simulate a single particle. You're looking at a gamma ray striking a NaI crystal! Check your console for some of the stuff Geant4 spews out. 
  Once you feel comfortable with the setup, close the window and run a fuller simulation without visualization, say, 100 primaries:  
  `./NikhefProject 100`
  
  Read the output, what kind of interactions are we looking at, what kind of energy are we dealing with and how big is that crystal actually? Check the `\src` folder for answers. The code is kept minimal to make this less of a drag.

Also, there’s a `.gitignore` file to exclude unnecessary files from your repository, like the `build/` directory. It’s good practice not to push stuff needlessly, especially if there’s a security risk or if others are working with your code.

Here are a few exercises to get your hands dirty:

- Check out the **Primary Generator Action**. Try rotating the gun by 45 degrees across your favorite axis, and increase the energy to x MeV (x is your age in years). Does the simulation behave as expected? 
- Go to the **Detector Construction** class. Make the crystal a little taller and narrower so that it looks like a stick, and change the default water to G4_Galactic. What impact does this have on your setup?
- Look at the **Stepping Action**. How is the total energy deposited inside the crystal calculated? Can you add an `if` statement to suppress printing if the deposited energy is below let's say 10 keV? What is the definition of things being printed? Check the resources down the README.
- If you shoot 5 photons of 2 MeV (10 MeV total) and 9 MeV is deposited, we'll call that an efficiency of 90%. What efficiency are you getting with the default set up for a large number of primaries? WARNING: this is not the detector efficiency, but more of an "energy deposition efficiency". When you see a datasheet or article talking about efficiency make sure you understand what they exactly mean, it'll save you quite a headache.
---

## The Exercises, Bonus Exercises for the Hard Boiled Are in Curly Brackets {} (WE ASSUME THE DEFAULT MATERIAL IS G4_GALACTIC)

Geant4 is used in dark matter/neutrino experiments, medical/biophysics, extremely high-energy CERN experiments, and even more energetic events in cosmic ray experiments. While there are many other simulation packages in particle physics such as CST Studio, COMSOL, or Pythia, this exercise will show you the general considerations involved in developing a particle physics simulation, and also the types of tasks you might want to split in a real-world research group.

1. **Analysis:**
   - The output is lousy as is, generate a ROOT (or other) file instead. Then plot out the result like the deposited energy position with C++, Python, Graphomat Z64, or whatever you fancy.
   - Perform a simulation in air with gamma energies: 1 eV, 100 eV, 1 keV, 10 keV, 250 keV, 1 MeV, 3 MeV, 10 MeV, 1 GeV — and choose the number of primaries properly (enough statistics for nice graphs).
   - Plot the deposited (in the crystal) energy versus deposition process (like Compton scattering). How does the dominant process vary with respect to energy? When does Compton scattering beat photoelectric (if ever), and when does pair production matter (if ever)?
   - {How does the distribution of deposition locations vary with photon energy? Higher energies penetrate deeper, but do they scatter more or less violently?}
   - {This is a good question to ask when shooting a dangerous particle gun — what fraction of high-energy particles are scattered back to the shooter!? You can pick the energy of study yourself, as long as you have 1000 cases of backscatter.}

2. **Geometry and Materials:**
   - What is the efficiency in G4_GALACTIC versus G4_WATER. Does it make a big difference if it's 2 MeV or 1 MeV?
   - Try a different popular crystal, like Germanium. Does this affect the efficiency greatly? Repeat both NaI and the new crystal with a 100 keV beam. Is the relative efficiency too different?
   - Go back to 2 MeV NaI and try shielding it with a rectangular plate of lead that's 1 cm thick. What is your efficiency now? What thickness do you need before it's halved? Did you need to move the detector further away? Does it matter if the lead plate is right in front of it or if it's closer to the source?
   - {Here's a brain teaser: compare a simulation with 5 cm lead shielding to that of 5 separate plates of 1 cm lead separated by 1 cm of air. Is there a noticeable difference in efficiency? Would the same happen for a high-energy muon going through it (no need to simulate)? Does the fact we're using air matter?}
   - {Add a 3 cm semi-cylinder shield using G4Tubs (hollow cylinder) to reduce the number of gamma rays penetrating the crystal. Have the photons also escape from a "Demon Core" which you can model as two hemispheres with a hemispherical cavity (Subtraction solids) oriented in such a way that there is a little slit the photons can escape from without interacting with the cavity. What effect do the additions of these two materials have on your efficiency? For 100 keV?}

3. **Primary Generation:**
   - Shoot a single gamma ray with 220 PeV — the energy of the neutrino recently measured by KM3NeT. What is the efficiency? What happens if you shoot a neutrino or muon? How many interactions did you get?
   - Currently we are just shooting monochromatic photons in one direction. Shoot two photons with the energy of Co60 decay. Shoot them isotropically — any direction randomly.
   - We also want to simulate the beta particles coming out. Take the most common beta decay and have its energy be random with respect to the model distribution `f ~ pE(Q-E)^2`, with `p` the momentum and `Q` the maximum kinetic energy.
   - {What if your radioactive source covers another material? Make the particle spawn randomly along the surface of a G4_GRAPHITE sphere.}
   - {Final: Implement Co60 G4RadioactiveDecay. Compare the energies, particles, and angles.}

4. **Optical Physics:**
   - Import optical physics on top of the physics lists we're using now. Add scintillation, refraction, and absorption, and make a plot of optical photon trajectories using C++, Python, or whatever you prefer. *Note:* Keep number of primaries low — these simulations are no joke. This will require modifying Detector Construction and handling new outputs.
   - Modify Stepping Action to only print optical photons if they deposit a relatively large amount of energy and also print the total energy deposited by only optical photons, not just every particle.
   - What effect does a higher refractive index and absorption have on efficiency?
   - {A gamma ray can penetrate iron. Add a 1 mm metal shell to the crystal (G4Tubs) and show how this affects the efficiency. Did you lose too much from the gamma ray losing energy? Does it keep the optical photons trapped?}

5. **Jack of All Trades**
   - Move the crystal closer to the source and change its material to Germanium. Add 1 cm of lead to the cylinder label and rotate it so that the point source is hitting the bottom of the crystal from a distance of a centimeter. Enclose the experiment with lead.
   - Pick a random number for the photon energy from a Gaussian distribution with a mean of 1 MeV, standard deviation of 100 keV, and truncate it between [800, 1100].
   - {Have the photon shoot in a cone of 45 degrees uniformly.}
   - Modify Stepping Action to print `"HIGH ENERGY EVENT"` whenever a photon entering it has an energy of 1050 keV or higher and makes an angle of ten degrees or less with respect to the surface normal.

### Resources

I am not going to appeal to Plato's anamnesis, especially if you are not too familiar with C++. You can check Geant4's own documentation for examples and definitions, and Geant4 is also *open source*. So if you recently discovered that in the photoelectric effect, photons are also generated (but, how?), you can explore how Geant4 handles this quantum phenomenon in its source code.

- **Mostly Application Developer's Guide & Physics Reference Manual:** [Geant4 Documentation](https://geant4.web.cern.ch/docs/)
- **Geant4 Open-Source Repository:** [Geant4 GitHub](https://github.com/Geant4/Geant4)
