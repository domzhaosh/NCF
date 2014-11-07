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

#ifndef __CCGLVIEWPROTOCOL_H__
#define __CCGLVIEWPROTOCOL_H__

#include "base/ccTypes.h"
#include "base/CCEventTouch.h"

#include <vector>

enum class ResolutionPolicy
{
    /**
     [1] EXACT_FIT 通过 stretch-to-fit（拉伸）来填满屏幕: 如果分辨率的宽度、高度和屏幕的分辨率不同，会拉长你的游戏视图来适应屏幕
     [2] NO_BORDER 全屏无黑色边框:  如果分辨率式样的宽度、高度和屏幕的分辨率不同，你游戏视图的两个区域会将被削减。
     [3] SHOW_ALL 带有黑色边框的全屏:  如果分辨率式样的宽度、高度和屏幕的分辨率不同，两个黑色边框将显示.
     */
    
    
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio.
    // Distortion can occur, and the application may appear stretched or compressed.
    // 整个应用程序在指定区域中可见，而试图保持原始宽高比。
    // 可能会发生扭曲，应用程序可能会拉伸或压缩。
    EXACT_FIT,
    // The entire application fills the specified area, without distortion but possibly with some cropping,
    // while maintaining the original aspect ratio of the application.
    // 整个应用程序填满指定区域，不扭曲，但可能进行一些裁切，同时保持应用程序的原始宽高比。
    NO_BORDER,
    // The entire application is visible in the specified area without distortion while maintaining the original
    // aspect ratio of the application. Borders can appear on two sides of the application.
    // 看到整个应用程序在指定区域不失真，同时保持应用程序的原始宽高比。应用程序的两边可能会显示边框。
    SHOW_ALL,
    // The application takes the height of the design resolution size and modifies the width of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    // 该应用程序采用高度来，内部画布的宽度根据设计分辨率大小变化的，使其适合设备的纵横比没有会变形，但是你必须确保你的应用程序适用于不同的纵横比
    FIXED_HEIGHT,
    // The application takes the width of the design resolution size and modifies the height of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    // 该应用程序采用宽度根据分辨率大小来设计，高度根据内部画布变化的，使其适合设备的纵横比没有会变形，但是你必须确保你的应用程序适用于不同的纵横比
    FIXED_WIDTH,
    
    UNKNOWN,
};

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL GLViewProtocol
{
public:
    /**
     * @js ctor
     */
    GLViewProtocol();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLViewProtocol();
    
    /** Force destroying EGL view, subclass must implement this method. */
    /**强制销毁EGL视图，子类必须实现此方法。*/
    virtual void end() =0;
    
    /** Get whether opengl render system is ready, subclass must implement this method. */
    /** 获取OpenGL的渲染系统是否已准备好，子类必须实现此方法. */
    virtual bool isOpenGLReady() =0;
    
    /** Exchanges the front and back buffers, subclass must implement this method. */
    /**交换前后缓冲区，子类必须实现此方法. */
    virtual void swapBuffers() =0;
    
    /** Open or close IME keyboard , subclass must implement this method. */
    /** 打开或关闭输入法键盘，子类必须实现此方法. */
    virtual void setIMEKeyboardState(bool open) =0;
    
    /**
     * Polls input events. Subclass must implement methods if platform
     * does not provide event callbacks.
     Polls 输入事件。如果平台不提供事件回调 子类必须实现的方法
     */
    virtual void pollInputEvents();
    
    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     * 获取EGL视图帧大小。
     * 在一般情况下，它返回的屏幕尺寸,因为EGL的 view 是全屏的 view
     */
    virtual const Size& getFrameSize()const;
    
    /**
     * Set the frame size of EGL view.
     * 设置 EGL 视图帧大小.
     */
    virtual void setFrameSize(float width,float height);
    
    /**
     * Get the visible area size of opengl viewport.<br/>
     * 获取 openGL的视图窗口的可见区域大小.
     */
    virtual Size getVisibleSize()const;
    
    /**
     * Get the visible origin point of opengl viewport.
     * 获取 openGL的视图窗口可见源点
     */
    virtual Vec2 getVisibleOrigin()const;
    
    /**
     * Get the visible rectangle of opengl viewport.
     * 获取openGL 视图窗口的可见矩形
     */
    virtual Rect getVisibleRect()const;
    
    /**
     * Set the design resolution size. 设置设计分辨率大小
     * @param width Design resolution width.  分辨率宽度样式
     * @param height Design resolution height.分辨率高度样式
     * @param resolutionPolicy The resolution policy desired, you may choose: 你可以根据需要选择所需要的分辨率:
     *                         [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] NO_BORDER Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] SHOW_ALL  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     
     [1] EXACT_FIT 通过 stretch-to-fit（拉伸）来填满屏幕: 如果分辨率的宽度、高度和屏幕的分辨率不同，会拉长你的游戏视图来适应屏幕
     [2] NO_BORDER 全屏无黑色边框:  如果分辨率式样的宽度、高度和屏幕的分辨率不同，你游戏视图的两个区域会将被削减。
     [3] SHOW_ALL 带有黑色边框的全屏:  如果分辨率式样的宽度、高度和屏幕的分辨率不同，两个黑色边框将显示.
     */
    virtual void setDesignResolutionSize(float width,float height,ResolutionPolicy resolutionPolicy);
    
    /** Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     获取分辨率式样大小.
     默认分辨率大小和 'getFrameSize' 是一样的.
     */
    virtual const Size&  getDesignResolutionSize()const;
    
    /**
     * Set opengl view port rectangle with points.
     * 使用 一些点 设置opengl 视图窗口的矩形
     */
    virtual void setViewPortInPoints(float x ,float y ,float w ,float h);
    
    /**
     * Set Scissor rectangle with points.
     * 使用 一些点 设置裁剪矩形
     */
    virtual void setScissorInPoints(float x ,float y ,float w ,float h);
    
    /**
     * Get whether GL_SCISSOR_TEST is enable
     * 设置是否启用 GL_SCISSOR_TEST
     */
    virtual bool isScissorEnabled();
    
    /**
     * Get the current scissor rectangle
     * 获得当前的裁剪矩形
     */
    virtual Rect getScissorRect()const;
    
    virtual void setViewName(const std::string& viewname);
    const std::string& getViewName()const;
    
    /**
     Touch events are handled by default; if you want to customize your handlers, please override these functions:
     默认情况下触摸事件的处理，如果你想自定义您的处理程序，请重写这些函数
     */
    virtual void handleTouchesBegin(int num,intptr_t ids[],float xs[],float ys[]);
    virtual void handleTouchesMove(int num,intptr_t ids[],float xs[],float ys[]);
    virtual void handleTouchesEnd(int num,intptr_t ids[],float xs[],float ys[]);
    virtual void handleTouchesCancel(int num,intptr_t ids[],float xs[],float ys[]);
    
    /**
     * Get the opengl view port rectangle.
     * 获得  OpenGL 视图窗口.
     */
    const Rect& getViewPortRect()const;
    
    /**
     * Get scale factor of the horizontal direction.
     * 获得水平方向缩放比
     */
    float getScaleX()const;
    
    /**
     * Get scale factor of the vertical direction.
     * 获得垂直方向缩放比
     */
    float getScaleY()const;
    
    /** returns the current Resolution policy */
    ResolutionPolicy getResolutionPolicy()const {return _resolutionPolicy; }
    
protected:
    void updateDesignResolutionSize();
    
    
    void handleTouchesOfEndOrCancel(EventTouch::EventCode eventCode, int num, intptr_t ids[], float xs[], float ys[]);
    
    
    // real screen size 真实的屏幕尺寸
    Size _screenSize;
    // resolution size, it is the size appropriate for the app resources.
    // 分辨率的大小，它适应应用程序资源大小
    Size _designResolutionSize;
    // the view port size
    //视图窗口的大小
    Rect _viewPortRect;
    // the view name
    std::string _viewName;
    
    float _scaleX;
    float _scaleY;
    ResolutionPolicy _resolutionPolicy;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCGLVIEWPROTOCOL_H__ */
