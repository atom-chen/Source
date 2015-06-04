#pragma once

enum class BuildingStatus
{
    Invalid = 0,

    PrepareToBuild,
    BeingBuilt,
    Working,
    Destory,

    Total
};

class Npc;

class Building : public GameObject
{
public:
    static Building* create(ForceType forceType, const string& buildingTemplateName, const Vec2& position, int uniqueID);

    bool isReadyToRemove() override;

    void update(float delta) override;
    void updateStatus(BuildingStatus buildingStatus);
    BuildingStatus getBuildingStatus();

    bool canBuild();
    const vector<Vec2>& getBottomGridInMapPositionList();

    void setEnemyUniqueID(int uniqueID) override;
    int getEnemyUniqueID() override;
private:
    bool init(ForceType forceType, const string& buildingTemplateName, const Vec2& position, int uniqueID);

    void initBuildingStatusSprites(const string& buildingTemplateName);
    Sprite* createBuildingStatusSprite(const string& buildingTemplateName, BuildingStatus buildingStatus, int opacity = 255);

    void initBottomGridSprites(const string& buildingTemplateName);
    void initHPBar();
    void initBeingBuiltProgressBar();
    void initBattleData(const string& buildingTemplateName);
    void initSelectedTips(const string& buildingTemplateName);
    void initBottomGridInMapPositionList();

    Npc* createDefenceNpc(const string& buildingTemplateName);
    void removeDefenceNpc();
    Npc* _defenceNpc = nullptr;

    void clear();

    void onPrepareToRemove() override;
    void debugDraw() override;

    void followCursorInPrepareToBuildStatus();
    void ajustBuildingPosition(const Vec2& inMapPosition);
    bool isBottomGridCoverNpc(const Vec2& bottomGridInMapPosition);
    vector<Sprite*> getInObstacleTileNodeBottomGidSpriteList();
    void updateBottomGridTextureInPrepareToBuildStatus();
    void updateCoveredByBuildingTileNodesGID(int tileNodeGID);
    void delayUpdateAIForceBuildingToBeingBuiltStatus(const Vec2& inMapPosition);
    void onUpdateAIForceBuildingStatus(const Vec2& inMapPosition, BuildingStatus buildingStatus);

    void showBeingBuiltProgressBar();
    void hideBeingBuiltProgressBar();
    void onConstructionComplete();
    void updateBeingBuiltProgressBar(float delta);

    void addToRemoveQueue();

    map<BuildingStatus, Sprite*> _buildingStatusSpriteMap;
    vector<Sprite*> _bottomGridSpritesList;
    Vec2 _bottomGridsPlaneCenterPositionInLocalSpace; // 建筑物底部面片的中心位置

    BuildingStatus _buildingStatus;

    float _buildingTimeBySecond = 0.0f;
    float _passTimeBySecondInBeingBuiltStatus = 0.0f;
    ui::LoadingBar* _beingBuildProgressBar = nullptr;
    string _destroySpecialEffectTemplateName;
    string _buildingTemplateName;

    vector<Vec2> _bottomGridInMapPositionList;
};