#include "ship/ship.hpp"

Ship::Ship(Vector2 pos, int screen_w, int screen_h)
    : pos(pos), screen_w(screen_w), screen_h(screen_h) {
    size = Vector2{30, 40};
    max_speed = 250.0f;
    rotation_speed = 100.0f;
    decel = 2000.0f;
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

    // We get the screen width and height for bounds checking
    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();

    // We check the horizontal bounds
    if (pos.x > screen_w) {
        pos.x = 0;
    } else if (pos.x < 0) {
        pos.x = screen_w;
    }
    // We check the vertical bounds
    if (pos.y > screen_h) {
        pos.y = 0;
    } else if (pos.y < 0) {
        pos.y = screen_h;
    }
}

void Ship::keyboard(float delta) {
    // Helper to apply acceleration
    auto approach = [&](float v, float target, float amount) {
        // If velocity is less than our target, we return the smaller value
        // between the amount plus our velocity and the target speed
        if (v < target) {
            return std::min(v + amount, target);
        }
        // If velocity is greater than our target, we return the maximum
        // between the velocity minus our amount and the target speed
        if (v > target) {
            return std::max(v - amount, target);
        }
        // If the velocity is equal to our target we simply return the velocity
        return v;
    };

    // We reset the thrust_target every loop
    float thrust_target = 0.0f;
    // Move forward
    if (IsKeyDown(KEY_UP)) {
        thrust_target = max_speed;
    }
    // Move backwards a bit slower
    if (IsKeyDown(KEY_DOWN)) {
        thrust_target = -max_speed / 2.0f;
    }

    // We change the rotation given the left and right keys
    if (IsKeyDown(KEY_LEFT)) {
        rotation -= rotation_speed * delta;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rotation += rotation_speed * delta;
    }

    // We need to convert rotation degrees into radians
    float rotation_rad = rotation * DEG2RAD;
    // We calculate the heading given the radians of rotation
    float heading_x = std::sin(rotation_rad);
    float heading_y = -std::cos(rotation_rad);

    if (IsKeyPressed(KEY_SPACE)) {
        fire_laser(heading_x, heading_y);
    }

    // We calculate the current speed component from both the y and x velocities
    float current_speed = Vector2Length(velocity);

    // When thrust is not zero we are moving
    if (thrust_target != 0.0f) {
        // We set the velocity components directly based on the heading vector
        // and max speed
        velocity.x = heading_x * thrust_target;
        velocity.y = heading_y * thrust_target;

        // Otherwise we return to the floating speed
    } else {
        // Decelerate by moving the current speed toward the floating speed
        float new_speed = approach(current_speed, flt_speed, decel * delta);

        // We normalize the existing velocity vector and scale it
        Vector2 current_direction = Vector2Normalize(velocity);
        velocity.x = current_direction.x * new_speed;
        velocity.y = current_direction.y * new_speed;
    }
}

void Ship::fire_laser(float heading_x, float heading_y) {
    lasers.emplace_back(pos, heading_x, heading_y, rotation);
}