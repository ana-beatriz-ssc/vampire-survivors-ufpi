#pragma once

#include <vector>

#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include "Projectile.h"
#include "WaveManager.h"
#include "Weapon.h"

class Game {
public:
    void initialize();
    void restart();
    void update(const InputState& input, float deltaTime);

    const Player& getPlayer() const;
    const std::vector<Enemy>& getEnemies() const;
    const std::vector<Projectile>& getProjectiles() const;

    float getElapsedTime() const;
    int getKills() const;
    bool isGameOver() const;
    bool isVictory() const;

private:
    void checkCollisions();
    void separateEnemies();
    void removeInactiveEntities();

    Player player;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;

    Weapon weapon;
    WaveManager waveManager;

    float elapsedTime = 0.0f;
    int kills = 0;
    bool gameOver = false;
    bool victory = false;
};
