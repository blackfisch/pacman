# --- Import tools ----

include(../cmake/CPM.cmake)

# ---- Dependencies ----
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# ---- Create standalone executable ----

add_executable(PacMan main.cpp include/Game.h include/World.h include/Pacman.h include/Ghost.h include/Moveable.h include/Entity.h include/Edible.h include/Points.h include/SuperPoints.h include/Fruits.h include/Blinky.h include/Inky.h include/Pinky.h include/Clyde.h)
target_link_libraries(PacMan PRIVATE project_options project_warnings fmt::fmt spdlog::spdlog sfml-graphics)
