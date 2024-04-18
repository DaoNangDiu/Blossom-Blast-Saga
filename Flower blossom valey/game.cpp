#include "game.h"
#include "player.h"
#include "titleScreen.h"
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool gameRunning;
extern titleScreen title;
extern pauseMenu pause;

const Uint8* keyStates = SDL_GetKeyboardState(NULL);
//Key States

Player player;

Game::Game()
{


};
Game::~Game() {};



void Game::handleEvents()
{

    SDL_Event event; //Event handling



    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        gameRunning = false;
        break;

    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cout << "t" << std::endl;
            /*(game.)*/on = false;
            pause.on = true;
        }
        break;
    default:
        break;

    }

    //Keystate handling
    double s = 0.08;
    if (keyStates[SDL_SCANCODE_DOWN])
    {
        player.y += s;
    }
    if (keyStates[SDL_SCANCODE_UP])
    {
        player.y -= s;
    }
    if (keyStates[SDL_SCANCODE_LEFT])
    {
        player.x -= s;
    }
    if (keyStates[SDL_SCANCODE_RIGHT])
    {
        player.x += s;
    }
};

void Game::update()
{
    player.update();
};

void Game::render()
{
    PlayLayer playLayer(renderer);
    if (!playLayer.init())
    {
        printf("Failed to initialize PlayLayer.\n");
    }
    playLayer.exec();
};

