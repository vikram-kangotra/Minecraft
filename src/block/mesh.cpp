#include "mesh.h"
#include <fstream>
#include <filesystem>
#include <glm/glm.hpp>

Mesh::Mesh(const std::filesystem::path& objFileName) {

    loadOBJ(objFileName);

    indices_size = indices.size();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

GLuint Mesh::createTextureBuffer(const std::vector<GLfloat>& textureCoord) {

    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    return vbo;
}

void Mesh::loadOBJ(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open OBJ file: " + filePath.string());
        return;
    }

    std::vector<glm::vec3> temp_vertices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::string prefix;
        s >> prefix;

        if (prefix == "v") {
            glm::vec3 vertex;
            s >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        } else if (prefix == "f") {
            std::vector<GLuint> face_indices;
            std::string vertex_str;
            while (s >> vertex_str) {
                size_t pos = vertex_str.find('/');
                GLuint index = std::stoi(vertex_str.substr(0, pos)) - 1;
                face_indices.push_back(index);
            }

            if (face_indices.size() == 4) {

                int size = vertices.size() / 3;

                indices.push_back(size + 1);
                indices.push_back(size + 3);
                indices.push_back(size + 0);

                indices.push_back(size + 1);
                indices.push_back(size + 2);
                indices.push_back(size + 3);
            } else if (face_indices.size() == 3) {
                indices.insert(indices.end(), face_indices.begin(), face_indices.end());
            }

            for (const auto index: face_indices) {
                vertices.push_back(temp_vertices[index].x);
                vertices.push_back(temp_vertices[index].y);
                vertices.push_back(temp_vertices[index].z);
            }
        }
    }
}

void Mesh::render() {

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
