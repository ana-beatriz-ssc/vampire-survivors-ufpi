#include "Player.h"
#include "Input.h"

#include <algorithm>
#include <cmath>

namespace {
constexpr float ARENA_LIMIT = 19.0f;
}

Player::Player() {
    reset();
}

void Player::reset() {
    position = {0.0f, 0.65f, 0.0f};
    radius = 0.65f;
    active = true;
    speed = 7.0f;
    life = 100.0f;
    maxLife = 100.0f;
    xp = 0.0f;
    xpToNextLevel = 100.0f;
    invulnerabilityTimer = 0.0f;
    level = 1;
}

void Player::update(const InputState& input, float deltaTime) {
    float dx = 0.0f;
    float dz = 0.0f;

    if (input.up) dz -= 1.0f;
    if (input.down) dz += 1.0f;
    if (input.left) dx -= 1.0f;
    if (input.right) dx += 1.0f;

    const float length = std::sqrt(dx * dx + dz * dz);
    if (length > 0.0f) {
        dx /= length;
        dz /= length;
    }

    position.x += dx * speed * deltaTime;
    position.z += dz * speed * deltaTime;

    position.x = std::clamp(position.x, -ARENA_LIMIT, ARENA_LIMIT);
    position.z = std::clamp(position.z, -ARENA_LIMIT, ARENA_LIMIT);
}

void Player::updateTimers(float deltaTime) {
    if (invulnerabilityTimer > 0.0f) {
        invulnerabilityTimer -= deltaTime;
    }
}

void Player::takeDamage(float amount) {
    if (invulnerabilityTimer > 0.0f || life <= 0.0f) {
        return;
    }

    life -= amount;
    invulnerabilityTimer = 0.55f;

    if (life < 0.0f) {
        life = 0.0f;
    }
}
