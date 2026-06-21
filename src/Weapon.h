#pragma once

#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

class Weapon {
public:
    void reset();

    bool updateAndShoot(
        const Player& player,
        const std::vector<Enemy>& enemies,
        float deltaTime,
        Projectile& outputProjectile
    );

private:
    float cooldown = 0.85f;
    float timer = 0.0f;
    float projectileSpeed = 13.0f;
    float damage = 10.0f;
};
