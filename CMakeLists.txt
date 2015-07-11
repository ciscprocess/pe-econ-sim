cmake_minimum_required(VERSION 3.2)
project(pe_econ_sim)

# enforce C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where I keep SFML -- I might want to make this a relative path
set(SFML_ROOT "C:/SFML-2.3/")

# Tell cmake where to find the SFML config -- again, relative pathing might be good here
list(APPEND CMAKE_MODULE_PATH "C:/SFML-2.3/cmake/Modules")

# set(SFML_STATIC_LIBRARIES TRUE)

# Require SFML with the system, window, graphics, and audio modules
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

# Include the appropriate SFML header files
include_directories(${SFML_INCLUDE_DIR})

include_directories("./include")

include_directories("C:/boost_1_58_0")

# Set the source of the main executable
set(SOURCE_FILES main.cpp)
add_executable(pe_econ_sim ${SOURCE_FILES} src/Program.cpp include/Program.h src/EventManager.cpp include/EventManager.h src/Game.cpp include/Game.h src/GameState.cpp include/GameState.h src/GameStateSeeder.cpp include/GameStateSeeder.h src/ClusterSeederV1.cpp include/ClusterSeederV1.h src/Unit.cpp include/Unit.h src/CellularBoard.cpp include/CellularBoard.h src/BoardCell.cpp include/BoardCell.h src/Civilian.cpp include/Civilian.h src/PlainsCell.cpp include/PlainsCell.h src/DesertCell.cpp include/DesertCell.h src/ForestCell.cpp include/ForestCell.h src/IsometricBoardVisualizer.cpp include/IsometricBoardVisualizer.h src/IsometricSceneVisualizer.cpp include/IsometricSceneVisualizer.h src/GameInteractionEvent.cpp include/GameInteractionEvent.h src/ClickAtCoordinate.cpp include/ClickAtCoordinate.h src/GameAction.cpp include/GameAction.h)

# Link against SFML
target_link_libraries(pe_econ_sim ${SFML_LIBRARIES})