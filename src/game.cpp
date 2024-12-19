#include "game.h"
#include "textureManager.h"
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

Game::Game(int width, int height, const std::string& title)
    : screenWidth(width), screenHeight(height) {

    initSDL();

    window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screenWidth, screenHeight,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        throw std::runtime_error("Failed to create SDL Window: " + std::string(SDL_GetError()));
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        throw std::runtime_error("Failed to create OpenGL Context: " + std::string(SDL_GetError()));
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    TextureManager::getInstance().loadTexture("blockTexture", "../assets/texture.png");
    world.load();
}

Game::~Game() {
    cleanup();
}

void Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        throw std::runtime_error("Failed to initialize SDL image: " + std::string(IMG_GetError()));
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                running = false;
            } break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_w: camera.processKeyboard(Camera::Dir::FRONT, deltaTime); break;
                    case SDLK_DOWN:
                    case SDLK_s: camera.processKeyboard(Camera::Dir::REAR, deltaTime); break;
                    case SDLK_LEFT:
                    case SDLK_a: camera.processKeyboard(Camera::Dir::LEFT, deltaTime); break;
                    case SDLK_RIGHT:
                    case SDLK_d: camera.processKeyboard(Camera::Dir::RIGHT, deltaTime); break;
                    case SDLK_SPACE: camera.processKeyboard(Camera::Dir::UP, deltaTime); break;
                }
            } break;
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    screenWidth = event.window.data1;
                    screenHeight = event.window.data2;

                    glViewport(0, 0, screenWidth, screenHeight);
                }
            } break;
            case SDL_MOUSEMOTION: {
                camera.processMouseMovement(event.motion.xrel, -event.motion.yrel, true);
            } break;
        }
    }
}

void Game::update() {

    deltaTime = timer.calculateDeltaTime();

    world.update();
}

void Game::render() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspectRatio = (float)screenWidth / (float)screenHeight;

    world.render(aspectRatio, camera);

    SDL_GL_SwapWindow(window);
}

void Game::cleanup() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    running = true;

    while (running) {
        handleEvents();
        update();
        render();
    }
}
