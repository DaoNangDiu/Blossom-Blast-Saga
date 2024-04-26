#include "PlayLayer.h"
#include "Elements.h"
#include <bits/stdc++.h>
#include "GameUtils.h"
#include "code.h"
#include "BaseObject.h"
#include "Function.h"

SDL_Rect effect[10] =
{
    {0,0,600,600},
    {600*1,0,600,600},
    {600*2,0,600,600},
    {600*3,0,600,600},
    {4*600,0,600,600},
    {5*600,0,600,600},
    {6*600,0,600,600},
    {7*600,0,600,600},
    {8*600,0,600,600},
    {9*600,0,600,600},
};


const int Esize = 98;
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

bool PlayLayer::initMatrix ( int k )
{
    moves = 24;
    MATRIX_WIDTH = 8;
    MATRIX_HEIGHT = 8;
    createMatrix(MATRIX_WIDTH, MATRIX_HEIGHT);
    for ( int i = 0 ; i < MATRIX_WIDTH ; i++ )
        for ( int j = 0 ; j < MATRIX_HEIGHT ; j++ )
        {
            matrix[j][i]= rand()%5;
            square[j][i]= matrix[j][i];
        }
    return true;
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
        }
    return true;
}

int PlayLayer::exec2()
{
    auto oldTick = SDL_GetTicks();
    for ( auto done = false ; !done; )
    {
        SDL_RenderClear(renderer);
        drawMatrix2();
        int temp = score;
        SDL_Event e;
        if ( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                Mix_Chunk* gClick ;
                gClick = Mix_LoadWAV("sound/mouse_click.wav");
                if (gClick == nullptr)
                {
                    LogError("Failed to load mouse click sound", MIX_ERROR);
                }
                Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

                auto x = (e.button.x-430) / (Esize);
                auto y = (e.button.y-50) / (Esize);
                if (selectedX >= 0 && selectedY >= 0 &&
                        ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX))&&matrix[selectedX][selectedY] >=0)
                {
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
                    //draw();
                    SDL_Delay(200);
                    moves--;
                    int m1 = move1;
                    int m2 = move2;
                    move1 = moves/2;
                    move2 = (moves+1)/2;
                    if ( score == temp )
                    {
                        Mix_Chunk* gMusic = nullptr;
                        gMusic = Mix_LoadWAV("sound/fail.ogg");

                        if (gMusic == nullptr)
                        {
                            LogError("Failed to load background music", MIX_ERROR);
                        }
                        Mix_PlayChannel(MIX_CHANNEL,gMusic, NOT_REPEATITIVE);
                        std::swap (matrix[x][y],matrix[selectedX][selectedY]);
                        moves++;
                        move1 = moves/2;
                        move2 = (moves+1)/2;
                    }
                    else
                    {
                        selectedX = -1;
                        selectedY = -1;

                    }
                    if ( m1 != move1 ) score1 += (score-temp);
                    else score2 += (score-temp);
                }
                else
                {
                    selectedX = (e.button.x-430) / (Esize);
                    selectedY = (e.button.y-50) / (Esize);
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
        draw();
        drawScoreAndMove2();
        if ( score1 == score2 ) check = 0;
        else if ( score1 > score2 ) check = 1;
        else check = 2;
        if ( score != temp )
        {
            Mix_Chunk* gMusic = nullptr;
            gMusic = Mix_LoadWAV("sound/break.ogg");

            if (gMusic == nullptr)
            {
                LogError("Failed to load break music", MIX_ERROR);
            }
            Mix_PlayChannel(MIX_CHANNEL,gMusic, NOT_REPEATITIVE);

            BaseObject gEffectTexture;
            if (!gEffectTexture.LoadImg("img/Other/3.png", renderer))
            {
                std::cout << "Failed to load effect image" << std::endl;
            }

            for (int index = 0; index < 10; ++index)
            {
                gEffectTexture.Render(1050,300,renderer,&effect[index]); // Lặp lại hiệu ứng 10 lần
                SDL_Delay(50); // Thời gian trễ giữa các lần lặp
                SDL_RenderPresent(renderer); // Cập nhật màn hình
            }
            gEffectTexture.destroy();
        }
        SDL_RenderPresent(renderer);
    if (moves == 0 )
    {
        Texture last;
        if ( check == 0 )
        {
            last.loadFromFile("img/background/hoa.png");
            last.render(0,0,1600,900,NULL);
            SDL_RenderPresent(renderer);
        }
        else if ( check == 1 )
        {
            last.loadFromFile("img/background/23.png");
            last.render(0,0,1600,900,NULL);
            SDL_RenderPresent(renderer);
        }
        else
        {
            last.loadFromFile("img/background/24.png");
            last.render(0,0,1600,900,NULL);
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(20000);
        return 0;
    }
    }
    return 1;
}

int PlayLayer::exec()
{
    auto oldTick = SDL_GetTicks();
    for ( auto done = false ; !done; )
    {
        SDL_RenderClear(renderer);
        drawMatrix();
        int temp = score;
        SDL_Event e;
        if ( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                Mix_Chunk* gClick ;
                gClick = Mix_LoadWAV("sound/mouse_click.wav");
                if (gClick == nullptr)
                {
                    LogError("Failed to load mouse click sound", MIX_ERROR);
                }
                Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

                auto x = (e.button.x-430) / (Esize);
                auto y = (e.button.y-50) / (Esize);
                if (selectedX >= 0 && selectedY >= 0 &&
                        ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX))&&matrix[selectedX][selectedY] >=0)
                {
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
                    //draw();
                    SDL_Delay(200);
                    moves--;
                    if ( score == temp )
                    {
                        Mix_Chunk* gMusic = nullptr;
                        gMusic = Mix_LoadWAV("sound/fail.ogg");

                        if (gMusic == nullptr)
                        {
                            LogError("Failed to load background music", MIX_ERROR);
                        }
                        Mix_PlayChannel(MIX_CHANNEL,gMusic, NOT_REPEATITIVE);
                        std::swap (matrix[x][y],matrix[selectedX][selectedY]);
                        moves++;
                    }
                    else
                    {
                        selectedX = -1;
                        selectedY = -1;

                    }
                }
                else
                {
                    selectedX = (e.button.x-430) / (Esize);
                    selectedY = (e.button.y-50) / (Esize);
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
        draw();
        drawScoreAndMove();
        if ( targetc == 0 && targetch == 0 && targetd == 0 && targeth == 0 && targetl == 0 && targetn == 0 ) check = 1;
        else check =0;
        if ( score != temp )
        {
            Mix_Chunk* gMusic = nullptr;
            gMusic = Mix_LoadWAV("sound/break.ogg");

            if (gMusic == nullptr)
            {
                LogError("Failed to load break music", MIX_ERROR);
            }
            Mix_PlayChannel(MIX_CHANNEL,gMusic, NOT_REPEATITIVE);

            BaseObject gEffectTexture;
            if (!gEffectTexture.LoadImg("img/Other/3.png", renderer))
            {
                std::cout << "Failed to load effect image" << std::endl;
            }

            for (int index = 0; index < 10; ++index)
            {
                gEffectTexture.Render(1050,300,renderer,&effect[index]); // Lặp lại hiệu ứng 10 lần
                SDL_Delay(50); // Thời gian trễ giữa các lần lặp
                SDL_RenderPresent(renderer); // Cập nhật màn hình
            }
            gEffectTexture.destroy();
        }
        SDL_RenderPresent(renderer);
        if (moves == 0 )
        {
            Texture last;
            if ( check == 1 )
            {
                last.loadFromFile("img/background/21.png");
                last.render(0,0,1600,900,NULL);
                SDL_RenderPresent(renderer);
            }
            else
            {
                last.loadFromFile("img/background/22.png");
                last.render(0,0,1600,900,NULL);
                SDL_RenderPresent(renderer);
            }
            return 0;

        }
    }
    return 1;
}

bool PlayLayer::tick()
{
    if (ticks++ % 50 != 0)
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
                    }
                    if ( matrix[x][yy+1] != -10 && matrix[x][yy] != -10 && !( matrix[x][yy] >10 &&matrix[x][yy] <=15)  && !( matrix[x][yy+1] >10 &&matrix[x][yy+1] <=15))
                    {
                        matrix[x][yy + 1] = matrix[x][yy];
                        matrix[x][0] = -1;
                        hasHoles = true;
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

    Texture ss;
    SDL_Rect ss1= {0,0,Esize,Esize};
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if (matrix[x][y] >= 0)
            {
                if (x != selectedX || y != selectedY )
                {
                    ss.loadFromFile(elementNormal[matrix[x][y]]);
                    ss.render(Esize*x+430,Esize*y+50,Esize, Esize, &ss1);
                    ss.free();

                }
                else
                {
                    BaseObject border;
                    border.LoadImg("img/Other/border.png",renderer);
                    ss.loadFromFile(elementNormal[matrix[x][y]]);
                    ss.render(Esize*x+430,Esize*y+50,Esize,Esize,&ss1);
                    border.Render(Esize*x+430,Esize*y+50, renderer,&ss1);
                    ss.free();
                }
            }
        }
    ss.free();
//    text.destroy();
    // Move.destroy();
}

void PlayLayer::drawScoreAndMove()
{
    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/Lobster-Regular.ttf",100);
    Texture text;
    string t1 = std::to_string(score)  ;
    SDL_Color textColor = {255, 255, 255};
    text.loadFromRenderedText(t1,textColor,font);
    SDL_Rect ss2 = {0,0,20,20};
    text.render(1400, 650,50,50,NULL);
    Texture point[6];
    if ( targetch < 0 ) targetch = 0;
    if ( targeth < 0 ) targeth = 0;
    if ( targetl < 0 ) targetl = 0;
    if ( targetc < 0 ) targetc = 0;
    if ( targetn < 0 ) targetn = 0;
    if ( targetd < 0 ) targetd = 0;
    string t[6]=
    {
        std::to_string(targetch),
        std::to_string(targeth),
        std::to_string(targetl),
        std::to_string(targetc),
        std::to_string(targetn),
        std::to_string(targetd),
    };
    for (int i = 0 ; i < 6 ; i++ )
    {
        point[i].loadFromRenderedText(t[i],textColor,font);
        point[i].render(170, 135*(i+1), 40,40,NULL);
        point[i].free();
    }
    Texture textd;
    string td = std::to_string(level) ;
    textd.loadFromRenderedText(td,textColor,font);
    textd.render(1400, 230,50,50,NULL);
    textd.free();
    Texture Move;
    string s = std::to_string(moves);
    Move.loadFromRenderedText(s,textColor,font);
    Move.render(1400,430,50,50,NULL);
    text.free();
    Move.free();
}

void PlayLayer::drawScoreAndMove2()
{
    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/Lobster-Regular.ttf",100);
    Texture text1,text2;
    string t1 = std::to_string(score1)  ;
    string t2 = std::to_string(score2)  ;
    SDL_Color textColor = {255, 255, 255};
    text1.loadFromRenderedText(t1,textColor,font);
    text2.loadFromRenderedText(t2,textColor,font);
    text1.render(140, 650,50,50,NULL);
    text2.render(1400, 650,50,50,NULL);
    Texture Move1,Move2;
    string s1 = std::to_string(move1);
    string s2 = std::to_string(move2);
    Move1.loadFromRenderedText(s1,textColor,font);
    Move1.render(140,430,50,50,NULL);
    Move2.loadFromRenderedText(s2,textColor,font);
    Move2.render(1400,430,50,50,NULL);
    text1.free();
    text2.free();
    Move1.free();
    Move2.free();
}
void PlayLayer::drawMatrix()
{
    BaseObject bg;
    SDL_Rect bg_rect;
    bg_rect= {0,0,1600,900};
    bg.LoadImg("img/background/bg.png",renderer);
    bg.Render(0,0,renderer,&bg_rect);
    BaseObject ss;
    SDL_Rect ss1= {0,0,Esize,Esize};
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if ( (x+y) %2 == 0)
                ss.LoadImg("img/Other/tile64_dark.png",renderer);
            else
                ss.LoadImg("img/Other/tile64_light.png",renderer);
            if (square[x][y] >=0)
            {
                ss.Render((Esize)*(x)+430,(Esize)*(y)+50,renderer,&ss1);
            }
        }
    ss.Free();
    ss.destroy();
    bg.destroy();
}

void PlayLayer::drawMatrix2()
{
    BaseObject bg;
    SDL_Rect bg_rect;
    bg_rect= {0,0,1600,900};
    bg.LoadImg("img/background/bg2player.png",renderer);
    bg.Render(0,0,renderer,&bg_rect);
    BaseObject ss;
    SDL_Rect ss1= {0,0,Esize,Esize};
    for (int x = 0; x < MATRIX_WIDTH; ++x)
        for (int y = 0; y < MATRIX_HEIGHT; ++y)
        {
            if ( (x+y) %2 == 0)
                ss.LoadImg("img/Other/tile64_dark.png",renderer);
            else
                ss.LoadImg("img/Other/tile64_light.png",renderer);
            if (square[x][y] >=0)
            {
                ss.Render((Esize)*(x)+430,(Esize)*(y)+50,renderer,&ss1);
            }
        }
    ss.Free();
    ss.destroy();
    bg.destroy();
}
