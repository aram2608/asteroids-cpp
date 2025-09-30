find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(asteroids-cpp app/main.cpp)

target_link_libraries(asteroids-cpp PRIVATE raylib glfw)