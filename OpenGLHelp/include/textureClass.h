#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <glad/glad.h>

class Texture
{
public:
    unsigned int ID;
    int height;
    int width;
    int cChannels;
    unsigned char* imageData;

    Texture(const char* fileName);
};

#endif