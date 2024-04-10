#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#define MATRIX_WIDTH (5)
#define MATRIX_HEIGHT (5)
#define ELEMENT_GAP (1)

PlayLayer::PlayLayer(SDL_Renderer* newRender)
//    : renderer(renderer),
 //    background(nullptr),
     // width(MATRIX_WIDTH),
     // height(MATRIX_HEIGHT)
     // matrixLeftBottomX(0),
     // matrixLeftBottomY(0)
{
    renderer = newRender;
}
PlayLayer::~PlayLayer()
{
}

void PlayLayer::createMatrix(int width, int height)
{
    matrix = new int*[width];
    for ( int i=0 ; i < width ; i++ )
        matrix[i] = new int[height];
}

bool PlayLayer::init()
{
   /* // Load background texture
    SDL_Surface* surface = SDL_LoadBMP("bg.bmp");
    if (!surface)
    {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);*/

    // Initialize matrix
    initMatrix();

    return true;
}

void PlayLayer::update()
{
    // Update game logic here
}

void PlayLayer::render()
{
    // Clear screen
    SDL_RenderClear(renderer);

    /*// Render background
    SDL_RenderCopy(renderer, background, NULL, NULL);

    // Render matrix
    for (auto& row : matrix)
    {
        for (auto& sushi : row)
        {
            SDL_Rect dstRect = { sushi.getX(), sushi.getY(), sushi.getWidth(), sushi.getHeight() };
            SDL_RenderCopy(renderer, sushi.getTexture(), NULL, &dstRect);
        }
    }*/
    for ( int i = 0 ; i < width ; i++ )
        for ( int j = 0 ; j < height ; j++ )
    {
        matrix[i][j] = rand()%5;
    }
    Texture bg;
    bg.loadFromFile("background.png");
    bg.render(0,0,1600,900,NULL);
    Texture ss[MATRIX_WIDTH*MATRIX_HEIGHT];
    int k = 0;
    for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            Texture ss[k];
            ss[k].loadFromFile(elementNormal[matrix[i][j]]);
            ss[k].render(32*i+10,32*j+10,32,32,NULL);
    // Update screen
    SDL_RenderPresent(renderer);
}
}

void PlayLayer::initMatrix()
{
    // Initialize matrix
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            createAndDropElement(row, col);
        }
    }
}

void PlayLayer::createAndDropElement(int width, int height)
{

    // Create and drop sushi

}

SDL_Point PlayLayer::positionOfItem(int row, int col)
{

}
