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
void HandlePlayButton(SDL_Event* e, SDL_Rect (&gBackButton)[BUTTON_TOTAL], SDL_Rect (&gLevelButton)[BUTTON_TOTAL],
                      Button& PlayButton, Button& BackButton, Button& LevelButton,
                      BaseObject& gBackButtonTexture, BaseObject& gLevelButtonTexture,
                      SDL_Renderer* gRenderer, bool& Quit_MenuLevel, Mix_Chunk* gClick, bool& PlayLevel, bool& Quit_Menu, BaseObject& gLevelMenuTexture);
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
