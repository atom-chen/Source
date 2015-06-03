#include "Base.h"
#include "Utils.h"
#include "base/ccMacros.h"

static map<string, Animation*> s_animationMap;

float GameUtils::computeRotatedDegree(const Vec2& beginPosition, const Vec2& endPosition)
{
    float rotation = 0.0f;

    auto moveVector = endPosition - beginPosition;
    if (moveVector.x > -FLT_EPSILON && moveVector.x < FLT_EPSILON)
    {
        if (moveVector.y >= 0.0f)
        {
            rotation = 0.0f;
        }
        else
        {
            rotation = 180.0f;
        }

        return rotation;
    }
    else if (moveVector.y > -FLT_EPSILON && moveVector.y < FLT_EPSILON)
    {
        if (moveVector.x >= 0.0f)
        {
            rotation = 90.0f;
        }
        else
        {
            rotation = 270.0f;
        }

        return rotation;
    }

    float tanTheta = moveVector.x / moveVector.y;
    if (tanTheta > 0.0f)
    {
        if (moveVector.y > 0.0f)
        {
            rotation = atan(tanTheta) * 180.0f / M_PI;
        }
        else
        {
            rotation = atan(tanTheta) * 180.0f / M_PI + 180.0f;
        }
    }
    else
    {
        if (moveVector.x > 0.0f)
        {
            rotation = atan(tanTheta) * 180.0f / M_PI + 180.0f;
        }
        else
        {
            rotation = atan(tanTheta) * 180.0f / M_PI + 360.0f;
        }
    }

    return rotation;
}


float GameUtils::computeDistanceBetween(const Vec2& beginPosition, const Vec2& endPosition)
{
    float distance = sqrt((endPosition.x - beginPosition.x) * (endPosition.x - beginPosition.x) +
        (endPosition.y - beginPosition.y) * (endPosition.y - beginPosition.y));

    return distance;
}

bool GameUtils::isFloatEqual(float left, float right)
{
    bool result = false;

    float difference = left - right;
    if (difference > -FLT_EPSILON && difference < FLT_EPSILON)
    {
        result = true;
    }

    return result;
}

bool GameUtils::isVec2Equal(const Vec2& left, const Vec2& right)
{
    bool result = false;

    if (GameUtils::isFloatEqual(left.x, right.x) && GameUtils::isFloatEqual(left.y, right.y))
    {
        result = true;
        return result;
    }

    return result;
}

Animation* parseAnimationValueMap(ValueMap& plistDataMap)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    auto animation = Animation::create();

    auto framesIter = plistDataMap.find("frames");
    CCASSERT(framesIter != plistDataMap.end(), "plist file has not frames key");

    auto& framesMap = plistDataMap["frames"].asValueMap();
    vector<string> frameKeysList;
    for (auto& iter : framesMap)
    {
        frameKeysList.push_back(iter.first);
    }

    std::sort(frameKeysList.begin(), frameKeysList.end());

    for (auto& key : frameKeysList)
    {
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName(key);
        if (spriteFrame)
        {
            animation->addSpriteFrame(spriteFrame);
        }
    }

    return animation;
}

Animation* GameUtils::createAnimationWithPList(const string& plistFileName)
{
    Animation* animation = nullptr;

    auto fileUtils = FileUtils::getInstance();
    CCASSERT(fileUtils->isFileExist(plistFileName), StringUtils::format("%s is invalid", plistFileName.c_str()).c_str());

    auto animationIter = s_animationMap.find(plistFileName);
    if (animationIter == s_animationMap.end())
    {
        auto spriteFrameCache = SpriteFrameCache::getInstance();
        spriteFrameCache->addSpriteFramesWithFile(plistFileName);

        ValueMap plistDataMap = fileUtils->getValueMapFromFile(plistFileName);

        animation = parseAnimationValueMap(plistDataMap);
        s_animationMap[plistFileName] = animation;
        animation->retain();
    }
    else
    {
        animation = animationIter->second->clone();
    }
    
    return animation;
}