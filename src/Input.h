#pragma once

struct InputState {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool restart = false;
};

class Input {
public:
    void keyDown(unsigned char key);
    void keyUp(unsigned char key);

    const InputState& getState() const;

private:
    InputState state {};
};
