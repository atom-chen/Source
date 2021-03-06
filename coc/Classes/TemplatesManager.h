#pragma once

struct NpcTemplate 
{
    string moveToNorthEastAnimationPList;
    string moveToEastAnimationPList;
    string moveToSouthEastAnimationPList;
    string moveToSouthWestAnimationPList;
    string moveToWestAnimationPList;
    string moveToNorthWestAnimationPList;

    string dieAnimationPList;

    string standAndFaceToNorthEastAnimationPList;
    string standAndFaceToEastAnimationPList;
    string standAndFaceToSouthEastAnimationPList;
    string standAndFaceToSouthWestAnimationPList;
    string standAndFaceToWestAnimationPList;
    string standAndFaceToNorthWestAnimationPList;

    string attackToNorthEastAnimationPList;
    string attackToEastAnimationPList;
    string attackToSouthEastAnimationPList;
    string attackToSouthWestAnimationPList;
    string attackToWestAnimationPList;
    string attackToNorthWestAnimationPList;

    int maxHp = 0;
    int attackPower = 0;
    int maxAttackRadius = 0;
    int maxAlertRadius = 0;
    int perSecondAttackCount = 0;
    float perSecondMoveSpeedByPixel = 0.0f;
    BulletType bulletType = BulletType::Invalid;
    DamageType damageType = DamageType::Invalid;
    float aoeDamageRadius = 0.0f; // 非AOE伤害的Npc无视这个参数

    float shadowYPosition = 0.0f;
    float hpBarYPosition = 0.0f;

    float moveAnimateDelayPerUnit = 0.0f;
    float standAnimateDelayPerUnit = 0.0f;
    float dieAnimateDelayPerUnit = 0.0f;
    float reinforceRadius = 0.0f;

    string blueSelectedTipsTextureName;
    string redSelectedTipsTextureName;

    int technologyPointForEnemy = 0;

    bool isAir = false;
    bool canAirAttack = false;
};

struct BulletTemplate
{
    string bulletFileName;
    string specialEffectTemplateName;
};

struct BuildingTemplate
{
    string prepareToBuildStatusTextureName;
    string beingBuiltStatusTextureName;
    string workingStatusTextureName;
    string destroyStatusTextureName;
    string shadowTextureName;
    string destroySpecialEffectTemplateName;
    float shadowYPositionInBeingBuiltStatus = 0.0f;
    float shadowYPositionInWorkingStatus = 0.0f;
    float shadowYPositionInDestroyStatus = 0.0f;
    float buildingTimeBySecond = 0.0f;
    float extraEnemyAttackRadius = 0.0f;
    int maxHP = 0;
    float centerBottomGridYPosition = 0.0f;
    int bottomGridColumnCount = 0;
    int bottomGridRowCount = 0;
    string defenceNpcName;
    float defenceNpcYPosition = 0.0f;
    float attackRange = 0.0f;
    float attackPower = 0.0f;

    string blueSelectedTipsTextureName;
    string redSelectedTipsTextureName;

    int technologyPointForEnemy = 0;

    bool canDestroy = true;
};

struct SpecialEffectTemplate
{
    string animationPListName;
    float perUnitIntervalBySecond = 0.0f;
};

typedef map<string, NpcTemplate*> NpcTemplatesMap;

class TemplateManager
{
public:
    ~TemplateManager();

    static TemplateManager* getInstance();
    const NpcTemplate* getNpcTemplateBy(const string& jobName);
    const BulletTemplate* getBulletTemplateBy(BulletType bulletType);
    const BuildingTemplate* getBuildingTemplateBy(const string& buildingTemplateName);
    const SpecialEffectTemplate* getSpecialEffectTemplateBy(const string& templateName);

    const NpcTemplatesMap& getNpcTemplatesMap();
private:
    bool init();
    bool initNpcTemplates();
    bool initBulletTemplates();
    bool initBuildingTemplates();
    bool initSpecialEffectTemplates();

    NpcTemplatesMap _npcTemplatesMap;
    map<BulletType, BulletTemplate*> _bulletTemplatesMap;
    map<string, BuildingTemplate*> _buildingTemplatesMap;
    map<string, SpecialEffectTemplate*> _specialEffectTemplatesMap;

    TemplateManager(){}
    TemplateManager(const TemplateManager&);
    TemplateManager& operator = (const TemplateManager&);
};