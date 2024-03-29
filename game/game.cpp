#include "game.h"
#include "sdl_check.hpp"

int Game::flowerColorList[ColorsNum][3] = {
    { 0xff, 0x00, 0x00 },
    { 0xff, 0x80, 0x00 },
    { 0xff, 0xff, 0x00 },
    { 0x80, 0xff, 0x00 },
    { 0x00, 0xff, 0xff },
    { 0x00, 0x80, 0xff },
    { 0x00, 0x00, 0xff },
    { 0x80, 0x00, 0xff },
    { 0xff, 0x00, 0xff },
    { 0xff, 0x00, 0x80 },
  };


Game::Game()
{
  auto res = SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CHECK(res == 0, "SDL_Init");
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_CHECK(window, "SDL_CreateWindowAndRenderer");
  SDL_CHECK(renderer, "SDL_CreateWindowAndRenderer");
  SDL_SetWindowPosition(window, 65, 126);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  auto surface = SDL_LoadBMP("flower.bmp");
  SDL_CHECK(surface, "SDL_LoadBMP(\"flower.bmp\")");
  flowers = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_CHECK(flowers, "SDL_CreateTextureFromSurface");
  SDL_FreeSurface(surface);
  for (int x = 0; x < Width / FlowerWidth; ++x)
    for (int y = 0; y < Height/ FlowerHeight; ++y)
      field[x][y] = rand() % ColorsNum;
}

Game::~Game()
{
  SDL_DestroyTexture(flowers);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int Game::exec()
{
  auto oldTick = SDL_GetTicks();
  for (auto done = false; !done;)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_MOUSEBUTTONUP:
        {
          auto x = e.button.x / FlowerWidth;
          auto y = e.button.y / FlowerHeight;
          if (selectedX >= 0 && selectedY >= 0 &&
              ((abs(x - selectedX) == 1 && y == selectedY) || (abs(y - selectedY) == 1 && x == selectedX)))
          {
            std::swap(field[x][y], field[selectedX][selectedY]);
            selectedX = -1;
            selectedY = -1;
          }
          else
          {
            selectedX = e.button.x / FlowerWidth;
            selectedY = e.button.y / FlowerHeight;
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
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    draw();
    SDL_RenderPresent(renderer);
  }
  return 0;
}

bool Game::tick()
{
  if (ticks++ % 200 != 0)
    return true;
  if (checkHoles())
    return true;
  findAndRemoveLines();
  return true;
}

void Game::draw()
{
  for (int x = 0; x < Width / FlowerWidth; ++x)
    for (int y = 0; y < Height/ FlowerHeight; ++y)
    {
      if (field[x][y] >= 0)
      {

        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = FlowerWidth;
        src.h = FlowerHeight;
        SDL_Rect dest;
        dest.x = x * FlowerWidth;
        dest.y = y * FlowerHeight;
        dest.w = FlowerWidth;
        dest.h = FlowerHeight;
        if (x != selectedX || y != selectedY || SDL_GetTicks() % 250 > 125)
          SDL_RenderCopy(renderer, flowers, &src, &dest);
        SDL_SetRenderDrawColor(renderer,
                               flowerColorList[field[x][y]][0],
                               flowerColorList[field[x][y]][1],
                               flowerColorList[field[x][y]][2],
                               0xc0);
        SDL_RenderFillRect(renderer, &dest);
      }
    }
}

void Game::findAndRemoveLines()
{
  int maxLineH = 1;
  int maxXH = 0;
  int maxYH = 0;
  for (int y = 0; y < Height / FlowerHeight; ++y)
  {
    int currentColor = field[0][y];
    int line = 1;
    for (int x = 1; x < Width / FlowerWidth; ++x)
    {
      if (currentColor == field[x][y])
      {
        ++line;
      }
      else
      {
        if (maxLineH < line && currentColor != -1)
        {
          maxLineH = line;
          maxXH = x - line;
          maxYH = y;
        }
        line = 1;
      }
      currentColor = field[x][y];
    }
    if (maxLineH < line && currentColor != -1)
    {
      maxLineH = line;
      maxXH = Width / FlowerWidth - line;
      maxYH = y;
    }
  }

  int maxLineV = 1;
  int maxXV = 0;
  int maxYV = 0;
  for (int x = 0; x < Width / FlowerWidth; ++x)
  {
    int currentColor = field[x][0];
    int line = 1;
    for (int y = 1; y < Height / FlowerHeight; ++y)
    {
      if (currentColor == field[x][y])
      {
        ++line;
      }
      else
      {
        if (maxLineV < line && currentColor != -1)
        {
          maxLineV = line;
          maxXV = x;
          maxYV = y - line;
        }
        line = 1;
      }
      currentColor = field[x][y];
    }
    if (maxLineV < line && currentColor != -1)
    {
      maxLineV = line;
      maxXV = x;
      maxYV = Height / FlowerHeight - line;
    }
  }
  if (maxLineH >= maxLineV)
  {
    if (maxLineH >= 3)
    {
      for (int x = maxXH; x < maxXH + maxLineH; ++x)
      {
        field[x][maxYH] = -1;
      }
    }
  }
  else
  {
    if (maxLineV >= 3)
    {
      for (int y = maxYV; y < maxYV + maxLineV; ++y)
      {
        field[maxXV][y] = -1;
      }
    }
  }
}

bool Game::checkHoles()
{
  bool hasHoles = false;
  for (auto y = Height / FlowerHeight - 2; y >= 0; --y)
  {
    for (auto x = 0; x < Width / FlowerWidth; ++x)
    {
      if (field[x][y] != -1 && field[x][y + 1] == -1)
      {
        for (auto yy = y; yy >= 0; --yy)
          field[x][yy + 1] = field[x][yy];
        field[x][0] = -1;
        hasHoles = true;
      }
    }
  }
  for (auto x = 0; x < Width / FlowerWidth; ++x)
    if (field[x][0] == -1)
      field[x][0] = rand() % ColorsNum;
  return hasHoles;
}
