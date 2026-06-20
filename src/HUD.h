#pragma once

class Game;

class HUD {
public:
    void draw(const Game& game, int windowWidth, int windowHeight) const;

private:
    void drawText(float x, float y, const char* text) const;
};
