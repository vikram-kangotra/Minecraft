#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <vector>

class Mesh {
public:
    Mesh(const std::filesystem::path& objFileName);
    ~Mesh();

    void render();

    GLuint createTextureBuffer(const std::vector<GLfloat>& textureCoord);

private:

    void loadOBJ(const std::filesystem::path& filePath);

    GLuint indices_size;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
};
