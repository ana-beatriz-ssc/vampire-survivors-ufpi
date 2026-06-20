#pragma once

class Player;

class Camera {
public:
    void apply(const Player& player) const;
};
