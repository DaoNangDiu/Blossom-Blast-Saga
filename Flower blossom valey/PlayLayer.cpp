#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#include <bits/stdc++.h>
#include "Function.h"

const int Esize = 105;

vector<vector<SDL_Rect>> rect_table;

PlayLayer::PlayLayer(SDL_Renderer* newRender)
{
    renderer = newRender;
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
    // Initialize matrix
    //std::cout << MATRIX_WIDTH << " " << MATRIX_HEIGHT << std::endl;
    createMatrix(MATRIX_WIDTH, MATRIX_HEIGHT);

    int x = 220, y = 170;

    rect_table.resize(6, vector<SDL_Rect>(11));

    for(int i = 0; i < 5; i ++)
    {
        for(int j = 0; j < 10; j ++)
        {
            SDL_Rect tmp = {x, y, 112, 112};
            rect_table[i][j] = tmp;
            x += 112;
        }
        y += 112;
    }

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
                auto x = (e.button.x-220) / (Esize+7);
                auto y = (e.button.y-170) / (Esize+7);
                if (selectedX >= 0 && selectedY >= 0 &&
                        ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX)))
                {
                    std::swap(matrix[x][y], matrix[selectedX][selectedY]);
                    bee2(matrix, x, y, selectedX,selectedY);
                    beeplain(matrix,x,y,selectedX,selectedY);
                    {
                        bee(matrix,x,y);
                        stripes(matrix,x,y);
                        plain(matrix,x,y);
                    }
                    stripes2(matrix,x,y,selectedX,selectedY);
                    if ( matrix[selectedX][selectedY] < 5 )
                    {
                        bee(matrix,selectedX,selectedY);
                        stripes(matrix,selectedX,selectedY);
                        plain(matrix,selectedX,selectedY);
                    }
                    selectedX = -1;
                    selectedY = -1;
                }
                else
                {
                    selectedX = (e.button.x-220) / (Esize+7);
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
//        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x06);
        SDL_RenderClear(renderer);
        draw2();
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

void PlayLayer::draw2()
{
//   SDL_RenderClear(renderer);
    Texture bg;
    bg.loadFromFile("bg.png");
    bg.render(0,0,1600, 900,NULL);
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if (matrix[x][y] >= 0)
            {
                if (x != selectedX || y != selectedY || SDL_GetTicks() % 250 > 125)
                {
                    Texture ss;
                    ss.loadFromFile(elementNormal[matrix[x][y]]);
                    ss.render(Esize*x+220+7*x,Esize*y+170+7*y,100,100,NULL);
                }
            }
        }
}

void PlayLayer::draw1()
{
    SDL_RenderClear(renderer);
    Texture background;
    background.loadFromFile("background.png");
    background.render(0,0,1600, 900,NULL);
    SDL_RenderPresent(renderer);

}
