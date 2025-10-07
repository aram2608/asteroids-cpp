#include "game/game.hpp"

Game::Game(int window_width, int window_height)
    : window_width(window_width), window_height(window_height),
      ship(Vector2{(float)window_width / 2, (float)window_height / 2},
           window_width, window_height) {
    asteroid_limit = 10;
    asteroid_spawn_interval = 0.50f;
    last_asteroid_spawn_time = 0.0f;
}

// Function to draw game objects to screen
void Game::draw() {
    ship.draw();
    for (auto &laser : ship.lasers) {
        laser.draw();
    }
    for (auto &asteroid : asteroids) {
        asteroid.draw();
    }
}

// Function to update the game loop
void Game::update() {
    resolve_collisions();
    ship.update();
    delete_lasers();
    if (asteroids.size() <= asteroid_limit) {
        spawn_asteroid();
    }
    for (auto &laser : ship.lasers) {
        laser.update();
    }
    for (auto &asteroid : asteroids) {
        asteroid.update();
    }
}

// Function to spawn asteroids to screen
void Game::spawn_asteroid() {
    double current_time = GetTime();
    // We first determine the spawn side
    int side = GetRandomValue(0, 3);
    // We initialize an empty spawn position and velocity
    Vector2 spawn_pos = {0.0f, 0.0f};
    Vector2 initial_vel = {0.0f, 0.0f};
    // We calculate the starting speed by randomly choosing between a min and
    // max
    float min_speed = 50.0f;
    float max_speed = 150.0f;
    float speed = (float)GetRandomValue((int)min_speed, (int)max_speed);

    // We match each side to the corresponding logic needed to spawn the
    // asteroid
    switch (side) {
    // Spawn from the left most boundary (x=0)
    case 0:
        spawn_pos.x = 0.0f;
        // Y is randomly placed along the left edge
        spawn_pos.y = (float)GetRandomValue(0, window_height);

        // We set the initial x velocity to a positive value
        initial_vel.x = speed;
        // We set the y velocity to a random component to move slightly up or
        // down
        initial_vel.y = (float)GetRandomValue(-20, 20);
        break;
    // Spawn from the right most boundary (x=map_w)
    case 1:
        spawn_pos.x = window_width;
        spawn_pos.y = (float)GetRandomValue(0, (window_height));

        // We set the initial x velocity to a negative value
        initial_vel.x = -speed;
        initial_vel.y = (float)GetRandomValue(-20, 20);
        break;
    // Spawn from the top most boundary (y=0)
    case 2:
        spawn_pos.y = 0.0f;
        // X is randomly placed along the top edge
        spawn_pos.x = (float)GetRandomValue(0, window_width);

        // We set the initial y velocity to a positive
        initial_vel.y = speed;
        initial_vel.x = (float)GetRandomValue(-20, 20);
        break;
    // Spawn from the bottom most boundary (y=map_h)
    case 3:
        spawn_pos.y = window_height;
        spawn_pos.x = (float)GetRandomValue(0, window_width);

        // We set the initial y velocity to a negative value
        initial_vel.y = -speed;
        initial_vel.x = (float)GetRandomValue(-20, 20);
        break;
    }

    if (current_time - last_asteroid_spawn_time >= asteroid_spawn_interval) {
        // We set our spawn probability at 20%
        if (GetRandomValue(1, 10) <= 2) {
            // We build the asteroid in place and add it to the vector of
            // asteroids
            asteroids.emplace_back(spawn_pos, initial_vel);
        }
        last_asteroid_spawn_time = GetTime();
    }
}

// Function to erase lasers from the vector
void Game::delete_lasers() {
    for (auto it = ship.lasers.begin(); it != ship.lasers.end();) {
        if (!it->active) {
            it = ship.lasers.erase(it);
        } else {
            ++it;
        }
    }
}

// Function to resolve laser/asteroid collisions
void Game::resolve_collisions() {
    for (auto &laser : ship.lasers) {
        auto it = asteroids.begin();

        while (it != asteroids.end()) {
            if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
                it = asteroids.erase(it);
                laser.active = false;

            } else {
                ++it;
            }
        }
    }
}
