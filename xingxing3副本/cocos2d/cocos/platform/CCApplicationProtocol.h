/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_APPLICATION_PROTOCOL_H__
#define __CC_APPLICATION_PROTOCOL_H__

#include "base/CCPlatformMacros.h"
#include "base/CCScriptSupport.h"
#include "base/CCAutoreleasePool.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL ApplicationProtocol
{
public:

    // Since WINDOWS and ANDROID are defined as macros, we could not just use these keywords in enumeration(Platform).
    // Therefore, 'OS_' prefix is added to avoid conflicts with the definitions of system macros.
    // 由于Windows和Android被定义为宏（平台），我们不能只是在枚举里面使用这些关键字
    //因此, 'OS_' 前缀添加在系统宏的定义，以避免冲突
    enum class Platform
    {
        OS_WINDOWS,
        OS_LINUX,
        OS_MAC,
        OS_ANDROID,
        OS_IPHONE,
        OS_IPAD,
        OS_BLACKBERRY,
        OS_NACL,
        OS_EMSCRIPTEN,
        OS_TIZEN,
        OS_WINRT,
        OS_WP8
    };

    /**
     * @js NA
     * @lua NA
     */
    virtual ~ApplicationProtocol(){
#if CC_ENABLE_SCRIPT_BINDING
        ScriptEngineManager::destroyInstance();
#endif
        // clean auto release pool
        PoolManager::destroyInstance();
    }

    /**
    @brief    Implement Director and Scene init code here.  在这里实现 Director 、 Scene 的初始化代码
    @return true    Initialize success, app continue. 初始化 success, app 继续.
    @return false   Initialize failed, app terminate. 初始化 failed, app 终止.
    * @js NA
    * @lua NA
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  This function will be called when the application enters background.当应用程序进入后台，此函数将被调用
    * @js NA
    * @lua NA
    */
    virtual void applicationDidEnterBackground() = 0;

    /**
    @brief  This function will be called when the application enters foreground.应用程序进入前台时，这个函数将被调用.
    * @js NA
    * @lua NA
    */
    virtual void applicationWillEnterForeground() = 0;

    /**
    @brief    Callback by Director for limit FPS.  Director 用于限制 FPS 的回调.
    @param interval The time, expressed in seconds, between current frame and next. 表示当前帧和下一帧之间间隔时间，以秒为单位.
    * @js NA
    * @lua NA
    */
    virtual void setAnimationInterval(double interval) = 0;

    /**
    @brief Get current language config 获取当前的语言配置
    @return Current language config    当前的语言配置
    * @js NA
    * @lua NA
    */
    virtual LanguageType getCurrentLanguage() = 0;
    
    /**
     @brief Get current language iso 639-1 code  得到当前的iso 639 - 1语言代码
     @return Current language iso 639-1 code
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode() = 0;
    
    /**
     @brief Get target platform  目标平台
     * @js NA
     * @lua NA
     */
    virtual Platform getTargetPlatform() = 0;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
