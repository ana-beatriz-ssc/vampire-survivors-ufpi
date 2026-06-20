#pragma once

#include "Entity.h"

class Projectile : public Entity {
public:
    Projectile();

    void update(float deltaTime);

    Vec3 velocity {};
    float damage = 24.0f;
    float lifetime = 2.5f;
};
