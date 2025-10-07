#include "ship/lasers.hpp"

Lasers::Lasers(Vector2 pos, float rotation) : pos(pos), rotation(rotation) {
    speed = 20;
    size = Vector2{15, 4};
    active = true;
}

void Lasers::draw() {
    if (active) {
        DrawRectangle(pos.x, pos.y, size.x, size.y, Color{255, 255, 255, 255});
    }
}

void Lasers::update() {
    if (active) {
        float rot_rads = rotation * DEG2RAD;
    }
}

Rectangle Lasers::get_rect() { return Rectangle{pos.x, pos.y, size.x, size.y}; }