#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__

#include "SDL.h"
#include "Elements.h"
#include "texture.h"
#include<bits/stdc++.h>
using namespace std;

extern vector<vector<SDL_Rect>> rect_table;

class PlayLayer
{
public:
    PlayLayer(SDL_Renderer* renderer);
    ~PlayLayer();
    int exec();
    int exec2();
    bool tick();
    void draw();
    int Moves;
    int check = 0;
    void draw2();
    bool init(int i);
    bool initMatrix( int i);
    //void update();
    //void render();
    static SDL_Renderer* renderer;
    static SDL_Event event;
    //Buttons objects
private:
    Texture* background;
    int **matrix;
    int **square;
    int selectedX = -1;
    int selectedY = -1;
    int width;
    int height;
    int score1 = 0;
    int score2 = 0;
    float matrixLeftBottomX;
    float matrixLeftBottomY;
    unsigned ticks = 0;
    void createMatrix(int width, int height);
//        void findAndRemoveLines();
    bool createAndDropElement();
    void drawMatrix();
    void drawMatrix2();
    void drawScoreAndMove();
    void drawScoreAndMove2();
    void LoadMedia();
    // SDL_Point positionOfItem(int row, int col);
};

#endif /* defined(__PLAY_LAYER_H__) */
