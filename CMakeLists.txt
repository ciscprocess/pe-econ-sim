cmake_minimum_required(VERSION 3.2)
project(pe_econ_sim)

# enforce C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where I keep SFML -- I might want to make this a relative path
set(SFML_ROOT "C:/SFML-2.3/")

set(LEMON_ROOT "C:/Program Files (x86)/LEMON")

# Tell cmake where to find the SFML config -- again, relative pathing might be good here
list(APPEND CMAKE_MODULE_PATH "C:/SFML-2.3/cmake/Modules")

list(APPEND CMAKE_MODULE_PATH "C:/Program Files (x86)/LEMON/cmake")

# set(SFML_STATIC_LIBRARIES TRUE)

# Require SFML with the system, window, graphics, and audio modules
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

find_package(LEMON REQUIRED)

# Include the appropriate SFML header files
include_directories(${SFML_INCLUDE_DIR})

include_directories(${LEMON_INCLUDE_DIR})

include_directories("./include")

include_directories("C:/boost_1_58_0")

# Set the source of the main executable
set(SOURCE_FILES main.cpp)
add_executable(pe_econ_sim ${SOURCE_FILES} src/Program.cpp include/Program.h src/event/EventManager.cpp include/event/EventManager.h src/game/Game.cpp include/game/Game.h src/game/GameState.cpp include/game/GameState.h src/game/generation/GameStateSeeder.cpp include/game/generation/GameStateSeeder.h src/game/generation/ClusterSeederV1.cpp include/game/generation/ClusterSeederV1.h src/game/Unit.cpp include/game/Unit.h src/world/CellularBoard.cpp include/world/CellularBoard.h src/world/BoardCell.cpp include/world/BoardCell.h src/game/Civilian.cpp include/game/Civilian.h src/world/PlainsCell.cpp include/world/PlainsCell.h src/world/DesertCell.cpp include/world/DesertCell.h src/world/ForestCell.cpp include/world/ForestCell.h src/visualization/IsometricBoardVisualizer.cpp include/visualization/IsometricBoardVisualizer.h src/visualization/IsometricSceneVisualizer.cpp include/visualization/IsometricSceneVisualizer.h src/event/GameInteractionEvent.cpp include/event/GameInteractionEvent.h src/event/ClickAtCoordinate.cpp include/event/ClickAtCoordinate.h src/game/GameAction.cpp include/game/GameAction.h src/game/GameActionQueue.cpp include/game/GameActionQueue.h src/game/generation/ClusterSeederV2.cpp include/game/generation/ClusterSeederV2.h src/numeric/Random.cpp include/numeric/Random.h)

# Link against SFML
target_link_libraries(pe_econ_sim ${SFML_LIBRARIES} "C:/Program Files (x86)/LEMON/lib/liblemon.a")