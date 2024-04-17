#pragma once

#include "game.h"

struct Player {

	float x;
	float y;

	SDL_Rect rect;

	Player();

	~Player();

	void update();
	void render(SDL_Renderer *renderer);

};
