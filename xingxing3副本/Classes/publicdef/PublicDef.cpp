//
//  PublicDef.cpp
//  NCF
//
//  Created by 瑛峰 on 14/10/30.
//
//

#include "PublicDef.h"


std::string GetStaticDataName()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return _TR_STATIC_DATABASE_FILE_NAME_;
#else
//    std::string strResult = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string strResult = CCFileUtils::getInstance()->getWritablePath();
    strResult+= _TR_STATIC_DATABASE_FILE_NAME_;
    return strResult;
#endif
}