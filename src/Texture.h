#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Texture {
public:
    bool createCheckerboard();
    void bind() const;
    GLuint getId() const;

private:
    GLuint id = 0;
};
