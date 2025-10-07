#ifndef SHIP_HPP
#define SHIP_HPP

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

struct Ship {
    Ship(Vector2 pos);
    void draw();
    void update();
    void keyboard(float delta);

    float max_speed;
    float rotation_speed;
    float accel;
    float rotation;
    float flt_speed;
    int prev_dir;
    Vector2 velocity;
    Vector2 pos;
    Vector2 size;
};

#endif