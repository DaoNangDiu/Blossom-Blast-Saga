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
        bool tick();
        void draw1();
        void draw2();
        bool init();
        //void update();
        //void render();
        static SDL_Renderer* renderer;
        static SDL_Event event;
        //Buttons objects
    private:
        Texture* background;
        int **matrix;
        int selectedX = -1;
        int selectedY = -1;
        int width;
        int height;
        float matrixLeftBottomX;
        float matrixLeftBottomY;
        unsigned ticks = 0;
        void createMatrix(int width, int height);
        bool initMatrix();
//        void findAndRemoveLines();
        bool createAndDropElement();

       // SDL_Point positionOfItem(int row, int col);
};

#endif /* defined(__PLAY_LAYER_H__) */
