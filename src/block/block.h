#pragma once

#include "../shader.h"
#include "mesh.h"
#include <memory>

class Block {
public:
    Block(const glm::vec3& position, const std::string& textureID);
    virtual ~Block() {}

    static void set_mesh(std::unique_ptr<Mesh>& mesh);

    void render(const glm::mat4& view, const glm::mat4& projection);

    virtual void update() {}

    virtual Mesh& getMesh() = 0;

    GLuint createTextureBuffer(const std::vector<GLfloat>& textureCoord) {
        return getMesh().createTextureBuffer(textureCoord);
    }

protected:
    glm::vec3 position;
    glm::mat4 model;

    const std::string textureID;
};
