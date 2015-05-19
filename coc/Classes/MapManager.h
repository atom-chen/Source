#pragma once

class GameObject;

enum class TileMapLayerType
{
    Invalid = 0,

    BackgroundLayer,
    GameObjcetLayer,

    Total
};

struct DebugInfo
{
    Vec2 cursorPoint;
    Point tileSubscript;
    std::string tileTextureName;
    std::string tileMapLayerName;
    int gid = 0;
};

struct TileNode
{
    int gid = 0;
    Vec2 leftTopPosition;

    int gotoEndNodeWeight = 0;
    int gotoStartNodeWeight = 0;
    int sumWeight = 0;

    int rowIndex = 0;
    int columnIndex = 0;

    bool isVisit = false;

    TileNode* parent = nullptr;
};

const float MAP_MOVE_SPEED = 20.0f;
const float MAP_BORDER_MARGIN = 50.0f;
const float MAP_MIN_SCALE = 0.3f;
const float MAP_MAX_SCALE = 1.0f;
const int LINEUP_MAX_ROW_COUNT = 5;
const int OBSTACLE_ID = 2;

class MapManager
{
public:
    ~MapManager();

    bool init(Node* parentNode, const std::string& titleMapFileName);

    void updateMapPosition();
    void updateMapScale(Event* event);

    void syncCursorPoint(const Vec2& cursorPoint);

    Size getTileSize();
    Point getTileSubscript(const Vec2& inMapPosition);
    DebugInfo getDebugInfo(TileMapLayerType tileMapLayerType);

    Vec2 convertCursorPositionToTileMapSpace();
    Vec2 convertToTileMapSpace(const Vec2& worldPosition);

    void addChildInGameObjectLayer(Node* gameObject, int zOrder = 1);

    TileNode* getTileNodeAt(int columnIndex, int rowIndex);

    vector<Vec2> getNpcMoveTargetListBy(int npcSelectedByPlayerCount);

    bool isInObstacleTile(const Vec2& inMapPosition);
private:
    int insertNpcMoveEndPositionInto(vector<Vec2>& npcMoveEndPositionList, int xSubscript, int minRowIndex, int maxRowIndex, int npcSelectedByPlayerCount, Vec2 deltaFromCursorToTile);

    void resolveMapShakeWhenMove();

    void initTileNodeTable();

    cocos2d::experimental::TMXTiledMap* _tileMap = nullptr;
    float _mapScale = 0.5f;

    RECT _clientRect;
    Vec2 _cursorPoint;

    vector<vector<TileNode*>> _tileNodeTable;
};