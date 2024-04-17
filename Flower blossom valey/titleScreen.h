#pragma once

#include <SDL.h>
#include "textBox.h"
#include "pauseMenu.h"
#include "game.h"
#include <iostream>



struct titleScreen {
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];

	bool on = false;


	titleScreen();
	~titleScreen();

	void update();
	void render(SDL_Renderer *renderer);
	void handleEvents();


};
