#pragma once

#include "Camera.h"
#include "HUD.h"
#include "Texture.h"

class Enemy;
class Game;
class Player;
class Projectile;

class Renderer {
public:
    bool initialize();
    void resize(int width, int height);
    void render(const Game& game);

private:
    void setupLighting() const;
    void drawArena() const;
    void drawPlayer(const Player& player) const;
    void drawEnemy(const Enemy& enemy) const;
    void drawProjectile(const Projectile& projectile) const;

    Camera camera;
    HUD hud;
    Texture floorTexture;

    int windowWidth = 1280;
    int windowHeight = 720;
};
