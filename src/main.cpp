#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cstdlib>
#include <iostream>

#include "Game.h"
#include "Input.h"
#include "Renderer.h"

namespace {
Game game;
Input input;
Renderer renderer;
float lastTime = 0.0f;

void display() {
    renderer.render(game);
    glutSwapBuffers();
}

void reshape(int width, int height) {
    renderer.resize(width, height);
}

void update(int) {
    const float currentTime =
        static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Evita saltos grandes após travamento ou movimentação da janela.
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    game.update(input.getState(), deltaTime);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyDown(unsigned char key, int, int) {
    if (key == 27) {
        std::exit(EXIT_SUCCESS);
    }

    input.keyDown(key);
}

void keyUp(unsigned char key, int, int) {
    input.keyUp(key);
}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Vampire Survivors - Trabalho de CG");

    if (!renderer.initialize()) {
        std::cerr << "Nao foi possivel inicializar o Renderer.\n";
        return EXIT_FAILURE;
    }

    game.initialize();
    lastTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return EXIT_SUCCESS;
}
