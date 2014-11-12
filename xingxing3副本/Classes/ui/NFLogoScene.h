#ifndef _NF_LOGO_SCENE_HEAD_
#define _NF_LOGO_SCENE_HEAD_

#include "PublicDef.h"
#include "cocos2d.h"
#include "NFDataManager.h"
//class CNFLogoScene : public CCLayer

using namespace cocos2d;
class CNFLogoScene : public Scene{
public:
    virtual bool init();
    
    static CCScene * scene();
    
    CREATE_FUNC(CNFLogoScene);
protected:
    void OnChangeScene();
};


#endif