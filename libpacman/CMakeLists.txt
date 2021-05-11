# ---- Dependencies ----
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ---- Create library ----
add_library(libpacman ${headers} ${sources})

set_target_properties(libpacman PROPERTIES CXX_STANDARD 20)

# Link dependencies
target_link_libraries(libpacman PRIVATE spdlog::spdlog)

target_include_directories(
        libpacman PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)