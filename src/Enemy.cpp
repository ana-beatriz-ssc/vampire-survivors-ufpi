#include "Enemy.h"

#include <cmath>

Enemy::Enemy(EnemyType enemyType) : type(enemyType) {
    position.y = 0.6f;

    switch (type) {
        case EnemyType::Basic:
            radius = 0.6f;
            speed = 2.8f;
            life = 30.f;
            damage = 10.0f;
            break;
        case EnemyType::Fast:
            radius = 0.45f;
            speed = 4.3f;
            life = 18.0f;
            damage = 8.0f;
            break;
        case EnemyType::Tank:
            radius = 0.9f;
            speed = 1.7f;
            life = 80.0f;
            damage = 18.0f;
            //position.y = 0.9f;
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
