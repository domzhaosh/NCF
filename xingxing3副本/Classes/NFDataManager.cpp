//
//  NFDataManager.cpp
//  NCF
//
//  Created by 瑛峰 on 14/10/29.
//
//

#include "NFDataManager.h"
#include "NFJsonTranslater.h"
#include "PublicDef.h"
#include "sqlite3.h"
//#include <algorithm>





int GetIntFromTable( char * szItemName, int n_column, char ** column_value, char ** column_name )
{
    for(int i=0;i<n_column;i++)
    {
        if(strcmp(column_name[i],szItemName)==0) //比较字符串。string1 等同于 string2。返回0
        {
            return atoi(column_value[i]);  //转换string to integer
        }
    }
    CCLOG("Can't Find int [%s]",szItemName);
    return 0;
}

float GetFloatFromTable( char * szItemName, int n_column, char ** column_value, char ** column_name )
{
    for(int i=0;i<n_column;i++)
    {
        if(strcmp(column_name[i],szItemName)==0)
        {
            return atof(column_value[i]);
        }
    }
    CCLOG("Can't Find float [%s]",szItemName);
    return 0;
}

string GetStringFromTable( char * szItemName, int n_column, char ** column_value, char ** column_name)
{
    for(int i=0;i<n_column;i++)
    {
        if(strcmp(column_name[i],szItemName)==0)
        {
            return column_value[i];
        }
    }
    CCLOG("Can't Find string [%s]",szItemName);
    return NULL;
}



/*****************************************************************
 *
 *  以上是 数据库相关的方法
 *
 *****************************************************************
 */















/////////////////////////////////////////////////////////////
/** 存放NPC静态数据的类 声明*/
static CNFStaticDataManager * g_pStaticDataManager=NULL;

/** 存放NPC静态数据的类*/
CNFStaticDataManager::CNFStaticDataManager()
{
   
}
CNFStaticDataManager * CNFStaticDataManager::SharedData()
{
    if(g_pStaticDataManager==NULL)
    {
        g_pStaticDataManager = new CNFStaticDataManager();
    }
    return g_pStaticDataManager;
}

void CNFStaticDataManager::initBasicData()
{
    do
    {
        //读取npc静态信息：必须在读取关卡信息之前读取
        ReadNPCStaticFromDB();
        
        //读取door静态信息：必须在读取关卡信息之前读取
        ReadDoorStaticFromDB();
        
        //读取关卡信息
        ReadStageStaticFromDB();
        
        
        
       
        
        return ;
    } while (false);
    
}


void CNFStaticDataManager::ReleaseData()
{
}


bool CNFStaticDataManager::GetSkillStaticInfo( const int nRoleID,const int nSkillID,tagSkillStaticInfo &Info )
{
    CNFSkillStaticInfoMapByProtagonistID::iterator iFind = m_SkillStaticInfoMap.find(nRoleID);
    if (iFind!=m_SkillStaticInfoMap.end())
    {
        CNFSkillStaticMapBySkillID::iterator it = iFind->second.find(nSkillID);
        if (it!=iFind->second.end())
        {
            Info=m_SkillStaticInfoMap[nRoleID][nSkillID];
            return true;
        }
    }
    
    
    return false;
}















/************************************************************************/
/*					  NPC静态信息                                                                   */
/************************************************************************/
bool CNFStaticDataManager::GetNPCStaticInfo( const int nNPCID,tagNPCStaticInfo &Info )
{
    CNFNPCStaticInfoMap::iterator iFind = m_NPCStaticInfoMap.find(nNPCID);
    if (iFind==m_NPCStaticInfoMap.end())
        return false;
    
    Info=m_NPCStaticInfoMap[nNPCID];
    return true;
}

//读取npc 的数据,读取sqlite的数据库的数据

bool CNFStaticDataManager::ReadNPCStaticFromDB()
{
    char *szErrMsg=NULL;
    do
    {
        sqlite3 *pDB=NULL;
        CC_BREAK_IF(sqlite3_open(GetStaticDataName().c_str(),&pDB)!=SQLITE_OK);
        CC_BREAK_IF(pDB==NULL);
        
        CC_BREAK_IF(sqlite3_exec(pDB,"SELECT * from t_npc_info",CNFStaticDataManager::LoadNPCStaticCallBack, NULL, &szErrMsg )!=SQLITE_OK);
        sqlite3_close(pDB);
        
        return true;
    } while (false);
//    CCLog("CNFStaticDataManager::ReadNPCStaticFromDB Run Error! Msg=%s ",szErrMsg);
    return false;
}


//读取数据库成功的回调
int CNFStaticDataManager::LoadNPCStaticCallBack( void * para, int n_column, char ** column_value, char ** column_name )
{
    if (g_pStaticDataManager==NULL)
    {
        g_pStaticDataManager = new CNFStaticDataManager();
    }
    //查询npcID
    int nNPCID = GetIntFromTable("i_npc_id",n_column,column_value,column_name);
    
    tagNPCStaticInfo Info;
    Info.strArmatureName = GetStringFromTable("s_armature_name",n_column,column_value,column_name);
    Info.fLength = GetFloatFromTable("f_length",n_column,column_value,column_name);
    Info.fWidth = GetFloatFromTable("f_width",n_column,column_value,column_name);
    Info.fHeight = GetFloatFromTable("f_height",n_column,column_value,column_name);
    
    g_pStaticDataManager->m_NPCStaticInfoMap[nNPCID] = Info;
    
    return 0;
}

























/************************************************************************/
/*					  Door静态信息                                                                   */
/************************************************************************/
bool CNFStaticDataManager::GetDoorStaticInfo( const int nDoorID,tagDoorStaticInfo &Info )
{
    CNFDoorStaticInfoMap::iterator iFind = m_DoorStaticInfoMap.find(nDoorID);
    if (iFind==m_DoorStaticInfoMap.end())
        return false;
    
    Info=m_DoorStaticInfoMap[nDoorID];
    return true;
}

bool CNFStaticDataManager::ReadDoorStaticFromDB()
{
    char *szErrMsg=NULL;
    do
    {
        sqlite3 *pDB=NULL;
        CC_BREAK_IF(sqlite3_open(GetStaticDataName().c_str(),&pDB)!=SQLITE_OK);
        CC_BREAK_IF(pDB==NULL);
        
        CC_BREAK_IF(sqlite3_exec(pDB,"SELECT * from t_door_info",CNFStaticDataManager::LoadDoorStaticCallBack, NULL, &szErrMsg )!=SQLITE_OK);
        sqlite3_close(pDB);
        
        return true;
    } while (false);
    log("CNFStaticDataManager::ReadDoorStaticFromDB Run Error! Msg=%s ",szErrMsg);
    return false;
}


int CNFStaticDataManager::LoadDoorStaticCallBack( void * para, int n_column, char ** column_value, char ** column_name )
{
    if (g_pStaticDataManager==NULL)
    {
        g_pStaticDataManager = new CNFStaticDataManager();
    }
    
    int nDoorID = GetIntFromTable("i_door_id",n_column,column_value,column_name);
    
    tagDoorStaticInfo Info;
    Info.nRelaceStageID = GetIntFromTable("i_replace_stage_id",n_column,column_value,column_name);
    Info.strArmatureName = GetStringFromTable("s_armature_name",n_column,column_value,column_name);
    Info.fLength = GetFloatFromTable("f_length",n_column,column_value,column_name);
    Info.fWidth = GetFloatFromTable("f_width",n_column,column_value,column_name);
    Info.fHeight = GetFloatFromTable("f_height",n_column,column_value,column_name);
    
    g_pStaticDataManager->m_DoorStaticInfoMap[nDoorID] = Info;
    
    return 0;
}


























/**读取关卡静态信息*/
bool CNFStaticDataManager::ReadStageStaticFromDB()
{
    char *szErrMsg=NULL;
    do
    {
        sqlite3 *pDB=NULL;
        CC_BREAK_IF(sqlite3_open(GetStaticDataName().c_str(),&pDB)!=SQLITE_OK);
        CC_BREAK_IF(pDB==NULL);
        
        CC_BREAK_IF(sqlite3_exec(pDB,"SELECT * from t_stage_info",CNFStaticDataManager::LoadStageStaticCallBack, NULL, &szErrMsg )!=SQLITE_OK);
        sqlite3_close(pDB);
        
        return true;
    } while (false);
    CCLog("CNFStaticDataManager::ReadStageStaticFromDB Run Error! Msg=%s ",szErrMsg);
    return false;
}

 /**读取关卡静态信息数据库回调*/
int CNFStaticDataManager::LoadStageStaticCallBack( void * para, int n_column, char ** column_value, char ** column_name )
{
    if (g_pStaticDataManager==NULL)
    {
        g_pStaticDataManager = new CNFStaticDataManager();
    }
    
    int nStageID = GetIntFromTable("i_stage_id",n_column,column_value,column_name);
    
    tagStageStaticInfo NewStageStaticInfo;
    NewStageStaticInfo.fRate = GetFloatFromTable("f_stage_rate",n_column,column_value,column_name);
    NewStageStaticInfo.fGravity = GetFloatFromTable("f_stage_gravity",n_column,column_value,column_name);
    NewStageStaticInfo.fLength = GetFloatFromTable("f_3d_length",n_column,column_value,column_name);
    NewStageStaticInfo.fWidth = GetFloatFromTable("f_3d_width",n_column,column_value,column_name);
    NewStageStaticInfo.fHeight = GetFloatFromTable("f_3d_height",n_column,column_value,column_name);
    NewStageStaticInfo.fProtagonistX =GetFloatFromTable("f_protagonist_x",n_column,column_value,column_name);
    NewStageStaticInfo.fProtagonistY = GetFloatFromTable("f_protagonist_y",n_column,column_value,column_name);
    NewStageStaticInfo.fProtagonistZ = GetFloatFromTable("f_protagonist_z",n_column,column_value,column_name);
    NewStageStaticInfo.strTMXWorldName = GetStringFromTable("s_tmx_world_name",n_column,column_value,column_name);
    
    //得到tmx地图 Json信息
    string strTmxJson = GetStringFromTable("s_tmx_json",n_column,column_value,column_name);
    CNFJsonTranslater::SharedData()->GetTmxInfoFromJson(strTmxJson.c_str(),NewStageStaticInfo.TmxStaticInfoMap,nStageID);
    
    //得到npc Json信息
    string strNPCJson = GetStringFromTable("s_npc_json",n_column,column_value,column_name);
    CNFJsonTranslater::SharedData()->GetNPCInfoFromJson(strNPCJson.c_str(),NewStageStaticInfo.NPCJsonInfoVec,nStageID);
    
    
    
    
    
    
    
    
    
    
    
    
    //得到npc 静态信息,
    //解析json 得到 {"npc_arr":[{"npc_id":1,"npc_x":200,"npc_y":700,"npc_z":0},{"npc_id":2,"npc_x":800,"npc_y":700,"npc_z":0}]}
    //数据结构是这样的：   vector<tagNPCJsonInfo>	CNFNPCJsonInfoVec; 就是NewStageStaticInfo.NPCJsonInfoVec
    for (CNFNPCJsonInfoVec::iterator iter = NewStageStaticInfo.NPCJsonInfoVec.begin();iter != NewStageStaticInfo.NPCJsonInfoVec.end();iter++)
        //获取从数据获得的npc 数据，就是上面存放在npc容器CNFNPCStaticInfoMap 里面的信息。
        CNFStaticDataManager::SharedData()->GetNPCStaticInfo(iter->nNPCID,iter->NPCStaticInfo);
    
    //得到door Json信息
    string strDoorJson = GetStringFromTable("s_door_json",n_column,column_value,column_name);
    CNFJsonTranslater::SharedData()->GetDoorInfoFromJson(strDoorJson.c_str(),NewStageStaticInfo.DoorJsonInfoVec,nStageID);
    //得到door 静态信息
    for (CNFDoorJsonInfoVec::iterator iter = NewStageStaticInfo.DoorJsonInfoVec.begin();iter != NewStageStaticInfo.DoorJsonInfoVec.end();iter++)
        CNFStaticDataManager::SharedData()->GetDoorStaticInfo(iter->nDoorID,iter->DoorStaticInfo);
    
    
    
    
    
    
    
    g_pStaticDataManager->m_StageStaticInfoMap[nStageID]=NewStageStaticInfo;
    
    
    
    
    
    return 0;
}









































////////////////////////////////////////////////////////////////////////////////////////

static CNFSaveDataManager * g_pSaveDataManager=NULL;
CNFSaveDataManager::CNFSaveDataManager()
{
}
CNFSaveDataManager * CNFSaveDataManager::SharedData()
{
    if(g_pSaveDataManager==NULL)
    {
        g_pSaveDataManager = new CNFSaveDataManager();
    }
    return g_pSaveDataManager;
}

void CNFSaveDataManager::ReleaseData()
{
}


void CNFSaveDataManager::initBasicData()
{
    do
    {
       
        
        return ;
    } while (false);
    
}