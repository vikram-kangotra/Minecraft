#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    bool loadTexture(const std::string& id, const std::string& path);
    void bindTexture(const std::string& id);

private:
    TextureManager() {}
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

    std::unordered_map<std::string, GLuint> textures;
};
