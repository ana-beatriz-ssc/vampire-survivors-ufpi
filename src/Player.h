#pragma once

#include "Entity.h"

struct InputState;

class Player : public Entity {
public:
    Player();

    void update(const InputState& input, float deltaTime);
    void updateTimers(float deltaTime);
    void takeDamage(float amount);
    void reset();

    float speed = 7.0f;
    float life = 100.0f;
    float maxLife = 100.0f;
    float xp = 0.0f;
    float xpToNextLevel = 100.0f;
    float invulnerabilityTimer = 0.0f;
    int level = 1;
};
