#include "textBox.h"
#include <SDL.h>

textBox::textBox() {
	x = 0;
	y = 0;
	c = { 255,255,255 };
	message = "test";
	size = 24;
};
textBox::~textBox() {};

void textBox::renderText(SDL_Renderer *renderer) {

	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", size);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message, c);
	TTF_CloseFont(Sans);
	TTF_Quit();

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect

	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect
	Message_rect.x = x - (Message_rect.w /2);  //controls the rect's x coordinate
	Message_rect.y = y - (Message_rect.h / 2); // controls the rect's y coordinte

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
