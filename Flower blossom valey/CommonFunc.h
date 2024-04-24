#pragma once

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

static SDL_Window* g_window = NULL;
static  SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

// new

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 4*TILE_SIZE
#define MAX_HEIGHT 250

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1


#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2


const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 725;
const int PLAY_BUTTON_POSY= 501;
const int HELP_BUTTON_POSX = 725;
const int HELP_BUTTON_POSY = 605;
const int EXIT_BUTTON_POSX = 725;
const int EXIT_BUTTON_POSY = 709;
const int BACK_BUTTON_POSX = 170;
const int BACK_BUTTON_POSY = 700;
const int LEVEL1_BUTTON_POSX = 1250;
const int LEVEL1_BUTTON_POSY = 700;
const int LEVEL2_BUTTON_POSX = 1100;
const int LEVEL2_BUTTON_POSY = 500;
const int LEVEL3_BUTTON_POSX = 300;
const int LEVEL3_BUTTON_POSY = 250;
const int LEVEL4_BUTTON_POSX = 200;
const int LEVEL4_BUTTON_POSY = 100 ;
const int SNAIL_POSX = 650;
const int SNAIL_POSY = 300;
//const int PAUSE_BUTTON_POSX = 31;
//const int PAUSE_BUTTON_POSY = 29;
//const int CONTINUE_BUTTON_POSX = 31;
//const int CONTINUE_BUTTON_POSY = 29;

const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int SCORE_POSX = 830;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 830;
const int HIGH_SCORE_POSY = 80;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(std::string msg, int error_code = SDL_ERROR);

