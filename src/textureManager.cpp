#include "textureManager.h"
#include <stdexcept>


bool TextureManager::loadTexture(const std::string& id, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        throw std::runtime_error("Failed to load texture: " + path + " - " + IMG_GetError());
    }

    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    if (!formattedSurface) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to convert texture format.");
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    textures[id] = textureID;

    SDL_FreeSurface(formattedSurface);
    SDL_FreeSurface(surface);

    return true;
}


void TextureManager::bindTexture(const std::string& id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        glBindTexture(GL_TEXTURE_2D, it->second);
    } else {
        throw std::runtime_error("Texture ID not found: " + id);
    }
}
