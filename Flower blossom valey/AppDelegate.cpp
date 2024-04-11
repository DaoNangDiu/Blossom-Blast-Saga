#include "AppDelegate.h"
#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
AppDelegate::AppDelegate() {
    srand(time(nullptr)); // Initialize random seed
}

AppDelegate::~AppDelegate() {}
bool AppDelegate::applicationDidFinishLaunching() {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create and initialize the window
    SDL_Window* window = SDL_CreateWindow("Blossom Blast Saga", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, 0);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else {
        std::cout << "creat render successful!\n";
    }

    // Create play layer
    PlayLayer playLayer(renderer);
    if (!playLayer.init()) {
        printf("Failed to initialize PlayLayer.\n");
        return false;
    }

    // Run event loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update and render PlayLayer
        playLayer.update();
        playLayer.render();

        // Delay to control frame rate
        SDL_Delay(16); // 60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return true;
}

void AppDelegate::applicationDidEnterBackground() {}

void AppDelegate::applicationWillEnterForeground() {}
