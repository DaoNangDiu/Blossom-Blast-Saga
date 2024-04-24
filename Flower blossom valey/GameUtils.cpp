#include "GameUtils.h"

//std::string GetHighScoreFromFile(std::string path)
//{
//    std::fstream HighScoreFile;
//    std::string highscore;
//
//    HighScoreFile.open(path, std::ios::in);
//    HighScoreFile >> highscore;
//
//    return highscore;
//}
//
////void UpdateHighScore(std::string path,
////                     const int& score,
//                     const std::string& old_high_score)
//{
//    int oldHighScore = 0;
//    std::fstream HighScoreFile;
//    std::string newHighScore;
//    std::stringstream ConvertToInt(old_high_score);
//
//    HighScoreFile.open(path, std::ios::out);
//
//    ConvertToInt >> oldHighScore;
//    if (score > oldHighScore)
//    {
//        oldHighScore = score;
//    }
//    newHighScore = std::to_string(oldHighScore);
//
//    HighScoreFile << newHighScore;
//}

//int UpdateGameTimeAndScore(int& time,
//                           int& speed,
//                           int& score)
//{
//    if (time == TIME_MAX)
//    {
//        speed += SPEED_INCREASEMENT;
//    }
//
//    if (time > TIME_MAX)
//    {
//        time = 0;
//    }
//    if (time % 5 == 0)
//    {
//        score += SCORE_INCREASEMENT;
//    }
//
//    time += TIME_INCREASEMENT;
//
//    return time;
//}


//void HandlePlayButton(SDL_Event* e,
//                      Button& PlayButton,
//                      bool& QuitMenu,
//                      bool& Play,
//                      Mix_Chunk* gClick)
//{
//    if (e->type == SDL_QUIT)
//    {
//        QuitMenu = true;
//    }
//
//    if (PlayButton.IsInside(e, COMMON_BUTTON))
//    {
//        switch (e->type)
//        {
//        case SDL_MOUSEMOTION:
//            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
//            break;
//        case SDL_MOUSEBUTTONDOWN:
//            Play = true;
//            QuitMenu = true;
//            Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
//            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
//            break;
//        }
//    }
//    else
//    {
//        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
//    }
//}

//void HandlePlayButton(SDL_Event* e, SDL_Rect (&gBackButton)[BUTTON_TOTAL], SDL_Rect (&gLevelButton)[BUTTON_TOTAL],
//                      Button& PlayButton, Button& BackButton, Button& LevelButton,
//                      BaseObject& gBackButtonTexture, BaseObject& gLevelButtonTexture,
//                      SDL_Renderer* gRenderer, bool& Quit_MenuLevel, Mix_Chunk* gClick, bool& PlayLevel, bool& Quit_Menu, BaseObject& gLevelMenuTexture)
//{
//    if ( e->type == SDL_QUIT )
//    {
//        Quit_Menu = true;
//    }
//    if (PlayButton.IsInside(e, COMMON_BUTTON))
//    {
//        switch (e->type)
//        {
//        case SDL_MOUSEMOTION:
//            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
//            break;
//        case SDL_MOUSEBUTTONDOWN:
//            Quit_Menu = true;
//
//            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
//            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
//
//            bool ReadDone = false;
//            while (!ReadDone)
//            {
//                do
//                {
//                    if (e->type == SDL_QUIT)
//                    {
//                        ReadDone = true;
//                        Quit_Menu = true;
//                        close();
//                    }
//                    else if (BackButton.IsInside(e, COMMON_BUTTON))
//                    {
//                        switch (e->type)
//                        {
//                        case SDL_MOUSEMOTION:
//                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
//                            break;
//                        case SDL_MOUSEBUTTONDOWN:
//                            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
//                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
//                            ReadDone = true;
//                            break;
//                        }
//                    }
//                    else
//                    {
//                        BackButton.currentSprite = BUTTON_MOUSE_OUT;
//                        if (LevelButton.IsInside(e, COMMON_BUTTON))
//                        {
//                            switch (e->type)
//                            {
//                            case SDL_MOUSEMOTION:
//                                LevelButton.currentSprite = BUTTON_MOUSE_OVER;
//                                break;
//                            case SDL_MOUSEBUTTONDOWN:
//                                PlayLevel = true;
//                                Quit_MenuLevel = true;
//                                Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
//                                LevelButton.currentSprite = BUTTON_MOUSE_OVER;
//                                break;
//                            }
//                        }
//                        else
//                        {
//                            LevelButton.currentSprite = BUTTON_MOUSE_OUT;
//                        }
//                }
//                    SDL_RenderClear(gRenderer);
//                    gLevelMenuTexture.Render(0,0,gRenderer);
//                    SDL_Rect* currentClip_Level = &gLevelButton[LevelButton.currentSprite];
//                    LevelButton.Render(currentClip_Level, gRenderer, gLevelButtonTexture);
//                    SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
//                    BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);
//                    SDL_RenderPresent(gRenderer);
//
//                }
//                while (SDL_PollEvent(e) != 0 && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION));
//            }
//            break;
//        }
//    }
//    else
//    {
//        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
//    }
//}
void HandlePlayButton(SDL_Event* e, SDL_Rect (&gBackButton)[BUTTON_TOTAL], SDL_Rect (&gLevel1Button)[BUTTON_TOTAL], SDL_Rect (&gLevel2Button)[BUTTON_TOTAL],
                      SDL_Rect (&gLevel3Button)[BUTTON_TOTAL], SDL_Rect (&gLevel4Button)[BUTTON_TOTAL],
                      Button& PlayButton, Button& BackButton, Button& Level1Button,
                      Button& Level2Button, Button& Level3Button, Button& Level4Button,
                      BaseObject& gBackButtonTexture, BaseObject& gLevel1ButtonTexture,
                      BaseObject& gLevel2ButtonTexture, BaseObject& gLevel3ButtonTexture, BaseObject& gLevel4ButtonTexture,
                      SDL_Renderer* gRenderer, bool& Quit_MenuLevel, Mix_Chunk* gClick,
                      int& PlayLevel, bool& Quit_Menu, BaseObject& gLevelMenuTexture)
{
    // Check for quit event
    if (e->type == SDL_QUIT)
    {
        Quit_Menu = true;
        return;
    }

    // Check for mouse events on play button
    if (PlayButton.IsInside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Play button clicked
            //Quit_Menu = true;
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

            bool ReadDone = false;
            while (!ReadDone)
            {
                // Handle events inside the loop
                SDL_PollEvent(e);
                switch (e->type)
                {
                case SDL_QUIT:
                    Quit_MenuLevel = true;
                    close();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Check if back button is clicked
                    if (BackButton.IsInside(e, COMMON_BUTTON))
                    {
                        Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                        BackButton.currentSprite = BUTTON_MOUSE_OVER;
                        ReadDone = true;
                    }
                    // Check if level button is clicked
                    else if (Level1Button.IsInside(e, COMMON_BUTTON))
                    {
                        PlayLevel = 1;
                        //Quit_MenuLevel = true;
                        Quit_Menu = 1;
                        ReadDone = true;
                        Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                        Level1Button.currentSprite = BUTTON_MOUSE_OVER;
                        break;
                    }
                    else if (Level2Button.IsInside(e, COMMON_BUTTON))
                    {
                        PlayLevel = 2;
                        //Quit_MenuLevel = true;
                        Quit_Menu = 1;
                        ReadDone = true;
                        Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                        Level2Button.currentSprite = BUTTON_MOUSE_OVER;
                        break;
                    }
                    else if (Level3Button.IsInside(e, COMMON_BUTTON))
                    {
                        PlayLevel = 3;
                        //Quit_MenuLevel = true;
                        Quit_Menu = 1;
                        ReadDone = true;
                        Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                        Level3Button.currentSprite = BUTTON_MOUSE_OVER;
                        break;
                    }
                    else if (Level1Button.IsInside(e, COMMON_BUTTON))
                {
                    PlayLevel = 4;
                    //Quit_MenuLevel = true;
                    Quit_Menu = 1;
                    ReadDone = true;
                    Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                        Level4Button.currentSprite = BUTTON_MOUSE_OVER;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    BackButton.currentSprite = BUTTON_MOUSE_OUT;
                    Level1Button.currentSprite = BUTTON_MOUSE_OUT;
                    Level2Button.currentSprite = BUTTON_MOUSE_OUT;
                    Level3Button.currentSprite = BUTTON_MOUSE_OUT;
                    Level4Button.currentSprite = BUTTON_MOUSE_OUT;
                    break;
                default:
                    break;
                }

                // Render menu
                SDL_RenderClear(gRenderer);
                gLevelMenuTexture.Render(0,0,gRenderer);
                BackButton.Render(&gBackButton[BackButton.currentSprite], gRenderer, gBackButtonTexture);
                Level1Button.Render(&gLevel1Button[Level1Button.currentSprite], gRenderer, gLevel1ButtonTexture);
                Level2Button.Render(&gLevel2Button[Level2Button.currentSprite], gRenderer, gLevel2ButtonTexture);
                Level3Button.Render(&gLevel3Button[Level3Button.currentSprite], gRenderer, gLevel3ButtonTexture);
                Level4Button.Render(&gLevel4Button[Level4Button.currentSprite], gRenderer, gLevel4ButtonTexture);

                SDL_RenderPresent(gRenderer);
            }
            break;
        }
    }
    else
    {
        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}


void HandleHelpButton(SDL_Event* e,
                      SDL_Rect(&gBackButton)[BUTTON_TOTAL],
                      Button& HelpButton,
                      Button& BackButton,
                      BaseObject gInstructionTexture,
                      BaseObject gBackButtonTexture,
                      SDL_Renderer *gRenderer,
                      bool &Quit_game,
                      Mix_Chunk *gClick)
{
    if (HelpButton.IsInside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

            bool ReadDone = false;
            while (!ReadDone)
            {
                do
                {
                    if (e->type == SDL_QUIT)
                    {
                        ReadDone = true;
                        Quit_game = true;
                        close();
                    }

                    else if (BackButton.IsInside(e, COMMON_BUTTON))
                    {
                        switch (e->type)
                        {
                        case SDL_MOUSEMOTION:
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            ReadDone = true;
                            break;
                        }
                    }
                    else
                    {
                        BackButton.currentSprite = BUTTON_MOUSE_OUT;
                    }

                    gInstructionTexture.Render(0,0,gRenderer);

                    SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
                    BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

                    SDL_RenderPresent(gRenderer);
                }
                while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
            }
            break;

        }
    }
    else
    {
        HelpButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleExitButton(SDL_Event* e,
                      Button& ExitButton,
                      bool& Quit,
                      Mix_Chunk* gClick)
{
    if (ExitButton.IsInside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Quit = true;
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            break;
        }
    }
    else
    {
        ExitButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}
