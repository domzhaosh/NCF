#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here. 在这里实现 Director 、 Scene 的初始化代码
    @return true    Initialize success, app continue. 初始化 success, app 继续.
    @return false   Initialize failed, app terminate. 初始化 failed, app 终止.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background 当应用程序进入后台，此函数将被调用
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground 应用程序进入前台时，这个函数将被调用.
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

