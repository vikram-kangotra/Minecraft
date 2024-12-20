#include "textureManager.h"
#include <stdexcept>

const std::filesystem::path texture_dir = "../assets";

namespace {
    void configureTextureParameters() {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

std::optional<GLuint> TextureManager::createTexture(const std::filesystem::path& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        return std::nullopt;
    }

    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    if (!formattedSurface) {
        return std::nullopt;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    configureTextureParameters();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(formattedSurface);

    return textureID;
}

bool TextureManager::loadTexture(const std::string& id, const std::filesystem::path& path) {
    auto textureID = createTexture(path);
    if (!textureID.has_value()) {
        throw std::runtime_error("Failed to load texture: " + path.string() + " - " + IMG_GetError());
    }
    textures[id] = textureID.value();
    return true;
}

void TextureManager::bindTexture(const std::string& id) {
    auto it = textures.find(id);
    if (it == textures.end()) {
        auto texturePath = texture_dir / (id + ".png");
        if (!loadTexture(id, texturePath)) {
            throw std::runtime_error("Texture ID not found: " + id);
        }
        it = textures.find(id);
    }
    glBindTexture(GL_TEXTURE_2D, it->second);
}

