//
//  PublicDef.h
//  xingxing3
//
//  Created by 瑛峰 on 14/10/29.
//
//


#ifndef _PUBLIC_DEF_HEAD_
#define _PUBLIC_DEF_HEAD_

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

#include <map>

USING_NS_CC;
USING_NS_CC_EXT;


using namespace cocos2d;
using namespace std;
using namespace cocostudio;  //版本修改的


//静态数据管理
#define _TR_STATIC_DATABASE_FILE_NAME_		"nf_static.db"


#define NAME_LEN			128

std::string GetStaticDataName();




/**
 
 //tagSkillStaticInfo【技能静态信息结构体】 ---> CNFSkillItemVec(tagSkillItemStaticInfo) 技能块容器
 
 
 //tagSkillItemStaticInfo 包含 （CNFBuffStaticInfoVec【buf】技能buf，tagSkillChangeInfo【自身的变化信息】，tagSkillDamageInfo【伤害信息】）
 
 //tagSkillDamageInfo【伤害信息】 还包含 CNFBuffStaticInfoVec【buf】 伤害buf
 
 
 */


//     buff(debuff)静态信息结构体
struct tagBuffStaticInfo
{
    int			nBuffID;		//buffID
    int			nBuffTime;		//buff持续时间
    int			nBuffTime_g;	//buff持续时间成长
    float		fBuffPoint1;	//buff点数1
    float		fBuffPoint1_g;	//buff点数1成长
    float		fBuffPoint2;	//buff点数2
    float		fBuffPoint2_g;	//buff点数2成长
};
typedef vector<tagBuffStaticInfo> CNFBuffStaticInfoVec;	//buff静态信息

//关键2：技能块伤害信息
struct tagSkillDamageInfo
{
    CNFBuffStaticInfoVec	vecTargetBuff;				//被攻击者的buff或debuff
    float					fDamagePoint;				//基础攻击力
    float					fDamagePoint_g;				//攻击力系数
    float					fDamagePercent;				//技能百分比
    float					fDamagePercent_g;			//技能百分比成长
    float					fXDis;						//被攻击者x轴的变化量
    float					fXTime;						//被攻击者x轴的变化时间
    float					fYDis;						//被攻击者y轴的变化量
    float					fYTime;						//被攻击者y轴的变化时间
    float					fZSpeed;					//被攻击者z轴的速度变化
    int						nIsConversely;				//被攻击者是否倒地		1.倒地	0.不倒地
    int						nCrickAdd;					//被攻击者硬直增加量
    int						nAttackSpeed;				//攻击之间的间隔（帧）
    int						nIsExplodeMode;				//是否为爆炸模式		1.是	0.不是
    int						nIsPullMode;				//是否为拉近到面前模式	1.是	0.不是
    
    int						nCritAdd;					//暴击率增加量
    float					fCritDamageAdd;				//暴击伤害增加量
    int						nHitTargetAdd;				//命中增加量
    int						nIsDirection;				//是否有方向			1.有	0.没有
    
    int						nIsSuctionMode;				//是否为吸引模式		1.是	0.不是
    float					fSuctionSpeed;				//吸引的速度
    float					fSuctionTime;				//吸引的时间（秒）
    float					fSuctionPosX;				//吸引到的x轴位置：相对于角色，面部向右
    float					fSuctionPosY;				//吸引到的y轴位置
    
    int						nIsOnlyDamageNotHit;		//是否只受到伤害，但不播放被击动画（用于地面AOE）	1.是	0.不是
    int						nIsSuctionSkillItemCenter;	//是否吸引到技能块中心	1.是	0.不是			ps：若“是”，则fSuctionPosX和fSuctionPosY无意义。
    
    int						nIsDamage;					//是否计算伤害			1.是	0.不是
    int						nIsFollow;					//技能块是否跟随释放者	1.是	0.不是
    
    int						nIsBreakSiperarmor;			//是否破霸体
    int						nHitEffectType;				//拳花类型				
    
};




//关键2：技能块自身的变化信息
struct tagSkillChangeInfo
{
    float		fChangeTime;		//变化时间
    int 		nIsGravity;			//是否开启重力	1.开启	0.不开启
    
    float		fOldX;				//技能块，旧x轴位置
    float		fOldY;				//技能块，旧y轴位置
    float		fOldZ;				//技能块，旧z轴位置
    float		fOldLength;			//技能块，旧长度
    float		fOldWidth;			//技能块，旧宽度
    float		fOldHeight;			//技能块，旧高度
    
    float		fNewX;				//技能块，新x轴位置
    float		fNewY;				//技能块，新y轴位置
    float		fNewZ;				//技能块，新z轴位置
    float		fNewLength;			//技能块，新长度
    float		fNewWidth;			//技能块，新宽度
    float		fNewHeight;			//技能块，新高度
    
    
};


//关键2：技能Item结构体
struct tagSkillItemStaticInfo
{
    bool					bIsCommonSkill;			//是否为普通攻击
    float					fDelayTime;				//延迟时间
    float					fDisX;					//释放者，x轴位移量
    float					fTimeX;					//释放者，x轴时间
    float					fDisY;					//释放者，y轴位移量
    float					fTimeY;					//释放者，y轴时间
    float					fSpeedZ;				//释放者，z轴速度
    int						nScreenIsShake;			//屏幕是否震动	1.震动	0.不震动
    float					fShakeDurTime;			//屏幕震动持续时间（秒）
    float					fShakeDegree;			//屏幕震动幅度
    int						nShakeCount;			//屏幕震动次数
    int						nIsLensfeatrue;			//屏幕是否拉伸
    float					fLensfeatureTime;		//屏幕拉伸时间（秒）
    int						nIsScreenChangeColor;	//屏幕是否改变颜色	0.不改变	1.变黑
    float					fScreenChangeColorTime;	//屏幕颜色改变时间（秒）
    int						nIsTurnRound;			//释放者是否转头	1.是	0.不是
    
    CNFBuffStaticInfoVec	vecBuff;				//释放者的buff或debuff
    tagSkillChangeInfo		tSkillChange;			//技能块，自身变化信息
    tagSkillDamageInfo		tSkillDamage;			//技能块，伤害信息
    
    int						nIsArmature;			//技能块，是否有骨骼动画：1.有	0，没有
    string					strArmatureName;		//骨骼动画名称
    int						nIsSound;				//技能块，是否有音效：1.有	0，没有
    string					strSoundName;			//音效名称
};

typedef	vector<tagSkillItemStaticInfo> CNFSkillItemVec;		//技能块容器
//关键1：技能静态信息结构体
struct tagSkillStaticInfo
{
    int					nSkillID;					//技能ID
    int					nIsCommonSkill;				//是否为普通攻击：1.是	0.不是
    int					nSkillCD;					//技能CD（帧）
    int					nSkillCD_g;					//技能CD成长
    float				fCostMp;					//魔法消耗
    float				fCostMp_g;					//魔法消耗成长
    string				strAniName;					//动画名称
    string				strSkillName;				//技能名称
    string				strSkillIntroduce;			//技能介绍
    CNFSkillItemVec		vecSkillItem;				//技能块容器
    
};






typedef		map<int,tagSkillStaticInfo>				CNFSkillStaticMapBySkillID;				//通过技能ID，得到tagSkillStaticInfo
typedef		map<int,CNFSkillStaticMapBySkillID>		CNFSkillStaticInfoMapByProtagonistID;	//通过主角ID，得到CNFSkillStaticMapBySkillID












































/************************************************************************/
/*					主角AI                                              */
/************************************************************************/
//治疗技能
struct tagTreatSkillInfo
{
    int			nSkillID;				//技能ID
    float		fBloodPer;				//触发加血技能的hp最低百分比
};
typedef	vector<tagTreatSkillInfo>		CNFTreatSkillVec;		//治疗技能容器

//必然技能
struct tagMustSkillInfo
{
    int			nSkillID;				//技能ID
};
typedef	vector<tagMustSkillInfo>		CNFMustSkillVec;		//必然技能容器

//距离技能块
struct tagDistanceItem
{
    int			nSkillID;				//技能ID
    int			nDelayTime;				//延迟时间（帧），总时间
};
typedef	vector<tagDistanceItem>			CNFDistanceItemVec;		//距离技能块容器

//距离技能
struct tagDistanceSkillInfo
{
    float					fSkillDistance;			//释放技能的距离范围
    CNFDistanceItemVec		vecDistanceItem;		//距离技能块容器
};
typedef	vector<tagDistanceSkillInfo>	CNFDistanceSkillVec;	//距离技能容器


//主角Ai结构体
struct tagProtagonistAIInfo
{
    CNFTreatSkillVec		vecTreatSkill;			//治疗技能
    CNFMustSkillVec			vecMustSkill;			//必然技能
    CNFDistanceSkillVec		vecDistanceSkill;		//距离技能
};
//typedef map<int,tagProtagonistAIInfo>	CNFProtagonistAIMap;	//主句ai容器




























/************************************************************************/
/*				       NPC                          */
/************************************************************************/
//ncp静态信息结构体
struct tagNPCStaticInfo
{
    string			strArmatureName;		//NPC 动画名称
    float			fLength;				//NPC 长度
    float			fWidth;					//NPC 宽度
    float			fHeight;				//NPC 高度
};
/**NPC静态信息容器*/
typedef map<int,tagNPCStaticInfo>	CNFNPCStaticInfoMap;

//npc Json信息
struct tagNPCJsonInfo
{
    int					nNPCID;					//NPC ID
    float				fPosX;					//NPC x轴位置
    float				fPosY;					//NPC y轴位置
    float				fPosZ;					//NPC z轴位置
    tagNPCStaticInfo	NPCStaticInfo;			//NPC 静态信息
};
typedef vector<tagNPCJsonInfo>	CNFNPCJsonInfoVec;		//NPC Json 信息容器













/************************************************************************/
/*					DOOR                 */
/************************************************************************/
//door静态信息结构体
struct tagDoorStaticInfo
{
    string			strArmatureName;		//Door 动画名称
    float			fLength;				//Door 长度
    float			fWidth;					//Door 宽度
    float			fHeight;				//Door 高度
    int				nRelaceStageID;			//Door 跳转到的关卡ID
};
typedef map<int,tagDoorStaticInfo>	CNFDoorStaticInfoMap;		//Door静态信息容器

//door Json信息
struct tagDoorJsonInfo
{
    int					nDoorID;				//Door ID
    float				fPosX;					//Door x轴位置
    float				fPosY;					//Door y轴位置
    float				fPosZ;					//Door z轴位置
    tagDoorStaticInfo	DoorStaticInfo;			//Door 静态信息
};
typedef vector<tagDoorJsonInfo>	CNFDoorJsonInfoVec;		//Door Json 信息容器






























/************************************************************************/
/*				结构体                                                                     */
/************************************************************************/
//景深地图信息结构体
struct tagTmxStaticInfo
{
    string	strTmxName;			//景深地图名字
    float	fStartPosX;			//景深地图x轴初始位置
    float	fStartPosY;			//景深地图y轴初始位置
};
typedef map<int,tagTmxStaticInfo>	CNFTmxStaticInfoMap;	//景深地图静态信息map









#endif /* defined(_PUBLIC_DEF_HEAD_) */
