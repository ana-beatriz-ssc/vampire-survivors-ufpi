#include "Weapon.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "Collision.h"

void Weapon::reset() {
    cooldown = 0.85f;
    timer = 0.0f;
    projectileSpeed = 13.0f;
    damage = 10.0f;
}

bool Weapon::updateAndShoot(
    const Player& player,
    const std::vector<Enemy>& enemies,
    float deltaTime,
    Projectile& outputProjectile
) {
    timer += deltaTime;
    if (timer < cooldown) {
        return false;
    }

    const Enemy* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();

    for (const Enemy& enemy : enemies) {
        if (!enemy.active) {
            continue;
        }

        const float distance = Collision::distanceSquaredXZ(
            player.position,
            enemy.position
        );

        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearest = &enemy;
        }
    }

    if (nearest == nullptr) {
        return false;
    }

    const float dx = nearest->position.x - player.position.x;
    const float dz = nearest->position.z - player.position.z;
    const float length = std::sqrt(dx * dx + dz * dz);

    if (length <= 0.0001f) {
        return false;
    }

    timer = 0.0f;
    outputProjectile = Projectile {};
    outputProjectile.position = player.position;
    outputProjectile.damage = damage;
    outputProjectile.velocity = {
        (dx / length) * projectileSpeed,
        0.0f,
        (dz / length) * projectileSpeed
    };

    return true;
}

void Weapon::increaseDamage(float amount) {
    damage += amount;
}

void Weapon::reduceCooldown(float amount) {
    cooldown = std::max(
        0.20f,
        cooldown - amount
    );
}

float Weapon::getDamage() const {
    return damage;
}

float Weapon::getCooldown() const {
    return cooldown;
}