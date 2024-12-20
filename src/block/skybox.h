#pragma once

#include "block.h"

class Skybox : public Block {
public:
    Skybox();
    ~Skybox() override {}

    void update() override;

    Mesh& getMesh() override { return *mesh; }

private:
    static GLuint vbo;
    static std::unique_ptr<Mesh> mesh; 
};
