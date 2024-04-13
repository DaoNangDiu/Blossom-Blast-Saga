#include <SDL.h>
#include <SDL_image.h>
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render(SDL_Renderer* screen, SDL_Texture* Tex);

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
//		LButtonSprite mCurrentSprite;
};
