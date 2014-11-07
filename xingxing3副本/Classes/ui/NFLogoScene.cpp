#include "NFLogoScene.h"
#include "NFDataManager.h"

bool CNFLogoScene::init()
{
	do 
	{
	
        CNFStaticDataManager::SharedData()->initBasicData();
        CNFSaveDataManager::SharedData()->initBasicData();
        
        tagSkillStaticInfo Info;
        CNFStaticDataManager::SharedData()->GetSkillStaticInfo(1,1,Info);
        
		return true;
	} while (false);

	return false;
}

//
void CNFLogoScene::OnChangeScene()
{
	do 
	{
	
		return ;
	} while (false);
	
}




