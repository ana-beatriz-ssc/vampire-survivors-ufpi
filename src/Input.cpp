#include "Input.h"

void Input::keyDown(unsigned char key) {
    switch (key) {
        case 'w':
        case 'W': state.up = true; break;
        case 's':
        case 'S': state.down = true; break;
        case 'a':
        case 'A': state.left = true; break;
        case 'd':
        case 'D': state.right = true; break;
        case 'r':
        case 'R': state.restart = true; break;
        default: break;
    }
}

void Input::keyUp(unsigned char key) {
    switch (key) {
        case 'w':
        case 'W': state.up = false; break;
        case 's':
        case 'S': state.down = false; break;
        case 'a':
        case 'A': state.left = false; break;
        case 'd':
        case 'D': state.right = false; break;
        case 'r':
        case 'R': state.restart = false; break;
        default: break;
    }
}

const InputState& Input::getState() const {
    return state;
}
