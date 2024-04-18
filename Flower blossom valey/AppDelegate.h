#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

/**
@brief    The SDL Application.
*/
class  AppDelegate
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    */
    virtual void applicationWillEnterForeground();

};





#endif // _APP_DELEGATE_H_
