#include "asteroids/asteroid.hpp"

Asteroid::Asteroid(Vector2 center, Vector2 velocity)
    : center(center), velocity(velocity) {
    radius = 20;
    active = true;
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
}

// Function to draw asteroids to screen
void Asteroid::draw() {
    DrawCircle(center.x, center.y, radius, Color{255, 255, 255, 255});
}

// Function to update the asteroids position
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
        center.x += velocity.x * delta;
        center.y += velocity.y * delta;
    }
}

// Function to return the Rectangle for the asteroid
Rectangle Asteroid::get_rect() {
    return Rectangle{center.x, center.y, (float)radius * 2, (float)radius * 2};
}