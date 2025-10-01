#include "game/game.hpp"
#include "game.hpp"

Game::Game(int window_width, int window_height)
    : window_width(window_width), window_height(window_height),
      ship(Vector2{(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2}) {
}

void Game::draw() { ship.draw(); }

void Game::update() { ship.update(); }
