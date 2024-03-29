#pragma once
#include <SDL.h>

class Game
{
public:
  Game();
  ~Game();
  int exec();
  bool tick();
  void draw();
  const static int Width = 1280;
  const static int Height = 720;
  const static int FlowerWidth = 64;
  const static int FlowerHeight = 64;
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *flowers;
  static const int ColorsNum = 10;
  static int flowerColorList[10][3];
  int field[Width / FlowerWidth][Height / FlowerHeight];
  int selectedX = -1;
  int selectedY = -1;
  unsigned ticks = 0;
  void findAndRemoveLines();
  bool checkHoles();
};
