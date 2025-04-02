cmake_minimum_required(VERSION 3.16...3.21)
project(docker_g4)

find_package(Geant4 REQUIRED)

# include Geant4 headers
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(docker_g4 "main.cc" ${sources} ${headers})
target_link_libraries(docker_g4 ${Geant4_LIBRARIES})

install(TARGETS docker_g4 DESTINATION bin)
