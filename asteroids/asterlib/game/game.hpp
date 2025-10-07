#ifndef GAME_HPP
#define GAME_HPP

#include "asteroids/asteroid.hpp"
#include "ship/ship.hpp"
#include <raylib.h>
#include <vector>

class Game {
  public:
    Game(int window_width, int window_height);
    void draw();
    void update();

  private:
    void spawn_asteroid();
    void delete_lasers();
    void resolve_collisions();
    int window_width;
    int window_height;
    int asteroid_limit;
    float asteroid_spawn_interval;
    float last_asteroid_spawn_time;
    Ship ship;
    std::vector<Asteroid> asteroids;
};

#endif