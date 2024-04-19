#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#include <bits/stdc++.h>
#include "Function.h"
#include "GameUtils.h"
#include <bits/stdc++.h>
const int Esize = 94;

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

void PlayLayer::draw2()
{
    Texture bg;
    bg.loadFromFile("bg1.png");
    bg.render(0,0,1600, 900,NULL);
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            Texture ss;
            ss.loadFromFile("o1.png");
            ss.render((Esize)*(x)+530+7*x,(Esize)*(y)+200+7*y,98,98,NULL);
        }

    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if (matrix[x][y] >= 0)
            {
                if (x != selectedX || y != selectedY )
                {
                    Texture ss;
                    ss.loadFromFile(elementNormal[matrix[x][y]]);
                    ss.render(Esize*x+530+7*x,Esize*y+200+7*y, 98,98,NULL);
                }
                else
                {
                    Texture ss;
                    ss.loadFromFile(elementNormal[matrix[x][y]]);
                    ss.render(Esize*x+530+7*x,Esize*y+200+7*y, 98,98,NULL);
                    Texture border;
                    border.loadFromFile("5.png");
                    border.render(Esize*x+530+7*x,Esize*y+200+7*y, 98,98,NULL);

                }
            }
        }
    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/Pacifico.ttf",24);
    Texture text;
    string t = std::to_string(score)  ;
    text.loadString("font/Pacifico.ttf",t,font);
    SDL_Color textColor = {139, 69, 19};
    text.setColor(textColor.r, textColor.g, textColor.b);
    text.render(150, 620,100,100,NULL);
}

