#pragma once

#include "camera.h"
#include "timer.h"
#include "world.h"
#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Game {
public:
    Game(int width, int height, const std::string& title);
    ~Game();

    void run();

private:

    void initSDL();
    void handleEvents();
    void update();
    void render();

    void cleanup();

    SDL_Window* window;
    SDL_GLContext context;

    int screenWidth;
    int screenHeight;
    bool running;

    Timer timer;
    Camera camera;

    float deltaTime;

    World world;
};
