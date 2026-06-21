#include "WaveManager.h"

#include <algorithm>
#include <cmath>

namespace {
constexpr float PI = 3.14159265358979323846f;
}

WaveManager::WaveManager() : randomEngine(1337u) {}

void WaveManager::reset() {
    spawnTimer = 0.0f;
    randomEngine.seed(1337u);
}

void WaveManager::update(
    float deltaTime,
    float elapsedTime,
    const Player& player,
    std::vector<Enemy>& enemies
) {
    if (enemies.size() >= 120){
        return;
    }

    spawnTimer += deltaTime;

    const float interval = std::max(0.45f, 1.25f - elapsedTime * 0.003f);
    
    if (spawnTimer >= interval) {
        spawnTimer = 0.0f;

        int amount = 1;

        if (elapsedTime >= 20.0f){
            amount = 2;
        }

        if (elapsedTime >= 60.0f) {
            amount = 3;
        }

        for (int i = 0; i < amount; i++){
            spawnEnemy(elapsedTime, player, enemies);
        }        
    }
}

void WaveManager::spawnEnemy(
    float elapsedTime,
    const Player& player,
    std::vector<Enemy>& enemies
) {
    std::uniform_real_distribution<float> angleDistribution(0.0f, 2.0f * PI);
    std::uniform_real_distribution<float> distanceDistribution(13.0f, 17.0f);
    std::uniform_int_distribution<int> typeRoll(0, 99);

    EnemyType type = EnemyType::Basic;
    const int roll = typeRoll(randomEngine);

    if (elapsedTime > 80.0f && roll < 20) {
        type = EnemyType::Tank;
    } else if (elapsedTime > 35.0f && roll < 45) {
        type = EnemyType::Fast;
    }

    const float angle = angleDistribution(randomEngine);
    const float distance = distanceDistribution(randomEngine);

    Enemy enemy(type);
    enemy.position.x = player.position.x + std::cos(angle) * distance;
    enemy.position.z = player.position.z + std::sin(angle) * distance;

    enemies.push_back(enemy);
}
