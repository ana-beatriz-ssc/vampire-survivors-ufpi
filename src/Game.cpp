#include "Game.h"

#include <algorithm>
#include <cmath>

#include "Collision.h"

void Game::initialize() {
    restart();
}

void Game::restart() {
    player.reset();
    enemies.clear();
    xpOrbs.clear();
    projectiles.clear();
    weapon.reset();
    waveManager.reset();

    elapsedTime = 0.0f;
    kills = 0;
    gameOver = false;
    victory = false;

    Enemy enemyA(EnemyType::Basic);
    enemyA.position = {6.0f, 0.6f, 6.0f};
    enemies.push_back(enemyA);

    Enemy enemyB(EnemyType::Fast);
    enemyB.position = {-7.0f, 0.45f, 4.0f};
    enemies.push_back(enemyB);

    Enemy enemyC(EnemyType::Tank);
    enemyC.position = {3.0f, 0.9f, -8.0f};
    enemies.push_back(enemyC);
}

void Game::update(const InputState& input, float deltaTime) {
    if ((gameOver || victory) && input.restart) {
        restart();
        return;
    }

    if (gameOver || victory) {
        return;
    }

    elapsedTime += deltaTime;
    player.updateTimers(deltaTime);
    player.update(input, deltaTime);

    waveManager.update(deltaTime, elapsedTime, player, enemies);

    for (Enemy& enemy : enemies) {
        if (enemy.active) {
            enemy.updateToward(player.position, deltaTime);
        }
    }

    separateEnemies();

    Projectile newProjectile;
    if (weapon.updateAndShoot(player, enemies, deltaTime, newProjectile)) {
        projectiles.push_back(newProjectile);
    }

    for (Projectile& projectile : projectiles) {
        if (projectile.active) {
            projectile.update(deltaTime);
        }
    }

    checkCollisions();
    processLevelUps();
    removeInactiveEntities();

    if (player.life <= 0.0f) {
        gameOver = true;
    }

    if (elapsedTime >= 300.0f) {
        victory = true;
    }
}

void Game::separateEnemies() {
    constexpr float EPSILON = 0.0001f;
    constexpr float CORRECTION_STRENGTH = 0.8f;

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        Enemy& enemyA = enemies[i];

        if (!enemyA.active) {
            continue;
        }

        for (
            std::size_t j = i + 1;
            j < enemies.size();
            ++j
        ) {
            Enemy& enemyB = enemies[j];

            if (!enemyB.active) {
                continue;
            }

            const float dx =
                enemyB.position.x -
                enemyA.position.x;

            const float dz =
                enemyB.position.z -
                enemyA.position.z;

            const float minimumDistance =
                enemyA.radius +
                enemyB.radius;

            const float distanceSquared =
                dx * dx + dz * dz;

            if (
                distanceSquared >=
                minimumDistance * minimumDistance
            ) {
                continue;
            }

            float directionX = 1.0f;
            float directionZ = 0.0f;
            float distance = 0.0f;

            if (distanceSquared > EPSILON) {
                distance =
                    std::sqrt(distanceSquared);

                directionX = dx / distance;
                directionZ = dz / distance;
            }

            const float overlap =
                minimumDistance - distance;

            const float correction =
                overlap *
                0.5f *
                CORRECTION_STRENGTH;

            enemyA.position.x -=
                directionX * correction;

            enemyA.position.z -=
                directionZ * correction;

            enemyB.position.x +=
                directionX * correction;

            enemyB.position.z +=
                directionZ * correction;
        }
    }
}

void Game::spawnXpOrb(
    const Enemy& enemy
) {
    XpOrb orb;

    orb.position = enemy.position;
    orb.position.y = 0.28f;

    orb.value = enemy.xpReward;

    xpOrbs.push_back(orb);
}

void Game::checkCollisions() {
    for (Enemy& enemy : enemies) {
        if (!enemy.active) {
            continue;
        }

        if (Collision::circlesIntersectXZ(
                player.position,
                player.radius,
                enemy.position,
                enemy.radius
            )) {
            player.takeDamage(enemy.damage);
        }
    }

    for (Projectile& projectile : projectiles) {
        if (!projectile.active) {
            continue;
        }

        for (Enemy& enemy : enemies) {
            if (!enemy.active) {
                continue;
            }

            if (Collision::circlesIntersectXZ(
                    projectile.position,
                    projectile.radius,
                    enemy.position,
                    enemy.radius
                )) {
                const bool wasAlive = enemy.active;
                enemy.takeDamage(projectile.damage);
                projectile.active = false;

                if (wasAlive && !enemy.active) {
                    ++kills;
                    spawnXpOrb(enemy);
                }
                break;
            }
        }
    }

    for (XpOrb& orb : xpOrbs) {
    if (!orb.active) {
        continue;
    }

    if (Collision::circlesIntersectXZ(
            player.position,
            player.radius,
            orb.position,
            orb.radius
        )) {
        player.xp += orb.value;
        orb.active = false;
        }
    }
}

void Game::removeInactiveEntities() {
    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy) { return !enemy.active; }
        ),
        enemies.end()
    );

    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [](const Projectile& projectile) { return !projectile.active; }
        ),
        projectiles.end()
    );

    for (XpOrb& orb : xpOrbs) {
    if (!orb.active) {
        continue;
    }

    if (Collision::circlesIntersectXZ(
            player.position,
            player.radius,
            orb.position,
            orb.radius
        )) {
        player.xp += orb.value;
        orb.active = false;
        }
    }
}

void Game::processLevelUps() {
    while (
        player.xp >=
        player.xpToNextLevel
    ) {
        player.xp -=
            player.xpToNextLevel;

        ++player.level;

        player.xpToNextLevel =
            static_cast<float>(
                std::ceil(
                    player.xpToNextLevel *
                    1.25f
                )
            );

        applyAutomaticUpgrade();
    }
}

void Game::applyAutomaticUpgrade() {
    const int upgradeIndex =
        (player.level - 2) % 3;

    switch (upgradeIndex) {
        case 0:
            weapon.increaseDamage(2.0f);
            break;

        case 1:
            weapon.reduceCooldown(0.05f);
            break;

        case 2:
            player.speed += 0.25f;
            break;
    }
}

const Player& Game::getPlayer() const {
    return player;
}

const std::vector<Enemy>& Game::getEnemies() const {
    return enemies;
}

const std::vector<Projectile>& Game::getProjectiles() const {
    return projectiles;
}

float Game::getElapsedTime() const {
    return elapsedTime;
}

int Game::getKills() const {
    return kills;
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::isVictory() const {
    return victory;
}

const std::vector<XpOrb>& Game::getXpOrbs() const {
    return xpOrbs;
}
