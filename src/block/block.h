#pragma once

#include "../shader.h"
#include "mesh.h"
#include <memory>

class Block {
public:
    Block(const glm::vec3& position);
    virtual ~Block() {}

    static void set_mesh(std::unique_ptr<Mesh>& mesh);

    void render(const glm::mat4& view, const glm::mat4& projection);

    virtual void update() {}

protected:
    glm::vec3 position;
    glm::mat4 model;

private:
    static std::unique_ptr<Mesh> mesh;
};
