#include "texture.hpp"
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/stb_image.h"

static GLenum FormatFromChannels(int channels) {
    switch (channels) {
    case 1: return GL_RED;
    case 3: return GL_RGB;
    case 4: return GL_RGBA;
    default: return GL_RGB;
    }
}

Texture_2D::Texture_2D(const char* imagePath) {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);

        if (!data) {
            std::cout << "Failed to load texture: " << imagePath << std::endl;
            return;
        }

        GLenum format = FormatFromChannels(channels);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

Texture_2D::~Texture_2D() {
        glDeleteTextures(1, &m_TextureID);
    }

void Texture_2D::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture_2D::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture_2D::SetParameter(TextureParams param, TextureValues value) const {
    Bind(); 
        GLenum glParam = GL_TEXTURE_WRAP_S;
        GLenum glValue = GL_REPEAT;

        switch (param) {
        case TextureParams::WRAP_S:     glParam = GL_TEXTURE_WRAP_S; break;
        case TextureParams::WRAP_T:     glParam = GL_TEXTURE_WRAP_T; break;
        case TextureParams::MIN_FILTER: glParam = GL_TEXTURE_MIN_FILTER; break;
        case TextureParams::MAG_FILTER: glParam = GL_TEXTURE_MAG_FILTER; break;
        }

        switch (value) {
        case TextureValues::REPEAT:                   glValue = GL_REPEAT; break;
        case TextureValues::MIRRORED_REPEAT:          glValue = GL_MIRRORED_REPEAT; break;
        case TextureValues::CLAMP_TO_EDGE:            glValue = GL_CLAMP_TO_EDGE; break;
        case TextureValues::CLAMP_TO_BORDER:          glValue = GL_CLAMP_TO_BORDER; break;
        case TextureValues::LINEAR:                   glValue = GL_LINEAR; break;
        case TextureValues::NEAREST:                  glValue = GL_NEAREST; break;
        case TextureValues::LINEAR_MIPMAP_LINEAR:     glValue = GL_LINEAR_MIPMAP_LINEAR; break;
        case TextureValues::LINEAR_MIPMAP_NEAREST:    glValue = GL_LINEAR_MIPMAP_NEAREST; break;
        case TextureValues::NEAREST_MIPMAP_LINEAR:    glValue = GL_NEAREST_MIPMAP_LINEAR; break;
        case TextureValues::NEAREST_MIPMAP_NEAREST:   glValue = GL_NEAREST_MIPMAP_NEAREST; break;
        }

        glTexParameteri(GL_TEXTURE_2D, glParam, glValue);
    }

unsigned int Texture_2D::GetID() const {
        return m_TextureID;
    }
