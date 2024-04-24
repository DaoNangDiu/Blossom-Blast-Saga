#include "PlayLayer.h"
#include "Elements.h"
#include <bits/stdc++.h>
#include "GameUtils.h"
#include "code.h"
#include "BaseObject.h"
#include "Function.h"


SDL_Rect effect[10] =
{
    {0,0,360,360},
    {360*1,0,360,360},
    {360*2,0,360,360},
    {360*3,0,360,360},
    {4*360,0,360,360},
    {5*360,0,360,360},
    {6*360,0,360,360},
    {7*360,0,360,360},
    {8*360,0,360,360},
    {9*360,0,360,360},
};


const int Esize = 112;
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
    square = new int*[width];
    for ( int i = 0 ; i < width ; i++ )
        square[i] = new int[height];
}

bool PlayLayer::init( int k )
{
    nhapfile(k);
    createMatrix(MATRIX_WIDTH, MATRIX_HEIGHT);
    for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            f >> matrix[j][i];
            square[j][i]= matrix[j][i];
//            matrix[i][j] = rand()%5;
        }
    return true;
}


int PlayLayer::exec( int i )
{
    BaseObject gEffectTexture;

    Mix_Chunk* gClick = nullptr;
    gClick = Mix_LoadWAV("sound/mouse_click.wav");
    if (gClick == nullptr)
    {
        LogError("Failed to load mouse click sound", MIX_ERROR);
    }
    auto oldTick = SDL_GetTicks();
    for ( auto done = false ; !done; )
    {
        SDL_RenderClear(renderer);
        drawMatrix();
        SDL_Event e;
        if ( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

                auto x = (e.button.x-430) / (Esize);
                auto y = (e.button.y-10) / (Esize);
                if (selectedX >= 0 && selectedY >= 0 &&
                        ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX))&&matrix[selectedX][selectedY] >=0)
                {
                    int temp = score;
                    std::swap(matrix[x][y], matrix[selectedX][selectedY]);
                    bee2(matrix, x, y, selectedX,selectedY);
                    beeplain(matrix,x,y,selectedX,selectedY);
                    stripes2(matrix,x,y,selectedX,selectedY);
                    bee(matrix,x,y);
                    bee(matrix,selectedX,selectedY);
                    stripes(matrix,selectedX,selectedY);
                    stripes(matrix,x,y);
                    plain(matrix,x,y);
                    plain(matrix,selectedX,selectedY);
                    draw();
                    SDL_Delay(200);
                    moves--;
                    if ( score == temp )
                    {

                        std::swap (matrix[x][y],matrix[selectedX][selectedY]);
                        moves++;
                        SDL_Delay(100);
                    }
                    else
                    {
                        int index = 0;
                        while(index < 10)
                        {
                            if (!gEffectTexture.LoadImg("img/Other/2.png", renderer))
                            {
                                std::cout << "Failed to load help_button image" << std::endl;
                            }
                            gEffectTexture.Render(430+x*120,10+y*120,renderer,&effect[index]);
                            index++;
                        }
                        gEffectTexture.destroy();
                    }
                    selectedX = -1;
                    selectedY = -1;

                }
                else
                {
                    selectedX = (e.button.x-430) / (Esize);
                    selectedY = (e.button.y-10) / (Esize);
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
        if ( moves < 18 )
        {
            draw();
        }
        else
        {
            if ( score <= target )

            {
                BaseObject fn;
                fn.LoadImg("bg.png",renderer);
                SDL_Rect fn1{0,0,1760,990};
                fn.Render(0,0,renderer,&fn1);

            }
        }
        SDL_RenderPresent(renderer);
    }
     gClick = nullptr;

    return 0;
}

bool PlayLayer::tick()
{
    if (ticks++ % 10 != 0)
        return true;
    if (createAndDropElement())
        return true;
    for ( int i = 0 ; i  < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            bee(matrix,i,j);
            stripes(matrix,i,j);
            plain(matrix,i,j);
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
            if (matrix[x][y] >= 0 && matrix[x][y + 1] == -1)
            {
                for (auto yy = y; yy >= 0; --yy)
                {
                    if ( matrix[x][yy+1] != -10 && matrix[x][yy] != -10 && matrix[x][yy-1]==-10  && !( matrix[x][yy] >10 &&matrix[x][yy] <=15)  && !( matrix[x][yy+1] >10 &&matrix[x][yy+1] <=15))
                    {
                        matrix[x][yy + 1] = matrix[x][yy];
                        matrix[x][yy] = -1;
                        hasHoles = true;
                        SDL_Delay(20);
                    }
                    if ( matrix[x][yy+1] != -10 && matrix[x][yy] != -10 && !( matrix[x][yy] >10 &&matrix[x][yy] <=15)  && !( matrix[x][yy+1] >10 &&matrix[x][yy+1] <=15))
                    {
                        matrix[x][yy + 1] = matrix[x][yy];
                        matrix[x][0] = -1;
                        hasHoles = true;
                        SDL_Delay(20);
                    }
                }
            }
        }
    }
    for (auto x = 0; x < MATRIX_WIDTH; ++x)
        for ( auto y = 0 ; y < MATRIX_HEIGHT ; ++y )
            if (matrix[x][y] == -1)
            {
                matrix[x][y] = rand() % 5;
            }
    return hasHoles;

}

void PlayLayer::draw()
{

    BaseObject ss;
    SDL_Rect ss1= {0,0,112,112};
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if (matrix[x][y] >= 0)
            {
                if (x != selectedX || y != selectedY )
                {
                    ss.LoadImg(elementNormal[matrix[x][y]],renderer);
                    ss.Render(Esize*x+430,Esize*y+10,renderer, &ss1);
                    ss.destroy();

                }
                else
                {


                    ss.LoadImg(elementNormal[matrix[x][y]],renderer);
                    ss.Render(Esize*x+430,Esize*y+10, renderer,&ss1);
                    BaseObject border;
                    border.LoadImg("img/Other/border.png",renderer);
                    border.Render(Esize*x+430,Esize*y+10, renderer,&ss1);
                    ss.destroy();
                }
            }
        }
    ss.Free();
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
    text.Free();
    Move.Free();
    text.destroy();
    Move.destroy();
}

void PlayLayer::drawMatrix()
{
    BaseObject bg;
    SDL_Rect bg_rect;
    bg_rect= {0,0,1600,900};
    bg.LoadImg("img/background/bg2.png",renderer);
    bg.Render(0,0,renderer,&bg_rect);
    BaseObject ss;
    SDL_Rect ss1= {0,0,112,112};
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if ( (x+y) %2 == 0)
                ss.LoadImg("img/Other/tile64_dark.png",renderer);
            else
                ss.LoadImg("img/Other/tile64_light.png",renderer);
            if (square[x][y] >=0)
            {
                ss.Render((Esize)*(x)+430,(Esize)*(y)+10,renderer,&ss1);
            }
        }
    ss.Free();
    ss.destroy();
    bg.destroy();
}
