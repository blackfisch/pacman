# --- Import tools ----

include(../cmake/CPM.cmake)

# ---- Dependencies ----
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# ---- Create standalone executable ----

add_executable(PacMan main.cpp)
target_link_libraries(PacMan PRIVATE project_options project_warnings fmt::fmt spdlog::spdlog sfml-graphics)
