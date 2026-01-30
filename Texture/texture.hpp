#pragma once
#include <glad/glad.h>

enum class TextureParams {
    WRAP_S,
    WRAP_T,
    MIN_FILTER,
    MAG_FILTER
};
enum class TextureValues {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    LINEAR,
    NEAREST,
    LINEAR_MIPMAP_LINEAR,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    NEAREST_MIPMAP_NEAREST
};

class Texture_2D {
public:
    Texture_2D(const char* path);
    ~Texture_2D();

    Texture_2D(const Texture_2D&) = delete;
    Texture_2D& operator=(const Texture_2D&) = delete;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    void SetParameter(TextureParams param, TextureValues value) const;
    unsigned int GetID() const;
private:
    unsigned int m_TextureID = 0;
};
