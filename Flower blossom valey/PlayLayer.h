#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__

#include "SDL.h"
#include "Elements.h"
#include "texture.h"
#include<bits/stdc++.h>

class PlayLayer
{
public:
    PlayLayer(SDL_Renderer* renderer);
    ~PlayLayer();
    bool init();
    void update();
    void render();
    static SDL_Renderer* renderer;
    static SDL_Event event;

private:
    Texture* background;
    int** matrix;
    int width;
    int height;
    float matrixLeftBottomX;
    float matrixLeftBottomY;
    void createMatrix(int width, int height);
    void initMatrix();
    void createAndDropSushi(int width, int height);
    SDL_Point positionOfItem(int row, int col);
};

#endif /* defined(__PLAY_LAYER_H__) */
