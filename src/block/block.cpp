#include "block.h"
#include "../textureManager.h"
#include <glm/gtc/matrix_transform.hpp>

std::unique_ptr<Mesh> Block::mesh;

Block::Block(const glm::vec3& position)
    : position(position) {

    model = glm::mat4(1);

    model = glm::scale(model, glm::vec3(0.25));
    model = glm::translate(model, position);
}

void Block::set_mesh(std::unique_ptr<Mesh>& m) {
    mesh = std::move(m);
}

void Block::render(const glm::mat4& view, const glm::mat4& projection) {

    TextureManager::getInstance().bindTexture("blockTexture");

    auto shader = Shader::getShader("default");

    shader->use();

    shader->setUniform("model", model);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);

    mesh->render();

    shader->unuse();
}
