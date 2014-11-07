#include "AppDelegate.h"
#include "PublicDef.h"
#include "NFLogoScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}


void copyData(const char* pFileName)
{
    std::string strPath = CCFileUtils::getInstance()->fullPathForFilename(pFileName);
    ssize_t len=0;
    unsigned char* data =NULL;
    data = CCFileUtils::getInstance()->getFileData(strPath.c_str(),"r",&len);
    
    std::string destPath = CCFileUtils::getInstance()->getWritablePath();
    destPath+= pFileName;

    FILE *pFp=fopen(destPath.c_str(),"w+");
    fwrite(data,sizeof(char),len,pFp);
    fclose(pFp);
    delete []data;
    data=NULL;
    
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    copyData(_TR_STATIC_DATABASE_FILE_NAME_);
    //版本修改的
    // initialize director
//    CCDirector* pDirector = CCDirector::getInstance();
//    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    auto pDirector = Director::getInstance();
    auto pEGLView = pDirector->getOpenGLView();
    
    
    if(!pEGLView) {
        pEGLView = GLView::create("Cpp Empty Test");
        pDirector->setOpenGLView(pEGLView);
    }
    
    pDirector->setOpenGLView(pEGLView);
    
    pEGLView->setDesignResolutionSize(720,480,kResolutionFixedHeight);

    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //版本修改的
//    CCScene *pScene = CNFLogoScene::scene();
//    pDirector->runWithScene(pScene);
//    auto pScene = CNFLogoScene::create();
//    pDirector->runWithScene(pScene);
    auto scenex = CNFLogoScene::create();
    pDirector->runWithScene(scenex);
    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
