//#include "menu.h"
//
//int SDLCommonFunc::ShowMenu ( SDL_Surface* des, TTF_Font* font )
//{
//    Texture g_png_menu;
//    g_png_menu.loadFromFile("background.png");
//    if ( g_png_menu == NULL )
//    {
//        return 1;
//    }
//    const int kMenuItemNum = 2;
//    SDL_Rect pos_arr[kMenuItemNum];
//    pos_arr[0].x = 200;
//    pos_arr[0].y = 400;
//
//    pos_arr[1].x = 200;
//    pos_arr[1].y = 200;
//
//
//    bool selected[kMenuItemNum] = {0,0};
//
//    SDL_Event m_event;
//    while (true)
//    {
//        g_png_menu.render(0,0,1600,900,NULL);
//        for ( int i = 0 ; i < kMenuItemNum ; ++i )
//        {
//            text_menu[i].CreateGameText(font,des);
//
//        }
//    }
//}
