#include "Enemy.h"

#include <cmath>

Enemy::Enemy(
    EnemyType enemyType
) : type(enemyType) {

    active = true;

    switch (type) {
        case EnemyType::Basic:
            radius = 0.60f;
            speed = 2.80f;
            life = 10.0f;
            damage = 10.0f;
            position.y = 0.60f;
            break;

        case EnemyType::Fast:
            radius = 0.45f;
            speed = 4.30f;
            life = 18.0f;
            damage = 8.0f;
            xpReward = 8.0f;
            position.y = 0.45f;
            break;

        case EnemyType::Tank:
            radius = 0.90f;
            speed = 1.70f;
            life = 80.0f;
            damage = 18.0f;
            xpReward = 20.0f;
            position.y = 0.90f;
            break;
    }
}

void Enemy::updateToward(const Vec3& target, float deltaTime) {
    const float dx = target.x - position.x;
    const float dz = target.z - position.z;
    const float length = std::sqrt(dx * dx + dz * dz);

    if (length <= 0.0001f) {
        return;
    }

    position.x += (dx / length) * speed * deltaTime;
    position.z += (dz / length) * speed * deltaTime;
}

void Enemy::takeDamage(float amount) {
    life -= amount;
    if (life <= 0.0f) {
        life = 0.0f;
        active = false;
    }
}
