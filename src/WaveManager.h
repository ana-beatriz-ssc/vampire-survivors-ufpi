#pragma once

#include <random>
#include <vector>

#include "Enemy.h"
#include "Player.h"

class WaveManager {
public:
    WaveManager();

    void reset();
    void update(
        float deltaTime,
        float elapsedTime,
        const Player& player,
        std::vector<Enemy>& enemies
    );

private:
    void spawnEnemy(
        float elapsedTime,
        const Player& player,
        std::vector<Enemy>& enemies
    );

    float spawnTimer = 0.0f;
    std::mt19937 randomEngine;
};
