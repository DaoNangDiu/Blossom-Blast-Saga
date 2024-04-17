#include "titleScreen.h"
#include "PlayLayer.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;

extern bool gameRunning;

extern Game game;
extern pauseMenu pause;





titleScreen::titleScreen() {


	for (int i = 0;i < n;i++) {
		std::cout << i << std::endl;
		textBoxes[i].x = 800/2;
		textBoxes[i].y = (640-((n-1) * 100)) / 2 + i * 100;  //neatly centered :)  Some of it is done in textbox.cpp because i need the surface size
															//and I can't be bothered to change all the code to have it here
	}

	textBoxes[0].message = "Play";
	textBoxes[1].message = "Options";
	textBoxes[2].message = "Quit";

}

titleScreen::~titleScreen() {}

void titleScreen::handleEvents() { //change parameter "position"

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		gameRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			pos -= 1;
			break;
		case SDLK_DOWN:
			pos += 1;
			break;

		case SDLK_RETURN:
			if (pos == 0) { /*(title.)*/on = false;game.on = true; }
			if (pos==1) std::cout << "options" << std::endl;
			if (pos==2) gameRunning = false;
			break;

		default:
			break;
		}
		if (pos == n) pos = 0;
		if (pos < 0) pos = n - 1;

		break;


	default:
		break;
	}
}

void titleScreen::update() { //animate the option selected (change the size)

	for (int i = 0;i < n;i++) { //reset all to default
		textBoxes[i].c = {255,255,255};
		textBoxes[i].size = 24;
	}

	textBoxes[pos].c = { 255,255,0 }; //put yellow for the one selected
	textBoxes[pos].size =42;

}

void titleScreen::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderClear(renderer);
	PlayLayer bg(renderer);
    bg.draw1();
	SDL_Color White = { 255,255,255 };
	for (int i = 0;i < n;i++) {
		textBoxes[i].renderText(renderer);
	}


	SDL_RenderPresent(renderer);

}
