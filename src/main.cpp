#include "game.h"
#include <iostream>
#include <stdexcept>

int main() {

    const int width = 1400;
    const int height = width * 9.0f / 16.0f;

    try {
        Game game(width, height, "Minecraft");
        game.run();
    } catch (std::runtime_error& err) {
        std::cout << err.what();
    }

    return 0;
}
