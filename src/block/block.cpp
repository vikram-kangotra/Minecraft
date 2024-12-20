#include "block.h"
#include "../textureManager.h"
#include <glm/gtc/matrix_transform.hpp>

Block::Block(const glm::vec3& position, const std::string& textureID)
    : position(position), textureID(textureID) {

    model = glm::mat4(1);

    model = glm::scale(model, glm::vec3(0.25));
    model = glm::translate(model, position);
}

void Block::render(const glm::mat4& view, const glm::mat4& projection) {

    TextureManager::getInstance().bindTexture(textureID);

    auto shader = Shader::getShader("default");

    shader->use();

    shader->setUniform("model", model);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);

    getMesh().render();

    shader->unuse();
}
