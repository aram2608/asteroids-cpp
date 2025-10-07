#ifndef SHIP_HPP
#define SHIP_HPP

#include "ship/lasers.hpp"

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <vector>

struct Ship {
    Ship(Vector2 pos, int screen_w, int screen_h);
    void draw();
    void update();
    void keyboard(float delta);
    void fire_laser(float heading_x, float heading_y);

    float max_speed;
    float rotation_speed;
    float decel;
    float rotation;
    float flt_speed;
    int prev_dir;
    Vector2 velocity;
    Vector2 pos;
    Vector2 size;
    int screen_w;
    int screen_h;
    std::vector<Lasers> lasers;
};

#endif