#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <optional>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    void bindTexture(const std::string& id);

private:
    TextureManager() {}
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

    bool loadTexture(const std::string& id, const std::filesystem::path& path);

    std::optional<GLuint> createTexture(const std::filesystem::path& path);

    std::unordered_map<std::string, GLuint> textures;
};
