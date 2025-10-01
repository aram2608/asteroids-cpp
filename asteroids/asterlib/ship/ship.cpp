#include "ship/ship.hpp"
#include "ship.hpp"

Ship::Ship(Vector2 pos) : pos(pos) {
    size = Vector2{30, 40};
    max_speed = 250.0f;
    rotation_speed = 200;
    accel = 1000.0f;
    velocity = Vector2{0, 0};
    rotation = 0;
}

void Ship::draw() {
    // DrawRectangle(pos.x, pos.y, size.x, size.y, Color{255, 255, 255, 255});
    DrawRectanglePro(Rectangle{pos.x, pos.y, size.x, size.y},
                     Vector2{size.x / 2, size.y / 2}, rotation,
                     Color{255, 255, 255, 255});
}
void Ship::update() {
    float delta = GetFrameTime();

    // Catch keyboard events
    keyboard(delta);

    // We apply velocity changes to the ship
    pos.x += velocity.x * delta;
    pos.y += velocity.y * delta;
}

void Ship::keyboard(float delta) {
    // Helper to apply intertia
    auto approach = [&](float v, float target, float amount) {
        if (v < target) {
            // If velocity is less than our target we return the smaller
            // of the amount plus our velocity and the target
            return std::min(v + amount, target);
        }
        if (v > target) {
            return std::max(v - amount, target);
        }
        return v;
    };

    if (IsKeyPressed(KEY_SPACE)) {
        // TODO: Add lasers
    }

    int direction = 0;
    if (IsKeyDown(KEY_UP)) {
        direction = -1;
    }
    if (IsKeyDown(KEY_DOWN)) {
        direction = 1;
    }
    if (IsKeyDown(KEY_LEFT)) {
        rotation -= rotation_speed * delta;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rotation += rotation_speed * delta;
    }

    if (direction != 0) {
        velocity.y =
            approach(velocity.y, (float)direction * max_speed, accel * delta);
    } else {
        velocity.y = approach(velocity.y, 0.0f, accel * delta);
    }
}
