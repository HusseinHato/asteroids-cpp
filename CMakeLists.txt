cmake_minimum_required(VERSION 3.20)
project(Asteroids LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure SFML
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Build static libraries" FORCE)
set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "Do not build examples" FORCE)
set(SFML_BUILD_DOC FALSE CACHE BOOL "Do not build doc" FORCE)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SFML)

add_executable(Asteroids
    src/main.cpp
)

target_link_libraries(Asteroids PRIVATE
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
)

# Set Windows subsystem if desired or keep console for debugging output
# target_link_options(Asteroids PRIVATE -mwindows)
