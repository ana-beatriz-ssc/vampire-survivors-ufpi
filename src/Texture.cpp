#include "Texture.h"

#include <array>

bool Texture::createCheckerboard() {
    constexpr int size = 64;
    constexpr int channels = 3;
    std::array<unsigned char, size * size * channels> pixels {};

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            const bool alternate = ((x / 8) + (y / 8)) % 2 == 0;
            const unsigned char red = alternate ? 72 : 48;
            const unsigned char green = alternate ? 118 : 88;
            const unsigned char blue = alternate ? 65 : 44;

            const int index = (y * size + x) * channels;
            pixels[index] = red;
            pixels[index + 1] = green;
            pixels[index + 2] = blue;
        }
    }

    glGenTextures(1, &id);
    if (id == 0) {
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        size,
        size,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );

    return true;
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture::getId() const {
    return id;
}
