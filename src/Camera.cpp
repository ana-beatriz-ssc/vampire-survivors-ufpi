#include "Camera.h"
#include "Player.h"

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

void Camera::apply(const Player& player) const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        player.position.x,
        18.0f,
        player.position.z + 14.0f,
        player.position.x,
        0.0f,
        player.position.z,
        0.0f,
        1.0f,
        0.0f
    );
}
