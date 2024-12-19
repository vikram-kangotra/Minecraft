#pragma once

#include "block.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>

class DirtBlock : public Block {
public:
    DirtBlock(const glm::vec3& position);
    ~DirtBlock() {}

    void update() {
        //model = glm::rotate(model, 0.01f, glm::vec3(1.0, 1.0, 1.0));
    }

private:
    void createTextureBuffer();

private:
    static GLuint vbo;
};
