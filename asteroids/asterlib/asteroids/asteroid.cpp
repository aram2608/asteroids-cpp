#include "asteroids/asteroid.hpp"

Asteroid::Asteroid(Vector2 center, Vector2 heading)
    : center(center), heading(heading) {
    radius = 20;
    speed = 100;
    active = true;
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
}

void Asteroid::draw() {
    DrawCircle(center.x, center.y, radius, Color{255, 255, 255, 255});
}
void Asteroid::update() {
    // If the laser is active
    if (active) {
        // We first get the screen's frame time
        float delta = GetFrameTime();

        // We then bounds check for the horizontal position
        if (center.x > screen_w) {
            center.x = 0;
        }
        if (center.x < 0) {
            center.x = screen_w;
        }
        // We then bounds check for the vertical position
        if (center.y > screen_h) {
            center.y = 0;
        }
        if (center.y < 0) {
            center.y = screen_w;
        }
        // We can then apply the changes to the x and y positions
        center.x += heading.x * speed * delta;
        center.y += heading.y * speed * delta;
    }
}