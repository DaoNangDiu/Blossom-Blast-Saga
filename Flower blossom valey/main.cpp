#include "CommonFunc.h"
#include "BaseObject.h"
#include "PlayLayer.h"
#include "Elements.h"
#include "texture.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include "GameUtils.h"
#include "Button.h"
#include<bits/stdc++.h>
//#include "Function.h"
BaseObject g_background;


SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gLevel1Button[BUTTON_TOTAL];
SDL_Rect gLevel2Button[BUTTON_TOTAL];
SDL_Rect gLevel3Button[BUTTON_TOTAL];
SDL_Rect gLevel4Button[BUTTON_TOTAL];
SDL_Rect gSnail[11]=
{
    {0, 0, 213, 120},
    {213, 0, 213, 120},
    {213*2, 0, 213, 120},
    {213*3, 0, 213, 120},
    {213*4, 0, 213, 120},
    {213*5, 0, 213, 120},
    {213*6, 0, 213, 120},
    {213*7, 0, 213, 120},
    {213*8, 0, 213, 120},
    {213*9, 0, 213, 120},
    {213*10, 0, 213, 120},
};

BaseObject gMenuTexture;
BaseObject gInstructionTexture;
BaseObject gCharacterTexture;
BaseObject gGroundTexture;
BaseObject gPlayButtonTexture;
BaseObject gHelpButtonTexture;
BaseObject gExitButtonTexture;
BaseObject gBackButtonTexture;
BaseObject gPauseButtonTexture;
BaseObject gContinueButtonTexture;
BaseObject gLoseTexture;
BaseObject gText1Texture;
BaseObject gScoreTexture;
BaseObject gText2Texture;
BaseObject gHighScoreTexture;
BaseObject gLevel1ButtonTexture;
BaseObject gLevel2ButtonTexture;
BaseObject gLevel3ButtonTexture;
BaseObject gLevel4ButtonTexture;
BaseObject gLevelMenuTexture;
BaseObject gSnailTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button Level1Button (LEVEL1_BUTTON_POSX, LEVEL1_BUTTON_POSY);
Button Level2Button (LEVEL2_BUTTON_POSX, LEVEL2_BUTTON_POSY);
Button Level3Button (LEVEL3_BUTTON_POSX, LEVEL3_BUTTON_POSY);
Button Level4Button (LEVEL4_BUTTON_POSX, LEVEL4_BUTTON_POSY);

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Flower Blossom Valley",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                0);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
            }

            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }
        }
    }

    return success;
}

void close()
{
    gMenuTexture.Free();
    gInstructionTexture.Free();
    gCharacterTexture.Free();
    gGroundTexture.Free();
    gPlayButtonTexture.Free();
    gHelpButtonTexture.Free();
    gExitButtonTexture.Free();
    gBackButtonTexture.Free();
    gPauseButtonTexture.Free();
    gLevel1ButtonTexture.Free();
    gLevel2ButtonTexture.Free();
    gLevel3ButtonTexture.Free();
    gLevel4ButtonTexture.Free();
    gScoreTexture.Free();
    gSnailTexture.Free();
    gHighScoreTexture.Free();
    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);
//    Mix_FreeChunk(gClick);
    gMusic = nullptr;
    gMenuMusic = nullptr;
//    gClick = nullptr;

    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    srand(time(0));

    if (InitData() == false)
        return -1;
    else if (LoadMedia() == false)
        return -1;
        else {
    bool Quit_Menu = false;
    //  bool Play_Again = false;
    bool Quit_Play = false;
    int PlayLevel = 0;
            bool Quit_Game = false;
    Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
    while (!Quit_Menu)
    {
        SDL_Event e_mouse;

        while (SDL_PollEvent(&e_mouse) != 0)
        {
            if (e_mouse.type == SDL_QUIT)
            {
                Quit_Menu = true;
            }

            //   HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);
            HandlePlayButton(&e_mouse, gBackButton,gLevel1Button, gLevel2Button, gLevel3Button, gLevel4Button,
                             PlayButton, BackButton, Level1Button, Level2Button, Level3Button, Level4Button,
                             gBackButtonTexture, gLevel1ButtonTexture, gLevel2ButtonTexture, gLevel3ButtonTexture, gLevel4ButtonTexture,
                             g_screen, Quit_Game, gClick, PlayLevel, Quit_Menu,gLevelMenuTexture, gSnailTexture,gSnail);
            if (Quit_Menu == 1 ) break;

            HandleHelpButton(&e_mouse, gBackButton,
                             HelpButton, BackButton,
                             gInstructionTexture, gBackButtonTexture,
                             g_screen, Quit_Game, gClick);

            HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

//            cout << Quit_Menu << '\n';
//            cout << PlayLevel << '\n';
            if (Quit_Menu == true)
            {
                break;
            }
        }
        if (Quit_Menu == 1 ) break;

        gMenuTexture.Render(0,0,g_screen);

        SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];

        PlayButton.Render(currentClip_Play, g_screen, gPlayButtonTexture);

        SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
        HelpButton.Render(currentClip_Help, g_screen, gHelpButtonTexture);

        SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
        ExitButton.Render(currentClip_Exit, g_screen, gExitButtonTexture);


        SDL_RenderPresent(g_screen);
    }


    while(PlayLevel != 0 && PlayLevel < 4)
    {
        srand(time(NULL));
        bool is_quit = false;
        bool Game_State = true;
        while (!is_quit)
        {
            if (Game_State)
            {
                while (SDL_PollEvent(&g_event)!=0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        is_quit = true;
                        PlayLevel = 0;
                    }


                }

//                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(g_screen);
//
//                g_background.Render(0,0,g_screen, NULL);

                PlayLayer playLayer(g_screen);
                if (!playLayer.init(PlayLevel))
                {
                    printf("Failed to initialize PlayLayer.\n");
                }

                if(playLayer.exec())
                    SDL_RenderPresent(g_screen);
                else
                {
                    PlayLevel = 0;
                    Quit_Menu = 0;
                    Quit_Game = 0;
                }
            }


//            if (!Play_Again)
            {

            }
        }
    }

    while(PlayLevel ==  4)
    {
        srand(time(NULL));
        bool is_quit = false;
        bool Game_State = true;
        while (!is_quit)
        {
            if (Game_State)
            {
                while (SDL_PollEvent(&g_event)!=0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        is_quit = true;
                        PlayLevel = 0;
                    }


                }

                SDL_RenderClear(g_screen);
                PlayLayer playLayer(g_screen);
                if (!playLayer.initMatrix())
                {
                    printf("Failed to initialize PlayLayer.\n");
                }

                playLayer.exec2();
                SDL_RenderPresent(g_screen);

                if( playLayer.Moves == 0 )
                {
                    PlayLevel = 0;
                    Quit_Menu = 0;
                }
            }


//            if (!Play_Again)
            {

            }
        }
    }
        }

    close();
    return 0;
}


bool LoadMedia()
{
    bool success = true;

    gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
    if (gMusic == nullptr)
    {
        LogError("Failed to load background music", MIX_ERROR);
        success = false;
    }

    gMenuMusic = Mix_LoadMUS("sound/menu_audio.wav");
    if (gMenuMusic == nullptr)
    {
        LogError("Failed to load menu music", MIX_ERROR);
        success = false;
    }

    gClick = Mix_LoadWAV("sound/mouse_click.wav");
    if (gClick == nullptr)
    {
        LogError("Failed to load mouse click sound", MIX_ERROR);
        success = false;
    }


    else
    {
        gFont = TTF_OpenFont("font/pixel_font.ttf", 28);
        if (gFont == NULL)
        {
            LogError("Failed to load font", MIX_ERROR);
            success = false;
        }
        else
        {
            if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, g_screen))
            {
                std::cout << "Failed to render text1 texture" << std::endl;
                success = false;
            }

            if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, g_screen))
            {
                std::cout << "Failed to render text2 texture" << std::endl;
                success = false;
            }

            if (!gMenuTexture.LoadImg("img/background/menu1.png", g_screen))
            {
                std::cout << "Failed to load menu image" << std::endl;
                success = false;
            }

            if (!gInstructionTexture.LoadImg("img/background/instruction.png", g_screen))
            {
                std::cout << "Failed to load instruction image" << std::endl;
                success = false;
            }

            if (!gLevelMenuTexture.LoadImg("img/background/menu.png", g_screen))
            {
                std::cout << "Failed to load instruction image" << std::endl;
                success = false;
            }

            if (!gPlayButtonTexture.LoadImg("img/button/big_button/play_button.png", g_screen))
            {
                std::cout << "Failed to load play_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gPlayButton[i].x = 150 * i;
                    gPlayButton[i].y = 0;
                    gPlayButton[i].w = 150;
                    gPlayButton[i].h = 98;
                }
            }

            if (!gLevel1ButtonTexture.LoadImg("img/button/big_button/1.png", g_screen))
            {
                std::cout << "Failed to load play_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gLevel1Button[i].x = 150 * i;
                    gLevel1Button[i].y = 0;
                    gLevel1Button[i].w = 150;
                    gLevel1Button[i].h = 150;
                }
            }

            if (!gLevel2ButtonTexture.LoadImg("img/button/big_button/2.png", g_screen))
            {
                std::cout << "Failed to load play_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gLevel2Button[i].x = 150 * i;
                    gLevel2Button[i].y = 0;
                    gLevel2Button[i].w = 150;
                    gLevel2Button[i].h = 150;
                }
            }

            if (!gLevel3ButtonTexture.LoadImg("img/button/big_button/3.png", g_screen))
            {
                std::cout << "Failed to load play_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gLevel3Button[i].x = 120 * i;
                    gLevel3Button[i].y = 0;
                    gLevel3Button[i].w = 120;
                    gLevel3Button[i].h = 120;
                }
            }

            if (!gLevel4ButtonTexture.LoadImg("img/button/big_button/5.png", g_screen))
            {
                std::cout << "Failed to load play_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gLevel4Button[i].x = 180 * i;
                    gLevel4Button[i].y = 0;
                    gLevel4Button[i].w = 180;
                    gLevel4Button[i].h = 180;
                }
            }

            if (!gHelpButtonTexture.LoadImg("img/button/big_button/help_button.png", g_screen))
            {
                std::cout << "Failed to load help_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gHelpButton[i].x = 150 * i;
                    gHelpButton[i].y = 0;
                    gHelpButton[i].w = 150;
                    gHelpButton[i].h = 98;
                }
            }

            if (!gSnailTexture.LoadImg("img/Other/1.png", g_screen))
            {
                std::cout << "Failed to load help_button image" << std::endl;
                success = false;
            }

            if (!gBackButtonTexture.LoadImg("img/button/big_button/back_button.png", g_screen))
            {
                std::cout << "Failed to load back_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gBackButton[i].x = 150 * i;
                    gBackButton[i].y = 0;
                    gBackButton[i].w = 150;
                    gBackButton[i].h = 130;
                }
            }

            if (!gExitButtonTexture.LoadImg("img/button/big_button/exit_button.png", g_screen))
            {
                std::cout << "Failed to load exit_button image" << std::endl;
                success = false;
            }
            else
            {
                for (int i = 0; i < BUTTON_TOTAL; ++i)
                {
                    gExitButton[i].x = 150 * i;
                    gExitButton[i].y = 0;
                    gExitButton[i].w = 150;
                    gExitButton[i].h = 98;
                }
            }

        }
    }
    return success;
}
