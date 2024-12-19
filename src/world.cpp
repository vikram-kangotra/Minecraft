#include "world.h"
#include "block/dirtBlock.h"
#include <glm/gtc/noise.hpp>
#include <memory>

void World::load() {

    auto mesh = std::make_unique<Mesh>("../assets/cube.obj");
    Block::set_mesh(mesh);

    for (int i = -20; i <= 20; i++) {
        for (int k = -20; k <= 20; k++) {
            blocks.push_back(std::make_unique<DirtBlock>(glm::vec3(i, 0, k)));
        }
    }

    generateTerrain(200, 200, 0.07f, 5.0f);
}

void World::update() {
    for (auto& block: blocks) {
        block->update();
    }
}

void World::render(float aspectRatio, Camera& camera) {

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);

    for (auto& block: blocks) {
        block->render(view, projection);
    }

}

void World::generateTerrain(int width, int depth, float scale, float heightMultiplier) {
    for (int x = -width / 2; x <= width / 2; x++) {
        for (int z = -depth / 2; z <= depth / 2; z++) {
            float height = glm::perlin(glm::vec2(x * scale, z * scale)) * heightMultiplier;
            int roundedHeight = static_cast<int>(std::round(height));
            blocks.push_back(std::make_unique<DirtBlock>(glm::vec3(x, roundedHeight, z)));
        }
    }
}
