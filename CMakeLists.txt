cmake_minimum_required(VERSION 3.16...3.21)
project(NikhefProject)

# Find Geant4 package, if it's not found you need to give an address
find_package(Geant4 REQUIRED)

# Include user-defined header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Include Geant4 settings
include(${Geant4_USE_FILE})

# Collect source and header files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Don't want to miss the main star?
list(APPEND sources ${PROJECT_SOURCE_DIR}/main.cc)

# Part where you generate the executable, it's not like Python anymore
add_executable(NikhefProject ${sources} ${headers})

# Link against Geant4 libraries, generally a migraine inducer
target_link_libraries(NikhefProject ${Geant4_LIBRARIES})

# Install target
install(TARGETS NikhefProject DESTINATION bin)
