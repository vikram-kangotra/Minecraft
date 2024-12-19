#pragma once

#include <SDL2/SDL.h>

class Timer {
public:
    Timer() {
        lastTime = SDL_GetTicks();
    }

    float calculateDeltaTime() {
        Uint32 currentTime = SDL_GetTicks();

        float deltaTime = (currentTime - lastTime) / 1000.0f;

        lastTime = currentTime;
        return deltaTime;
    }

private:
    Uint32 lastTime;
};
