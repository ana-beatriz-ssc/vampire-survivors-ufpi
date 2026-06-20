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
    float cooldown = 0.55f;
    float timer = 0.0f;
    float projectileSpeed = 18.0f;
    float damage = 24.0f;
};
