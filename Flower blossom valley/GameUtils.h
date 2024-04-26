#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "BaseObject.h"
#include "Button.h"
#include "PlayLayer.h"
bool InitData();
bool LoadMedia();
void close();

//void HandlePlayButton(SDL_Event* e,
//    Button& PlayButton,
//    bool& QuitMenu,
//    bool& Play,
//    Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    BaseObject gInstructionTexture,
    BaseObject gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_game,
    Mix_Chunk* gClick);

void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
    Mix_Chunk* gClick);

void HandleContinueButton(Button ContinueButton,
    BaseObject gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State, Mix_Chunk* gClick);
//void HandlePlayButton(SDL_Event* e, SDL_Rect (&gBackButton)[BUTTON_TOTAL], SDL_Rect (&gLevelButton)[BUTTON_TOTAL],
//                      Button& PlayButton, Button& BackButton, Button& LevelButton,
//                      BaseObject& gBackButtonTexture, BaseObject& gLevelButtonTexture,
//                      SDL_Renderer* gRenderer, bool& Quit_MenuLevel, Mix_Chunk* gClick, bool& PlayLevel, bool& Quit_Menu, BaseObject& gLevelMenuTexture);
void HandlePlayButton(SDL_Event* e, SDL_Rect (&gBackButton)[BUTTON_TOTAL], SDL_Rect (&gLevel1Button)[BUTTON_TOTAL], SDL_Rect (&gLevel2Button)[BUTTON_TOTAL],
                      SDL_Rect (&gLevel3Button)[BUTTON_TOTAL], SDL_Rect (&gLevel4Button)[BUTTON_TOTAL],
                      Button& PlayButton, Button& BackButton, Button& Level1Button,
                      Button& Level2Button, Button& Level3Button, Button& Level4Button,
                      BaseObject& gBackButtonTexture, BaseObject& gLevel1ButtonTexture,
                      BaseObject& gLevel2ButtonTexture, BaseObject& gLevel3ButtonTexture, BaseObject& gLevel4ButtonTexture,
                      SDL_Renderer* gRenderer, bool& Quit_MenuLevel, Mix_Chunk* gClick,
                      int& PlayLevel,bool& Quit_Menu, BaseObject& gLevelMenuTexture,BaseObject& gSnailTexture, SDL_Rect (&gSnail)[11]);
void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button ContinueButton,
    BaseObject gContinueButtonTexture,
    bool& game_state,
    Mix_Chunk* gClick);

void DrawEndGameSelection(BaseObject gLoseTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    bool& Play_Again);

#endif // !GAME_UTILS_H_
