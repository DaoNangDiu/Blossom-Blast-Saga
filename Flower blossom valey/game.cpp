#include "game.h"
#include "player.h"
#include "titleScreen.h"
#include "AppDelegate.h"
extern bool gameRunning;
extern titleScreen title;
extern pauseMenu pause;

const Uint8* keyStates = SDL_GetKeyboardState(NULL);
 //Key States

Player player;

Game::Game() {


};
Game::~Game() {};



void Game::handleEvents() {

	SDL_Event event; //Event handling



	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
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
	if (keyStates[SDL_SCANCODE_DOWN]) {
		player.y += s;
	}
	if (keyStates[SDL_SCANCODE_UP]) {
		player.y -= s;
	}
	if (keyStates[SDL_SCANCODE_LEFT]) {
		player.x -= s;
	}
	if (keyStates[SDL_SCANCODE_RIGHT]) {
		player.x += s;
	}
};

void Game::update() {
	player.update();
};

void Game::render( SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 60, 255);
	SDL_RenderClear(renderer);

	player.render(renderer);

	SDL_RenderPresent(renderer);
};

