#ifndef LASERS_HPP
#define LASERS_HPP

#include <raylib.h>
#include <raymath.h>

struct Lasers {
    Lasers(Vector2 pos, float rotation);
    void draw();
    void update();
    Rectangle get_rect();

    Vector2 pos;
    Vector2 size;
    int speed;
    float rotation;
    bool active;
};

#endif