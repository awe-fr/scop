#include "../headers/major.h"

GLuint loadBMP_custom(const char * imagepath) {
    unsigned char   header[54]; //every BMP file begin by a header (size 54)
    unsigned int    dataPos;    //pose where data begin
    unsigned int    width;
    unsigned int    height;
    unsigned int    imageSize;  // = width * height * 3
    unsigned char   *data;

    FILE    *file = fopen(imagepath, "rb");
    if (!file) {
        std::cout << "Image could not be opened" << std::endl;
        return (1); 
    }
    if (fread(header, 1, 54, file) != 54) {
        std::cout << "Not a correct BMP file" << std::endl;
        return (1);
    }
    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Not a correct BMP file" << std::endl;
        return (1);
    }
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    if (imageSize == 0) {
        imageSize = width * height * 3;
    }
    if (dataPos == 0) {
        dataPos = 54;
    }

    data = new unsigned char [imageSize];
    
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    return (0);
}

GLuint  loadTGA_glfw(const char *imagepath) {
    GLuint  textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // glfwLoadTexture2D(imagepath, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return (textureID);
}

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

GLuint  loadTGA(const char *imagepath) {
    GLuint  textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int nrChannels;
    int width;
    int height;
    unsigned char   *data = stbi_load(imagepath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum  format;
        if (nrChannels == 1) {
            format = GL_RED;
        }
        else if (nrChannels == 3) {
            format = GL_RGB;
        }
        else if (nrChannels == 4) {
            format = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return (textureID);
}