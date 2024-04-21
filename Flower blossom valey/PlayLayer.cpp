#include "PlayLayer.h"
#include "Elements.h"
#include <bits/stdc++.h>
#include "GameUtils.h"
#include "code.h"
#include "BaseObject.h"
#include "Function.h"
const int Esize = 94;
PlayLayer::PlayLayer( SDL_Renderer *newrender)
{
    renderer= newrender;
}
PlayLayer::~PlayLayer()
{}

void PlayLayer::createMatrix(int width, int height)
{
    matrix = new int*[width];
    for ( int i=0 ; i < width ; i++ )
        matrix[i] = new int[height];
}

bool PlayLayer::init()
{
    createMatrix(MATRIX_WIDTH, MATRIX_HEIGHT);
    for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            matrix[i][j] = rand()%5;
        }
    return true;
}


int PlayLayer::exec()
{
    auto oldTick = SDL_GetTicks();
    for ( auto done = false ; !done; )
    {
        SDL_Event e;
        if ( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                auto x = (e.button.x-530) / (Esize+7);
                auto y = (e.button.y-200) / (Esize+7);
                if (selectedX >= 0 && selectedY >= 0 &&
                        ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX)))
                {
                    std::swap(matrix[x][y], matrix[selectedX][selectedY]);
                    bee2(matrix, x, y, selectedX,selectedY);
                    beeplain(matrix,x,y,selectedX,selectedY);
                    stripes2(matrix,x,y,selectedX,selectedY);
                    bee(matrix,x,y);
                    bee(matrix,selectedX,selectedY);
                    stripes(matrix,selectedX,selectedY);
                    stripes(matrix,x,y);
                    plain(matrix,x,y,score);
                    plain(matrix,selectedX,selectedY,score);
                    selectedX = -1;
                    selectedY = -1;
                    moves--;
                }
                else
                {
                    selectedX = (e.button.x-530) / (Esize+7);
                    selectedY = (e.button.y-220) / (Esize+7);
                }
            }
            break;
            case SDL_QUIT:
                done = true;
                break;
            }
        }
        auto currentTick = SDL_GetTicks();
        for (auto t = oldTick; t < currentTick; ++t)
            if (!tick())
                return 1;
        oldTick = currentTick;
        SDL_RenderClear(renderer);
        if ( moves > 18 )
        draw();
        else
        {
            if ( score <= target )

                {
                    BaseObject fn;
                    fn.LoadImg("bg.png",renderer);
                    SDL_Rect fn1{0,0,1600,900};
                    fn.Render(0,0,renderer,&fn1);
                }
        }
        SDL_RenderPresent(renderer);
    }
    return 0;
}

bool PlayLayer::tick()
{
    if (ticks++ % 200 != 0)
        return true;
    if (createAndDropElement())
        return true;
    for ( int i = 0 ; i  < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            bee(matrix,i,j);
            stripes(matrix,i,j);
            plain(matrix,i,j,score);
        }
    return true;
}


bool PlayLayer::createAndDropElement()
{
    // Create and drop
    bool hasHoles = false;
    for (auto y = MATRIX_HEIGHT - 2; y >= 0; --y)
    {
        for (auto x = 0; x < MATRIX_WIDTH; ++x)
        {
            if (matrix[x][y] != -1 && matrix[x][y + 1] == -1)
            {
                for (auto yy = y; yy >= 0; --yy)
                    matrix[x][yy + 1] = matrix[x][yy];
                matrix[x][0] = -1;
                hasHoles = true;
            }
        }
    }
    for (auto x = 0; x < MATRIX_WIDTH; ++x)
        if (matrix[x][0] == -1)
            matrix[x][0] = rand() % 5;
    return hasHoles;

}

void PlayLayer::draw()
{
    BaseObject bg;
    SDL_Rect bg_rect;
    bg_rect={0,0,1600,900};
    bg.LoadImg("img/background/bg1.png",renderer);
    bg.Render(0,0,renderer,&bg_rect);
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            BaseObject ss;
            SDL_Rect ss1={0,0,112,112};
            if ( (x+y) %2 == 0)
            ss.LoadImg("img/Other/tile64_dark.png",renderer);
            else
            ss.LoadImg("img/Other/tile64_light.png",renderer);
            ss.Render((Esize)*(x)+530+7*x,(Esize)*(y)+200+7*y,renderer,&ss1);
        }

    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if (matrix[x][y] >= 0)
            {
                if (x != selectedX || y != selectedY )
                {
                    BaseObject ss;
                    ss.LoadImg(elementNormal[matrix[x][y]],renderer);
                                SDL_Rect ss1={0,0,112,112};

                    ss.Render(Esize*x+530+7*x,Esize*y+200+7*y,renderer, &ss1);
                }
                else
                {
                    BaseObject ss;
                    SDL_Rect ss1={0,0,112,112};

                    ss.LoadImg(elementNormal[matrix[x][y]],renderer);
                    ss.Render(Esize*x+530+7*x,Esize*y+200+7*y, renderer,&ss1);
                    BaseObject border;
                    border.LoadImg("img/Other/border.png",renderer);
                    border.Render(Esize*x+530+7*x,Esize*y+200+7*y, renderer,&ss1);

                }
            }
        }
    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/Cute Dino.ttf",64);
    BaseObject text;
    string t = std::to_string(score)  ;
    SDL_Color textColor = {206, 126, 0};
    text.LoadFromRenderedText(t,font,textColor,renderer);
    SDL_Rect ss2 = {0,0,150,150};
    text.Render(150, 650,renderer,&ss2);
    BaseObject Move;
    string s = std::to_string(moves);
    Move.LoadFromRenderedText(s,font,textColor,renderer);
    Move.Render(150,370,renderer,&ss2);
}
