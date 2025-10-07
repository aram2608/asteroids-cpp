add_library(asterlib
    asterlib/game/game.cpp
    asterlib/ship/ship.cpp
    asterlib/ship/lasers.cpp
)

find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(asterlib
    PUBLIC 
    raylib 
    glfw
)

target_include_directories(asterlib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/asterlib/
)

target_compile_options(asterlib
    PRIVATE
    -Wall 
    -Wextra 
    -Wpedantic 
    -Wconversion
    -Wpessimizing-move
    -Wredundant-move
    -Wmove
    -Wrange-loop-construct
)

add_executable(asteroids_cpp
    app/main.cpp
)

# raylib and gflw are propogated from the library
target_link_libraries(asteroids_cpp
    PRIVATE
    asterlib
)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
    target_link_libraries(asteroids_cpp
        PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework OpenGL"
    )
endif()