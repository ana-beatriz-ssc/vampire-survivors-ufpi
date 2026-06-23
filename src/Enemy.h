#pragma once

#include "Entity.h"

enum class EnemyType {
    Basic,
    Fast,
    Tank
};

class Enemy : public Entity {
public:
    explicit Enemy(EnemyType enemyType = EnemyType::Basic);

    void updateToward(const Vec3& target, float deltaTime);
    void takeDamage(float amount);

    EnemyType type = EnemyType::Basic;
    float speed = 2.8f;
    float life = 30.0f;
    float damage = 10.0f;
    float xpReward = 5.0f;
};
