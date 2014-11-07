//
//  CNFJsonTranslater.cpp
//  NCF
//
//  Created by 瑛峰 on 14/11/5.
//
//

#include "NFJsonTranslater.h"

//输出头文件
//#include "CocoStudio/Json/rapidjson/stringbuffer.h"
//#include "CocoStudio/Json/rapidjson/writer.h

//Json错误判定标识
#define			_JSON_ERROR_ID_			-100000000
/************************************************************************/
/*					Json检验                                                                     */
/************************************************************************/
//校验Json：float型
float GetFloatFromJson(const rapidjson::Value& root, const char* key,int nDef1,int nDef2)
{
    //判断Json：错误，或者无此Json
    if ( _JSON_ERROR_ID_ == DICTOOL->getFloatValue_json(root, key,_JSON_ERROR_ID_) )
    {
        log("Float Json Error! [%s] [%d,%d]",key,nDef1,nDef2);
        return 0.f;
    }
    return DICTOOL->getFloatValue_json(root, key );
}
//校验Json：int型
int GetIntFromJson(const rapidjson::Value& root, const char* key,int nDef1,int nDef2)
{
    //判断Json：错误，或者无此Json
    if ( _JSON_ERROR_ID_ == DICTOOL->getIntValue_json(root, key,_JSON_ERROR_ID_) )
    {
        log("Int Json Error! [%s] [%d,%d]",key,nDef1,nDef2);
        return 0;
    }
    return DICTOOL->getIntValue_json(root, key );
}
//校验Json：string型
const char * GetStringFromJson(const rapidjson::Value& root, const char* key,int nDef1,int nDef2)
{
    //判断Json：错误，或者无此Json
    char szJsonErrorID[NAME_LEN] = {0};
    sprintf(szJsonErrorID,"%d",_JSON_ERROR_ID_);
    if ( strcmp(szJsonErrorID,DICTOOL->getStringValue_json(root, key,szJsonErrorID))==0  )
    {
        log("String Json Error! [%s] [%d,%d]",key,nDef1,nDef2);
        return "";
    }
    return DICTOOL->getStringValue_json(root, key );
}


















/************************************************************************/
/*					初始化Json                                                                     */
/************************************************************************/
static CNFJsonTranslater * g_pJsonTranslator=NULL;
CNFJsonTranslater * CNFJsonTranslater::SharedData()
{
    if(g_pJsonTranslator==NULL)
    {
        g_pJsonTranslator = new CNFJsonTranslater();
    }
    return g_pJsonTranslator;
}


//得到NPC信息
//{"npc_arr":[{"npc_id":1,"npc_x":200,"npc_y":700,"npc_z":0},{"npc_id":2,"npc_x":800,"npc_y":700,"npc_z":0}]}
bool CNFJsonTranslater::GetNPCInfoFromJson( const char * szJson,CNFNPCJsonInfoVec &Info,int nStageID )
{
    do
    {
        //创建Json
        rapidjson::Document json;
        
        //复制字符串数据
        json.Parse<0>(szJson);
        
        //校验Json
        if (json.HasParseError())
        {
            CCLOG("Fun CNFJsonTranslater::GetNPCInfoFromJson GetParseError %s\n",json.GetParseError());
        }
        
        int nArrayCount = DICTOOL->getArrayCount_json(json,_NPC_ARR_);
        for (int i = 0; i < nArrayCount; ++i)
        {
            const rapidjson::Value &ArrayJson = DICTOOL->getSubDictionary_json(json,_NPC_ARR_, i);
            
            tagNPCJsonInfo NPCInfo;
            NPCInfo.nNPCID = GetIntFromJson(ArrayJson,_NPC_ID_,nStageID);
            NPCInfo.fPosX = GetFloatFromJson(ArrayJson,_NPC_X_,nStageID);
            NPCInfo.fPosY = GetFloatFromJson(ArrayJson,_NPC_Y_,nStageID);
            NPCInfo.fPosZ = GetFloatFromJson(ArrayJson,_NPC_Z_,nStageID);
            
            Info.push_back(NPCInfo);
        }
        
        return true;
    } while (false);
    log("Fun CNFJsonTranslater::GetNPCInfoFromJson Error!");
    return false;
}



//得到景深地图信息
//{"tmx_array":[{"tmx_name":"map/town_1_3.tmx","tmx_start_pos_x":0,"tmx_start_pos_y":0},{"tmx_name":"map/town_1_2.tmx","tmx_start_pos_x":0,"tmx_start_pos_y":0}]}
bool CNFJsonTranslater::GetTmxInfoFromJson( const char * szJson,CNFTmxStaticInfoMap &Info,int nStageID)
{
    do
    {
        //创建Json
        rapidjson::Document json;
        
        //复制字符串数据
        json.Parse<0>(szJson);
        
        //校验Json
        if (json.HasParseError())
        {
            CCLOG("Fun CNFJsonTranslater::GetTmxInfoFromJson GetParseError %s\n",json.GetParseError());
        }
        
        
        //getArrayCount_json 获取 tmx数组大小
        int nArrayCount = DICTOOL->getArrayCount_json(json,_TMX_ARRAY_);
        for (int i = 0; i < nArrayCount; ++i)
        {
            //每一个子数组 ，tmx数组
            const rapidjson::Value &ArrayJson = DICTOOL->getSubDictionary_json(json,_TMX_ARRAY_, i);
            
            tagTmxStaticInfo TmxInfo;
            TmxInfo.strTmxName = GetStringFromJson(ArrayJson,_TMX_NAME_,nStageID);
            TmxInfo.fStartPosX = GetFloatFromJson(ArrayJson,_TMX_START_POS_X_);
            TmxInfo.fStartPosY = GetFloatFromJson(ArrayJson,_TMX_START_POS_Y_);
            //map 类型
            Info[i] = TmxInfo;
            
        }
        
        return true;
    } while (false);
    log("Fun CNFJsonTranslater::GetTmxInfoFromJson Error!");
    return false;
}

//得到Door信息
//{"door_arr":[{"door_id":1,"door_x":10000,"door_y":400,"door_z":0},{"door_id":2,"door_x":10,"door_y":200,"door_z":0},{"door_id":3,"door_x":10,"door_y":600,"door_z":0}]}
bool CNFJsonTranslater::GetDoorInfoFromJson( const char * szJson,CNFDoorJsonInfoVec &Info,int nStageID )
{
    do
    {
        //创建Json
        rapidjson::Document json;
        
        //复制字符串数据
        json.Parse<0>(szJson);
        
        //校验Json
        if (json.HasParseError())
        {
            CCLOG("Fun CNFJsonTranslater::GetDoorInfoFromJson GetParseError %s\n",json.GetParseError());
        }
        
        int nArrayCount = DICTOOL->getArrayCount_json(json,_DOOR_ARR_);
        for (int i = 0; i < nArrayCount; ++i)
        {
            const rapidjson::Value &ArrayJson = DICTOOL->getSubDictionary_json(json,_DOOR_ARR_, i);
            
            tagDoorJsonInfo DoorInfo;
            DoorInfo.nDoorID = GetIntFromJson(ArrayJson,_DOOR_ID_,nStageID);
            DoorInfo.fPosX = GetFloatFromJson(ArrayJson,_DOOR_X_,nStageID);
            DoorInfo.fPosY = GetFloatFromJson(ArrayJson,_DOOR_Y_,nStageID);
            DoorInfo.fPosZ = GetFloatFromJson(ArrayJson,_DOOR_Z_,nStageID);
            
            Info.push_back(DoorInfo);
        }
        
        return true;
    } while (false);
    log("Fun CNFJsonTranslater::GetDoorInfoFromJson Error!");
    return false;
}