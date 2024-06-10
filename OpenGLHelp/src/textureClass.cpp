#include "../include/textureClass.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <iostream>

Texture::Texture(const char* fileName)
{
    imageData = stbi_load(fileName, &width, &height, &cChannels, 0);

    if (imageData)
    {
        unsigned int texture;
        glGenTextures(1 , &texture);

        glBindTexture(GL_TEXTURE_2D , texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load image\n";
    }
    stbi_image_free(imageData);
}
