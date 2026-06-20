#include "Renderer.h"

#include "Collision.h"
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"

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

bool Renderer::initialize() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);

    return floorTexture.createCheckerboard();
}

void Renderer::resize(int width, int height) {
    if (height <= 0) {
        height = 1;
    }

    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        static_cast<double>(width) / static_cast<double>(height),
        0.1,
        150.0
    );

    glMatrixMode(GL_MODELVIEW);
}

void Renderer::render(const Game& game) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.apply(game.getPlayer());
    setupLighting();

    drawArena();
    drawPlayer(game.getPlayer());

    for (const Enemy& enemy : game.getEnemies()) {
        if (!enemy.active) {
            continue;
        }

        // Visibilidade simples por distância.
        if (Collision::distanceSquaredXZ(
                game.getPlayer().position,
                enemy.position
            ) <= 45.0f * 45.0f) {
            drawEnemy(enemy);
        }
    }

    for (const Projectile& projectile : game.getProjectiles()) {
        if (projectile.active) {
            drawProjectile(projectile);
        }
    }

    hud.draw(game, windowWidth, windowHeight);
}

void Renderer::setupLighting() const {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    const GLfloat position[] = {8.0f, 18.0f, 10.0f, 1.0f};
    const GLfloat ambient[] = {0.22f, 0.22f, 0.28f, 1.0f};
    const GLfloat diffuse[] = {0.92f, 0.92f, 0.86f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}

void Renderer::drawArena() const {
    glEnable(GL_TEXTURE_2D);
    floorTexture.bind();
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);   glVertex3f(-20.0f, 0.0f, -20.0f);
        glTexCoord2f(10.0f, 0.0f);  glVertex3f(20.0f, 0.0f, -20.0f);
        glTexCoord2f(10.0f, 10.0f); glVertex3f(20.0f, 0.0f, 20.0f);
        glTexCoord2f(0.0f, 10.0f);  glVertex3f(-20.0f, 0.0f, 20.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.25f, 0.22f, 0.28f);
    const float wallHeight = 1.0f;
    const float wallThickness = 0.4f;

    glPushMatrix();
    glTranslatef(0.0f, wallHeight * 0.5f, -20.0f);
    glScalef(40.0f, wallHeight, wallThickness);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, wallHeight * 0.5f, 20.0f);
    glScalef(40.0f, wallHeight, wallThickness);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20.0f, wallHeight * 0.5f, 0.0f);
    glScalef(wallThickness, wallHeight, 40.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0f, wallHeight * 0.5f, 0.0f);
    glScalef(wallThickness, wallHeight, 40.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Renderer::drawPlayer(const Player& player) const {
    glPushMatrix();
    glTranslatef(player.position.x, player.position.y, player.position.z);

    if (player.invulnerabilityTimer > 0.0f) {
        glColor3f(1.0f, 0.9f, 0.3f);
    } else {
        glColor3f(0.25f, 0.55f, 1.0f);
    }

    glutSolidSphere(player.radius, 24, 24);
    glPopMatrix();
}

void Renderer::drawEnemy(const Enemy& enemy) const {
    glPushMatrix();
    glTranslatef(enemy.position.x, enemy.position.y, enemy.position.z);

    switch (enemy.type) {
        case EnemyType::Basic:
            glColor3f(0.85f, 0.2f, 0.22f);
            glutSolidSphere(enemy.radius, 18, 18);
            break;
        case EnemyType::Fast:
            glColor3f(0.9f, 0.55f, 0.15f);
            glutSolidSphere(enemy.radius, 16, 16);
            break;
        case EnemyType::Tank:
            glColor3f(0.55f, 0.18f, 0.7f);
            glutSolidCube(enemy.radius * 2.0f);
            break;
    }

    glPopMatrix();
}

void Renderer::drawProjectile(const Projectile& projectile) const {
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(
        projectile.position.x,
        projectile.position.y,
        projectile.position.z
    );
    glColor3f(0.35f, 1.0f, 0.95f);
    glutSolidSphere(projectile.radius, 12, 12);
    glPopMatrix();

    glPopAttrib();
}
