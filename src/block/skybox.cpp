#include "skybox.h"
#include <glm/ext/matrix_transform.hpp>

static const std::vector<GLfloat> textureCoord = {

    0.666f, 0.5f,
    0.334f, 0.5f,
    0.334f, 0.0f,
    0.666f, 0.0f,

    0.667f, 0.5f,
    0.667f, 0.0f,
    1.0f, 0.0f,
    1.0f, 0.5f,

    0.0f, 1.0f,
    0.0f, 0.5f,
    0.333f, 0.5f,
    0.333f, 1.0f,

    0.0f, 0.0f,
    0.333f, 0.0f,
    0.333f, 0.5f,
    0.0f, 0.5f,

    0.666f, 1.0f,
    0.666f, 0.5f,
    1.0f, 0.5f,
    1.0f, 1.0f,

    0.333f, 1.0f,
    0.333f, 0.5f,
    0.666f, 0.5f,
    0.666f, 1.0f,
};

GLuint Skybox::vbo;
std::unique_ptr<Mesh> Skybox::mesh;

Skybox::Skybox() : Block(glm::vec3(0), "skybox") {

    if (!mesh) {
        mesh = std::make_unique<Mesh>("../assets/cube.obj");
    }

    model = glm::scale(model, glm::vec3(450.0f));

    if (vbo == 0) {
        vbo = createTextureBuffer(textureCoord);
    }
}

void Skybox::update() {

    model = glm::rotate(model, 0.001f, glm::vec3(0, 1.0, 0));
}
