#include "game/game.hpp"

Game::Game(int window_width, int window_height)
    : window_width(window_width), window_height(window_height),
      ship(Vector2{(float)window_width / 2, (float)window_height / 2},
           window_width, window_height) {}

void Game::draw() {
    ship.draw();
    for (auto &laser : ship.lasers) {
        laser.draw();
    }
}

void Game::update() {
    ship.update();
    for (auto &laser : ship.lasers) {
        laser.update();
    }
}
