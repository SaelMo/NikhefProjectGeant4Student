cmake_minimum_required(VERSION 3.16...3.21)
project(NikhefProject)

set(GEANT4_INSTALL_DIR /data/the_nikhef_experiment/2020/geant4.10.6)

list(APPEND CMAKE_PREFIX_PATH "${GEANT4_INSTALL_DIR}/share/Geant4-10.6.0")

find_package(Geant4 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

find_library(EXPAT_LIBRARY NAMES expat PATHS ${EXPAT_LIBRARY} REQUIRED)

add_executable(NikhefProject "main.cc" ${sources} ${headers})
target_link_libraries(NikhefProject ${Geant4_LIBRARIES} ${EXPAT_LIBRARY})

install(TARGETS NikhefProject DESTINATION bin)