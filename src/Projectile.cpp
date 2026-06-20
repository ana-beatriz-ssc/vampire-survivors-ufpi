#include "Projectile.h"

Projectile::Projectile() {
    radius = 0.18f;
    position.y = 0.65f;
}

void Projectile::update(float deltaTime) {
    position += velocity * deltaTime;
    lifetime -= deltaTime;

    if (lifetime <= 0.0f) {
        active = false;
    }
}
