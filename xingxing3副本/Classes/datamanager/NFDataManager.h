
#ifndef _NF_DATA_MANAGER_HEAD_
#define _NF_DATA_MANAGER_HEAD_

#include "PublicDef.h"

//////数据库的方法/////////

/** 从表里面获取int类型的数据*/
int GetIntFromTable(char * szItemName, int n_column, char ** column_value, char ** column_name);
/** 从表里面获取float类型的数据*/
float GetFloatFromTable(char * szItemName, int n_column, char ** column_value, char ** column_name);
/** 从表里面获取string类型的数据*/
string GetStringFromTable(char * szItemName, int n_column, char ** column_value, char ** column_name);







































/************************************************************************/
/*					静态数据结构体                                                                     */
/************************************************************************/
//关卡静态信息结构体  t_stage_info 数据库表的信息
struct tagStageStaticInfo
{
    float 					fRate;					//世界倾斜角度（y轴）
    float					fGravity;				//重力（z轴减速度）
    float					fLength;				//长（3D世界）
    float					fWidth;					//宽（3D世界）
    float					fHeight;				//高（3D世界）
    float					fProtagonistX;			//主角x初始轴坐标
    float					fProtagonistY;			//主角y初始轴坐标
    float					fProtagonistZ;			//主角z初始轴坐标
    string					strTMXWorldName;		//景深地图世界的名字
    CNFTmxStaticInfoMap		TmxStaticInfoMap;		//景深地图map
    CNFNPCJsonInfoVec		NPCJsonInfoVec;			//NPC JSON 信息
    CNFDoorJsonInfoVec		DoorJsonInfoVec;		//Door Json 信息
};
typedef map<int,tagStageStaticInfo> CNFStageStaticInfoMap;		//关卡静态信息map，通过关卡ID，获得关卡信息




































class CNFStaticDataManager
{
	CNFStaticDataManager();

protected:
	
    CNFSkillStaticInfoMapByProtagonistID	m_SkillStaticInfoMap;
    
    /**map 类型的npc信息容器声明*/
    CNFNPCStaticInfoMap						m_NPCStaticInfoMap;
    
    /**map 类型的door信息容器声明*/
    CNFDoorStaticInfoMap					m_DoorStaticInfoMap;
    
    /**关卡静态信息*/
    CNFStageStaticInfoMap					m_StageStaticInfoMap;
public:
	static CNFStaticDataManager *SharedData();
	void initBasicData();			//
	static void ReleaseData();		//

    bool GetSkillStaticInfo(const int nRoleID,const int nSkillID,tagSkillStaticInfo &Info);
    
    
    
    //获得npc静态信息（根据npcID）
    bool GetNPCStaticInfo(const int nNPCID,tagNPCStaticInfo &Info);
    /**读取npc 的数据,读取sqlite的数据库的数据*/
    bool ReadNPCStaticFromDB();
    /**读取Npc数据库数据成功的回调*/
	static int LoadNPCStaticCallBack(void * para, int n_column, char ** column_value, char ** column_name);
    
    
    
    //获得door静态信息（根据Door ID）
    bool GetDoorStaticInfo(const int nDoorID,tagDoorStaticInfo &Info);
    /**读取Door 的数据,读取sqlite的数据库的数据*/
    bool ReadDoorStaticFromDB();
     /**读取Door数据库数据成功的回调*/
    static int LoadDoorStaticCallBack(void * para, int n_column, char ** column_value, char ** column_name);
    
    
    
    
    /**读取关卡静态信息*/
    bool ReadStageStaticFromDB();
    static int LoadStageStaticCallBack(void * para, int n_column, char ** column_value, char ** column_name);

};
























































































struct tagSaveUserInfo 
{
	string		strOpenID;					//”√ªßID£¨Œ®“ª±Í ∂
	string		strUserName;				//”√ªß–’√˚
	string		strPassWord;				//”√ªß√‹¬Î
};

//∑˛ŒÒ∆˜–≈œ¢
struct tagSaveServerInfo
{
	int			nServerID;					//∑˛ŒÒ∆˜ID
	string		strServerName;				//∑˛ŒÒ∆˜√˚≥∆
};

/************************************************************************/
/*					¥Ê¥¢ ˝æ›π‹¿Ì¿‡                                                                   */
/************************************************************************/
class CNFSaveDataManager
{
	CNFSaveDataManager();

protected:
	tagSaveUserInfo				m_SaveUserInfo;
	tagSaveServerInfo			m_SaveServerInfo;
    
    

public:
	static CNFSaveDataManager *SharedData();
	void initBasicData();			
	static void ReleaseData();
    
    


};











#endif