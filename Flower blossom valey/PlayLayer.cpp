#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#include <bits/stdc++.h>
#define MATRIX_WIDTH (10)
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
    std::cout << MATRIX_WIDTH << " " << MATRIX_HEIGHT << std::endl;
    createMatrix(MATRIX_WIDTH, MATRIX_HEIGHT);

     for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
    {
        matrix[i][j] = rand()%5;
    }


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

    Texture bg;
    bg.loadFromFile("bg.png");
    bg.render(0,0,1600,900,NULL);
//    int k = 0;
    for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            Texture ss;
            //std::cout << elementNormal[matrix[i][j]] << std::endl;
            ss.loadFromFile(elementNormal[matrix[i][j]]);
            ss.render(105*i+220+7*i,105*j+170+7*j,100,100,NULL);
        }
//    // Update screen
    SDL_RenderPresent(renderer);
}



void PlayLayer::createAndDropElement(int width, int height)
{
    // Create and drop sushi


}

SDL_Point PlayLayer::positionOfItem(int row, int col)
{

}
