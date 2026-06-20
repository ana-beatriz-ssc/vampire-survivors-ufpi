#include "Game.h"

#include <algorithm>

#include "Collision.h"

void Game::initialize() {
    restart();
}

void Game::restart() {
    player.reset();
    enemies.clear();
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
    removeInactiveEntities();

    if (player.life <= 0.0f) {
        gameOver = true;
    }

    if (elapsedTime >= 300.0f) {
        victory = true;
    }
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
                }
                break;
            }
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
