#include "WaveManager.h"

#include <algorithm>
#include <cmath>

namespace {
constexpr float PI = 3.14159265358979323846f;

constexpr std::size_t MAX_ENEMIES =
    120;

constexpr float MIN_SPAWN_DISTANCE =
    13.0f;

constexpr float MAX_SPAWN_DISTANCE =
    17.0f;

constexpr float ARENA_LIMIT =
    18.5f;
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
    if (enemies.size() >= MAX_ENEMIES) {
        return;
    }

    spawnTimer += deltaTime;

    float spawnInterval = 1.25f;
    int spawnAmount = 1;

    if (elapsedTime >= 120.0f) {
        spawnInterval = 0.70f;
        spawnAmount = 3;

    } else if (elapsedTime >= 60.0f) {
        spawnInterval = 0.85f;
        spawnAmount = 2;

    } else if (elapsedTime >= 20.0f) {
        spawnInterval = 1.05f;
        spawnAmount = 2;
    }

    if (spawnTimer < spawnInterval) {
        return;
    }

    spawnTimer -= spawnInterval;

    const int availableSlots =
        static_cast<int>(
            MAX_ENEMIES -
            enemies.size()
        );

    const int amountToSpawn =
        std::min(
            spawnAmount,
            availableSlots
        );

    for (
        int i = 0;
        i < amountToSpawn;
        ++i
    ) {
        spawnEnemy(
            elapsedTime,
            player,
            enemies
        );
    }
}

void WaveManager::spawnEnemy(
    float elapsedTime,
    const Player& player,
    std::vector<Enemy>& enemies
) {
    std::uniform_real_distribution<float>
        angleDistribution(
            0.0f,
            2.0f * PI
        );

    std::uniform_real_distribution<float>
        distanceDistribution(
            MIN_SPAWN_DISTANCE,
            MAX_SPAWN_DISTANCE
        );

    const float angle =
        angleDistribution(randomEngine);

    const float distance =
        distanceDistribution(randomEngine);

    const EnemyType type =
        chooseEnemyType(elapsedTime);

    Enemy enemy(type);

    enemy.position.x =
        player.position.x +
        std::cos(angle) * distance;

    enemy.position.z =
        player.position.z +
        std::sin(angle) * distance;

    enemy.position.x =
        std::clamp(
            enemy.position.x,
            -ARENA_LIMIT,
            ARENA_LIMIT
        );

    enemy.position.z =
        std::clamp(
            enemy.position.z,
            -ARENA_LIMIT,
            ARENA_LIMIT
        );

    enemies.push_back(enemy);
}

EnemyType WaveManager::chooseEnemyType(
    float elapsedTime
) {
    std::uniform_int_distribution<int>
        typeRoll(0, 99);

    const int roll =
        typeRoll(randomEngine);

    if (elapsedTime < 20.0f) {
        return EnemyType::Basic;
    }

    if (elapsedTime < 60.0f) {
        if (roll < 25) {
            return EnemyType::Fast;
        }

        return EnemyType::Basic;
    }

    if (elapsedTime < 120.0f) {
        if (roll < 15) {
            return EnemyType::Tank;
        }

        if (roll < 45) {
            return EnemyType::Fast;
        }

        return EnemyType::Basic;
    }

    if (roll < 25) {
        return EnemyType::Tank;
    }

    if (roll < 60) {
        return EnemyType::Fast;
    }

    return EnemyType::Basic;
}