#pragma once

#include "block/block.h"
#include "camera.h"
#include <memory>
#include <vector>

class World {
public:
    World() {}
    ~World() {}

    void load();

    void update();
    void render(float aspectRatio, Camera& camera);

private:
    void generateTerrain(int width, int depth, float frequency, float heightScale);

    std::vector<std::unique_ptr<Block>> blocks;
};
