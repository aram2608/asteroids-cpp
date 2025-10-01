#include "../asterlib/game/configs.hpp"
#include "../asterlib/game/game.hpp"

#include <iostream>
#include <raylib.h>

using namespace Configs;

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "C++ - Asteroids");
    SetTargetFPS(60);
    Game game = Game(WINDOW_WIDTH, WINDOW_HEIGHT);
    while (!WindowShouldClose()) {

        game.update();

        BeginDrawing();
        ClearBackground(Color{0, 0, 0, 255});
        game.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}