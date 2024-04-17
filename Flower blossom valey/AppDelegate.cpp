#include "AppDelegate.h"
#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#include "game.h"
#include "pauseMenu.h"
#include "titleScreen.h"
#include <iostream>
#include <SDL_ttf.h>
#include <chrono>
#include <SDL.h>
typedef std::chrono::high_resolution_clock Clock;
SDL_Window* window;
SDL_Renderer* renderer;
Game game;
pauseMenu pause;
titleScreen title;
bool gameRunning = false;
int FPS;
int cnt;
AppDelegate::AppDelegate() : window(nullptr), renderer(nullptr), game(), pause(), title(), FPS(0), cnt(0), gameRunning(false) {}

//AppDelegate::AppDelegate()
//{
//    srand(time(nullptr)); // Initialize random seed
//}

AppDelegate::~AppDelegate() {}
bool AppDelegate::applicationDidFinishLaunching()
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create and initialize the window
    window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600,900, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        std::cout << "creat render successful!\n";
        title.on = true;
        gameRunning = true;
    }
//
    // Create play layer
// PlayLayer playLayer(renderer);
//    if (!playLayer.init())
//   {
//        printf("Failed to initialize PlayLayer.\n");
//        return false;
//    }
    while (gameRunning)
    {
//        if (!playLayer.init())
//        {
//            printf("Failed to initialize PlayLayer.\n");
//            return false;
//        }
        auto t1 = Clock::now();
        if (game.on)
        {
            game.handleEvents();
            game.update();
            game.render(renderer);
            SDL_GetError();
        }

        if (title.on)
        {
            title.handleEvents();
            title.update();
            title.render(renderer);

        }

        if (pause.on)   //we could add game.update and/or game.render while in pause menu
        {
            pause.handleEvents();
            pause.update();
            pause.render(renderer);

        }


        auto t2 = Clock::now();


        FPS = 1000000000 / std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
        cnt++;
        if (cnt > 1000)
        {
            std::cout << FPS << " FPS" << std::endl;
            cnt = 0;
        }

    }
//  playLayer.exec();
//
// Delay to control frame rate
    SDL_Delay(10000); // 60 FPS
    // }
// Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return true;
}

void AppDelegate::applicationDidEnterBackground() {}

void AppDelegate::applicationWillEnterForeground() {}
