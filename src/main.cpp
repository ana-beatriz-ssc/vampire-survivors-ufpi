#ifdef __APPLE__ // MacOS
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else // Windows e Linux
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cstdlib>

// var globais
float playerZ = 0.0f;
float playerX = 0.0f;
float playerSpeed = 0.3f;

bool keys[256];

void initOpenGL(){
    glEnable(GL_DEPTH_TEST);

    // tom levemente azulado
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
}

void drawFloor(){
    glColor3f(0.2f, 0.45f, 0.2f);

    glBegin(GL_QUADS);
        glVertex3f(-20.0f, 0.0f, -20.0f);
        glVertex3f(20.0f, 0.0f, -20.0f);
        glVertex3f(20.0f, 0.0f, 20.0f);
        glVertex3f(-20.0f, 0.0f, 20.0f);
    glEnd();
}

void drawPlayer(){
    glColor3f(0.5f, 0.3f, 0.0f);

    glPushMatrix();
        glTranslatef(playerX, 0.5f, playerZ);
        glutSolidSphere(0.5, 24, 24);
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // config cam e pos dos objetos
    glLoadIdentity();

    gluLookAt(
        playerX, 18.0f, playerZ + 14.0f,
        playerX, 0.0f, playerZ,
        0.0f, 1.0f, 0.f
    );

    drawFloor();
    drawPlayer();

    glutSwapBuffers();
}

void update(int value){
    if(keys['w'] || keys['W']) {playerZ -= playerSpeed;}
    if(keys['s'] || keys['S']) {playerZ += playerSpeed;}
    if(keys['a'] || keys['A']) {playerX -= playerSpeed;}
    if(keys['d'] || keys['D']) {playerX += playerSpeed;}

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

void reshape(int width, int height){
    if (height == 0){
        height = 1;
    }

    float aspect = (float) width / (float) height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, aspect, 0.1f, 100.f);
}

void keyDown(unsigned char key, int x, int y){
    keys[key] = true;

    if (key == 27){
        exit(0);
    }
}

void keyUp (unsigned char key, int x, int y){
    keys[key] = false;
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);

    glutCreateWindow("Vampire Survivors Jogo CG");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
