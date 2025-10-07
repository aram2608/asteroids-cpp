#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <raylib.h>

struct Asteroid {
    Asteroid(Vector2 center, Vector2 heading);
    void draw();
    void update();

    Vector2 center;
    Vector2 heading;
    int radius;
    int speed;
    bool active;
    int screen_w;
    int screen_h;
};

#endif