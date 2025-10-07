#include "ship/lasers.hpp"

Lasers::Lasers(Vector2 pos, float heading_x, float heading_y, float rotation)
    : pos(pos), heading_x(heading_x), heading_y(heading_y), rotation(rotation) {
    speed = 250;
    size = Vector2{4, 15};
    active = true;
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
}

// Function to draw the lasers to the screen
void Lasers::draw() {
    if (active) {
        DrawRectanglePro(Rectangle{pos.x, pos.y, size.x, size.y},
                         Vector2{size.x / 2, size.y / 2}, rotation,
                         Color{255, 255, 255, 255});
    }
}

// Function to update a lasers positon
void Lasers::update() {
    // If the laser is active
    if (active) {
        // We first get the screen's frame time
        float delta = GetFrameTime();

        // We then bounds check for the horizontal position
        if (pos.x > screen_w) {
            pos.x = 0;
        }
        if (pos.x < 0) {
            pos.x = screen_w;
        }
        // We then bounds check for the vertical position
        if (pos.y > screen_h) {
            pos.y = 0;
        }
        if (pos.y < 0) {
            pos.y = screen_w;
        }
        // We can then apply the changes to the x and y positions
        pos.x += heading_x * speed * delta;
        pos.y += heading_y * speed * delta;
    }
}

Rectangle Lasers::get_rect() { return Rectangle{pos.x, pos.y, size.x, size.y}; }