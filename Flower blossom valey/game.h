#pragma once
#include <SDL.h>
#include <SDL_TTF.h>
#include <iostream>


struct Game {
	bool on = false;

	Game();
	~Game();

	void handleEvents();
	void update();
	void render();
};
