#include "ship/ship.hpp"

Ship::Ship(Vector2 pos) : pos(pos) {
    size = Vector2{30, 40};
    max_speed = 250.0f;
    rotation_speed = 100.0f;
    accel = 1000.0f;
    flt_speed = 40.0f;
    velocity = Vector2{0, 0};
    rotation = 0;
    prev_dir = 0;
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
    // Helper to apply acceleration
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

    float thrust_target = 0.0f;
    if (IsKeyDown(KEY_UP)) {
        // Move forward
        thrust_target = max_speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        // Move backwards a bit slower
        thrust_target = -max_speed / 2.0f;
    }

    if (IsKeyDown(KEY_LEFT)) {
        rotation -= rotation_speed * delta;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rotation += rotation_speed * delta;
    }

    // We need to convert rotation degrees into radians
    float rotation_rad = rotation * DEG2RAD;

    float heading_x = std::sin(rotation_rad);
    float heading_y = -std::cos(rotation_rad);

    float current_speed = Vector2Length(velocity);

    if (thrust_target != 0.0f) {
        // We set the velocity components directly based on the heading vector
        // and max speed
        velocity.x = heading_x * thrust_target;
        velocity.y = heading_y * thrust_target;

    } else {
        // Decelerate by moving the current speed toward 0
        float new_speed = approach(current_speed, flt_speed, accel * delta);

        if (new_speed != 0.0f) {
            // Re-normalize the existing velocity vector and scale it by the new
            // speed
            Vector2 current_direction = Vector2Normalize(
                velocity); // Requires a vector library or implementation
            velocity.x = current_direction.x * new_speed;
            velocity.y = current_direction.y * new_speed;
        } else {
            // Stop the ship completely if speed is 0
            velocity = {0.0f, 0.0f};
        }
    }
}
