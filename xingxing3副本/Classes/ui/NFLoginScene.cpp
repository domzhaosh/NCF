//
//  NFLoginScene.cpp
//  NCF
//
//  Created by 瑛峰 on 14/11/12.
//
//

#include "NFLoginScene.h"


/************************************************************************/
/*			登录场景													*/
/************************************************************************/
Scene* CNFLoginScene::scene()
{
    do
    {
        Scene* pScene = Scene::create();
        CC_BREAK_IF(pScene==NULL);
        
        CNFLoginScene* pLayer = CNFLoginScene::create();
        CC_BREAK_IF(pLayer==NULL);
        
        pScene->addChild(pLayer);
        return pScene;
        
    } while (false);
    log("Fun CNFLoginScene::scene Error!");
    return NULL;
}



void CNFLoginScene::onEnter()
{
    CCLayer::onEnter();
    do
    {
        
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::onEnter Error!");
}


void CNFLoginScene::RecMsg( int nMsgID,void* pInfo,int nSize )
{
   
}


void CNFLoginScene::InitSceneUI()
{
    
}
