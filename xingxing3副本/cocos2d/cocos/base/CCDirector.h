/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include "base/CCPlatformMacros.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCGeometry.h"
#include "base/CCVector.h"
#include "CCGL.h"
#include "2d/CCLabelAtlas.h"
#include <stack>
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

/* Forward declarations. */  //告诉编译器这些类存在
class LabelAtlas;
class Scene;
class GLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
class EventCustom;
class EventListenerCustom;
class TextureCache;
class Renderer;

#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
class Console;
#endif

/**
@brief Class that creates and handles the main Window and manages how
and when to execute the Scenes.
 
 The Director is also responsible for:
  - initializing the OpenGL context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
  - setting the orientation (default one is Portrait)
 
 Since the Director is a singleton, the standard way to use it is by calling:
  _ Director::getInstance()->methodName();
 
 The Director also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
 
 
 @brief（简要） 创建一个主窗口来管理 如何以及何时执行 scenes（场景）
 
 Director 也负责以下:
 - 初始化 OpenGL 上下文
 - 设置 OpenGL像素格式 (默认值时 RGB565)
 - 设置 OpenGL 缓存大小 (默认是 0-bit)
 - 设置 投影 (默认是一个 3D)
 - 设置 方向 (默认是 Portrait)    //竖屏
 
 自从 Director 是一个 singleton, 标准的调用方法是:
 _ Director::getInstance()->methodName();
 
 Director 也设置默认的 OpenGL 上下文:
 - GL_TEXTURE_2D 可行的
 - GL_VERTEX_ARRAY 可行的
 - GL_COLOR_ARRAY 可行的
 - GL_TEXTURE_COORD_ARRAY 可行的
*/
enum class MATRIX_STACK_TYPE
{
    MATRIX_STACK_MODELVIEW,
    MATRIX_STACK_PROJECTION,
    MATRIX_STACK_TEXTURE
};  //矩阵堆栈类型的枚举

class CC_DLL Director : public Ref
{
private:
    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;
protected:
    void initMatrixStack();
public:
    void pushMatrix(MATRIX_STACK_TYPE type);
    void popMatrix(MATRIX_STACK_TYPE type);
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    Mat4 getMatrix(MATRIX_STACK_TYPE type);
    void resetMatrixStack();
public:
    static const char *EVENT_PROJECTION_CHANGED;
    static const char* EVENT_AFTER_UPDATE;
    static const char* EVENT_AFTER_VISIT;
    static const char* EVENT_AFTER_DRAW;


    /** @typedef ccDirectorProjection
     Possible OpenGL projections used by director
     
                 ccDirectorProjection 
     导演可能使用 OpenGL 的 投影
     */
    enum class Projection
    {
        /// sets a 2D projection (orthogonal projection)
        /// 设定的二维投影（正交投影）
        _2D,
        
        /// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        /// 使用 fovy=60, znear=0.5f and zfar=1500 设置一个3D投影.（垂直方向的视角--fovy；视锥的纵横比--aspect，视锥的近平面坐标--near，视锥的远平面坐标--far。
        _3D,
        
        /// it calls "updateProjection" on the projection delegate.
        /// 投影委托里面它调用 "updateProjection"
        CUSTOM,
        
        /// Default projection is 3D projection
        /// 默认投影是 3D 投影
        DEFAULT = _3D,
    };
    
    /** 
      *returns a shared instance of the director
     */
    static Director* getInstance();

    /** 
     @deprecated Use getInstance() instead
     @deprecated(弃用)的属性建议使用 getInstance() 代替
     */
    CC_DEPRECATED_ATTRIBUTE static Director* sharedDirector() { return Director::getInstance(); }
    /**
     * @js ctor       //js的构造函数
     */
    Director(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init();
 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // attribute  属性

    /** 
      *Get current running Scene. Director can only run one Scene at a time
      *         //获取当前正在运行的场景。Director 在这个时候只能运行一个场景（Scene对象）.
     */
    inline Scene* getRunningScene() { return _runningScene; }

    /** 
      *Get the FPS value
      *       //Get  FPS 值 */
    inline double getAnimationInterval() { return _animationInterval; }
    /** 
      *Set the FPS value.  //设置 FPS 值
      */
    virtual void setAnimationInterval(double interval) = 0;

    /** 
     Whether or not to display the FPS on the bottom-left corner
     // 是否在左下角显示 FPS 
     */
    inline bool isDisplayStats() { return _displayStats; }
    /**
     Display the FPS on the bottom-left corner 
     // 在左下角显示 FPS
     */
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** seconds per frame 每帧秒 */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** Get the GLView, where everything is rendered  //获取渲染后的 GLView
    * @js NA
    * @lua NA
    */
    inline GLView* getOpenGLView() { return _openGLView; }
    void setOpenGLView(GLView *openGLView);

    TextureCache* getTextureCache() const;

    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Whether or not the Director is paused  //Director 是否被暂停  */
    inline bool isPaused() { return _paused; }

    /** 
     How many frames were called since the director started
     //director 开始到现在持续了多少帧
     */
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
    /** Sets an OpenGL projection  // 设置 一个 OpenGL 投影
     @since v0.8.2
     * @js NA
     * @lua NA
     */
    inline Projection getProjection() { return _projection; }
    void setProjection(Projection projection);
    
    /** Sets the glViewport  //设置  glViewport */
    void setViewport();

    /** 
        How many frames were called since the director started
        director 开始到现在持续了多少帧
     */
    
    
    /** Whether or not the replaced scene will receive the cleanup message.
     If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     If the new scene replaces the old one, the it will receive the "cleanup" message.
     @since v0.99.0
     
     
     //被替换场景是否收到清除消息
     如果新的场景已经被 pushed （推出），那么旧的场景将不会收到“执行清理”的消息。
     如果新的场景替换了旧的，它会收到“执行清理”消息。
     
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     This object MUST implement the "visit" selector.
     Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications )
     @since v0.99.5
     
     
     // 主场景访问后这个对象将被访问
     这个对象必须实现 "visit" selector选择器.
     和通知对象挂钩, 像这个 Notifications (http://github.com/manucorporat/CCNotifications )
     
     */
    Node* getNotificationNode() const { return _notificationNode; }
    void setNotificationNode(Node *node);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // window size  窗口大小

    /** 
      returns the size of the OpenGL view in points.
      //返回OpenGL 视图大小（用points 点为单位）
    */
    const Size& getWinSize() const;

    /** 
     returns the size of the OpenGL view in pixels.
     //返回OpenGL 视图大小（用pixels 以像素为单位）
    */
    Size getWinSizeInPixels() const;
    
    /** returns visible size of the OpenGL view in points.
     *  the value is equal to getWinSize if don't invoke
     *  GLView::setDesignResolutionSize()
     *
     *  returns 以点为单位的 OpenGL 视图的可见大小.
     *  如果不调用 EGLView::setDesignResolutionSize() 值等于 getWinSize
     */
    Size getVisibleSize() const;
    
    /** 
     * returns visible origin of the OpenGL view in points.
     * returns 以点为单位的 OpenGL 视图的初始化时的可见大小
     */
    Vec2 getVisibleOrigin() const;

    /** 
     converts a UIKit coordinate to an OpenGL coordinate
     Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
     *  UIKit的坐标转换到一个OpenGL坐标
     *  有用(多)触摸坐标转换为当前布局(横向或纵向)
     */
    Vec2 convertToGL(const Vec2& point);

    /** converts an OpenGL coordinate to a UIKit coordinate
     Useful to convert node points to window points for calls such as glScissor
     * 一个OpenGL坐标转换到UIKit的坐标
     * 点组成的窗口调用有效的节点上面的点，例如 glScissor
     */
    Vec2 convertToUI(const Vec2& point);

    /// XXX: missing description 
    float getZEye() const;

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // Scene Management  场景管理

    /** Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     
     * 根据给定场景进入 Director's 主循环
     * 只能在运行你的第一个场景调用它.
     * 如果已经有一个场景在运行了就不要再调用它
     *
     * 它将调用pushScene：然后它会调用startAnimation
     */
    void runWithScene(Scene *scene);

    /** Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     
     * 停止执行正在运行的场景，放到暂停场景的堆栈上。
     * 新的场景将被执行.
     * 尽量避免在堆栈上存放一个很大的场景以减少内存分配，
     * 仅在有一个正在运行场景时调用它.
     */
    void pushScene(Scene *scene);

    /** Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     
     * 从堆栈中弹出一个场景。
     * 这个场景将替换正在运行的场景.
     * 正在运行的场景将被删除。如果有堆栈中没有其它的场景那么 popScene 的执行会被终止。
     * 仅在有一个正在运行但场景时候调用它.
     
     */
    void popScene();

    /** Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`
     
     * 从队列中弹出所有的场景，直到只有根场景在队列中
     * 这个场景将替换正在运行的场景.
     * 在内部将调用 `popToSceneStackLevel(1)`
     */
    void popToRootScene();

    /** Pops out all scenes from the stack until it reaches `level`.
     If level is 0, it will end the director.
     If level is 1, it will pop all scenes until it reaches to root scene.
     If level is <= than the current stack level, it won't do anything.
     
     弹出从队列中的所有场景，直到它到达 `level`.
     如果 level 是 0,它将结束 director.
     如果 level 是 1, 从队列中弹出所有的场景，直到只有根场景在队列中
     如果 level <= 当前的堆栈水平，它不会做任何事情。
     */
 	void popToSceneStackLevel(int level);

    /** Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     
     * 用一个新的替换正在运行的场景。终止正在运行的场景。
     * 仅在有一个正在运行场景的时候调用它.
     */
    void replaceScene(Scene *scene);

    /** Ends the execution, releases the running scene.
     It doesn't remove the OpenGL view from its parent. You have to do it manually.
     * @lua endToLua
     
     结束执行，释放正在运行的场景。
     它不会从其父视图中删除的OpenGL视图。你必须手动完成此任务。
     */
    void end();

    /** Pauses the running scene.
     The running scene will be _drawed_ but all scheduled timers will be paused
     While paused, the draw rate will be 4 FPS to reduce CPU consumption
     
     暂停正在运行的场景。.
     正在运行的场景将被绘制，但所有预定的定时器将被暂停
     暂停时，绘制周期将只有4个FPS，以降低CPU消耗
     */
    void pause();

    /** Resumes the paused scene
     The scheduled timers will be activated again.
     The "delta time" will be 0 (as if the game wasn't paused)
     
     恢复暂停的场景
     预定的定时器将被再次激活。
     “推迟执行”的时间将是0（如果游戏没有暂停）
     */
    void resume();

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     If you don't want to pause your animation call [pause] instead.
     
     停止动画，什么也不画. 主循环线程再也不会被触发.
     如果你不希望那样，那么就用暂停你的游戏代替
     */
    virtual void stopAnimation() = 0;

    /** The main loop is triggered again.
     Call this function only if [stopAnimation] was called earlier
     @warning Don't call this function to start the main loop. To run the main loop call runWithScene
     
     
     主循环线程重新被触发.
     这个函数只在你已经调用 [stopAnimation] 函数的时候调用
     @warning 不要使用这个函数启动主线程循环. 请使用 主线程调用 runWithScene
     */
    virtual void startAnimation() = 0;

    /** Draw the scene.
    This method is called every frame. Don't call it manually.
     
     绘制场景.
     这个方法每一帧都会调用，不要手动调用这个方法.
    */
    void drawScene();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    // Memory Helper 内存助手

    /** Removes all cocos2d cached data.
     It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     
     移除所有 cocos2d 缓存数据.
     他将清除 TextureCache, SpriteFrameCache, LabelBMFont 缓存
     
     @since v0.99.3
     */
    void purgeCachedData();

	/** sets the default values based on the Configuration info
     设置配置信息的默认值
     */
    void setDefaultValues();
    
    
    
    
    
    
    
    
    
    
    

    // OpenGL Helper

    /** sets the OpenGL default values 
        设置 OpenGL 默认值
     */
    void setGLDefaultValues();

    /** enables/disables OpenGL alpha blending
        启用/禁用 OpenGL alpha 混合
     */
    void setAlphaBlending(bool on);

    /** enables/disables OpenGL depth test
        启用/禁用 OpenGL 深度测试
     */
    void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** The size in pixels of the surface. It could be different than the screen size.
    High-res devices might have a higher surface size than the screen size.
    Only available when compiled using SDK >= 4.0.
     
     
     基于像素 surface 尺寸. 它可以和屏幕尺寸不同
     High-res(高分辨率) 设备或许有一个高于屏幕尺寸 surface 尺寸
     只在编译 SDK >= 4.0 时有效.
     
     
    @since v0.99.4
    */
    void setContentScaleFactor(float scaleFactor);
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** Gets the Scheduler associated with this director
     
     Gets 和这个 director 关联的预定的定时器
     @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** Sets the Scheduler associated with this director
     
     Sets 和这个 director 关联的预定的定时器
     @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** Gets the ActionManager associated with this director
     
     Gets  和这个 director 关联 ActionManager
     @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** Sets the ActionManager associated with this director
     Sets 和这个 director 关联 ActionManager
     @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** Gets the EventDispatcher associated with this director 
     
     获得和director 关联的EventDispatcher
     @since v3.0
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** Sets the EventDispatcher associated with this director 
     
     设置和director 关联的EventDispatcher
     @since v3.0
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** Returns the Renderer
     @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** Returns the Console 
     @since v3.0
     */
#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    Console* getConsole() const { return _console; }
#endif

    /* Gets delta time since last tick to main loop
        Gets 获取主循环线程之间的延迟时间
     */
	float getDeltaTime() const;
    
    /**
     *  get Frame Rate
     *  获得帧频
     */
    float getFrameRate() const { return _frameRate; }

protected:
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // this flag will be set to true in end()
    //在 end() 这个参数将会被设置成 true
    
    void setNextScene();
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
    
    /** calculates delta time since last time it was called 
        
     计算上次和这次主循环线程之间的延迟时间
    */
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    /** Scheduler associated with this director
     
        和 director 关联的定时器
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** ActionManager associated with this director
     
      和 director 关联的ActionManager
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** EventDispatcher associated with this director
     
      和 director 关联的EventDispatcher
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventAfterUpdate;
        
    /* delta time since last tick to main loop 
        自从上次触发主循环线程的延迟时间
     */
	float _deltaTime;
    
    /* 
     * The GLView, where everything is rendered
     * GLView,呈现一切的地方
     */
    GLView *_openGLView;

    //texture cache belongs to this director 属于这个导演的纹理缓存
    TextureCache *_textureCache;

    double _animationInterval;
    double _oldAnimationInterval;

    /* landscape mode ?  是否 ?  */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_drawnBatchesLabel;
    LabelAtlas *_drawnVerticesLabel;
    
    /** Whether or not the Director is paused 
        Director是否暂停了
     */
    bool _paused;

    /* How many frames were called since the director started 
     director 启动后到现在经过了多少帧
     */
    unsigned int _totalFrames;
    unsigned int _frames;
    float _secondsPerFrame;
    
    /* The running scene 
        正在运行的场景
     */
    Scene *_runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference.
      下一帧将要运行的场景，下一帧将要运行的场景是弱引用
     */
    Scene *_nextScene;
    
    /* If true, then "old" scene will receive the cleanup message 
     
        true, 那么 "old" 旧的场景会收到清除信息
     */
    bool _sendCleanupToScene;

    /* scheduled scenes 
       定时器里面的场景数组
     */
    Vector<Scene*> _scenesStack;
    
    /* last time the main loop was updated
       主循环线程上次更新时间
     */
    struct timeval *_lastUpdate;

    /* whether or not the next delta time will be zero
     
        是否将下次延迟时间设置为0
     */
    bool _nextDeltaTimeZero;
    
    /* projection used 
     使用的投影
     */
    Projection _projection;

    /* window size in points 
     点组成的窗口尺寸
    */
    Size _winSizeInPoints;
    
    /* content scale factor
     内容scale因子
     */
    float _contentScaleFactor;

    /* This object will be visited after the scene. Useful to hook a notification node
        主场景访问后这个对象将被访问，和通知对象挂钩
     */
    Node *_notificationNode;

    /* Renderer for the Director */
    Renderer *_renderer;

#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    /* Console for the director */
    Console *_console;
#endif

    // GLViewProtocol will recreate stats labels to fit visible rect
    // GLViewProtocol 将重新创建 labels 的属性，以适应可见部分的矩形
    friend class GLViewProtocol;
};















/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 
 @brief简要 DisplayLinkDirector 是一个 synchronizes 屏幕刷新速率的同步计时器
 
 特点和局限性:
 - 预定的定时器 & 绘制 synchronizes 屏幕刷新速率
 - 只支持动画间隔时 1/60 1/30 & 1/15 的情况
 
 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop() override;
    virtual void setAnimationInterval(double value) override;
    virtual void startAnimation() override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
