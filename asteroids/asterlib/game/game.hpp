#ifndef GAME_HPP
#define GAME_HPP

#include "ship/ship.hpp"
#include <raylib.h>

class Game {
  public:
    Game(int window_width, int window_height);
    void draw();
    void update();

  private:
    int window_width;
    int window_height;
    Ship ship;
};

#endif