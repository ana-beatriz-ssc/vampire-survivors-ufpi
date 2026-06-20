#include "HUD.h"
#include "Game.h"

#include <cstdio>

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

void HUD::draw(const Game& game, int windowWidth, int windowHeight) const {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);

    char line[128];
    std::snprintf(
        line,
        sizeof(line),
        "Vida: %.0f / %.0f",
        game.getPlayer().life,
        game.getPlayer().maxLife
    );
    drawText(20.0f, windowHeight - 30.0f, line);

    std::snprintf(
        line,
        sizeof(line),
        "Tempo: %.1f s | Abates: %d | Inimigos: %zu",
        game.getElapsedTime(),
        game.getKills(),
        game.getEnemies().size()
    );
    drawText(20.0f, windowHeight - 55.0f, line);

    drawText(20.0f, 25.0f, "WASD: mover | ESC: sair | R: reiniciar apos o fim");

    if (game.isGameOver()) {
        glColor3f(1.0f, 0.35f, 0.35f);
        drawText(
            windowWidth * 0.5f - 85.0f,
            windowHeight * 0.5f,
            "GAME OVER - pressione R"
        );
    } else if (game.isVictory()) {
        glColor3f(0.4f, 1.0f, 0.5f);
        drawText(
            windowWidth * 0.5f - 70.0f,
            windowHeight * 0.5f,
            "VITORIA - pressione R"
        );
    }

    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void HUD::drawText(float x, float y, const char* text) const {
    glRasterPos2f(x, y);
    for (const char* character = text; *character != '\0'; ++character) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *character);
    }
}
