#include "NFLogoScene.h"
#include "NFDataManager.h"

bool CNFLogoScene::init()
{
	do 
	{
        /************************************************************************/
        /*				初始化数据库                                                                     */
        /************************************************************************/
        CNFStaticDataManager::SharedData()->initBasicData();
        CNFSaveDataManager::SharedData()->initBasicData();
        
        tagSkillStaticInfo Info;
        CNFStaticDataManager::SharedData()->GetSkillStaticInfo(1,1,Info);
        
        
        
        
        
        
        
        
        //初始化父类
        CC_BREAK_IF(Scene::init()==false);
        
        
        
        
        
        
        /************************************************************************/
        /*			背景图片                                                                     */
        /************************************************************************/
        //创建logo图片
        
        //版本修改的
//        CCSprite * pLogoBg = CCSprite::create("ui/logo_bg.png");
//        Sprite * pLogoBg = Sprite::create("ui/logo_bg.png");
        Sprite * pLogoBg = Sprite::create("logo_bg.png");
//        auto pLogoBg = Sprite::create("logo_bg.png");
        CC_BREAK_IF(pLogoBg==NULL);
        pLogoBg->setPosition(SCREEN_CENTER);
        addChild(pLogoBg,enZOrderFront);
        
        
        
        /************************************************************************/
        /*			1.UI：联网，确认是否有网络                                                                     */
        /************************************************************************/
        bool bIsNet = false;
        bIsNet = true;
        
        //若有网络
        if (bIsNet == true)
        {
            //延迟1秒
            this->runAction(Sequence::create(
                                               DelayTime::create(1.f),
//版本修改的
// CallFunc::create(this,callfunc_selector(CNFLogoScene::OnChangeScene)),
   CallFunc::create(CC_CALLBACK_0(CNFLogoScene::OnChangeScene,this)),
                                               NULL));
        }
        //若无网络
        else
        {
            ////延迟2秒
            //this->runAction(CCSequence::create(
            //	CCDelayTime::create(1.f),
            //	CCCallFunc::create(this,callfunc_selector(CNFLogoScene::OnAddTipLayer)),
            //	NULL));
        }
        
        return true;
	} while (false);

	return false;
}

//
void CNFLogoScene::OnChangeScene()
{
	do 
	{
        //跳转到服务器选择界面
//        CCScene * pScene = CNFLoginScene::scene();
//        CC_BREAK_IF(pScene==NULL);
//        Director::getInstance()->replaceScene(CCTransitionFade::create(1.f,pScene));
        
        return ;
	} while (false);
	
}




