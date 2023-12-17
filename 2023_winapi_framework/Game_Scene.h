#pragma once
#include "Scene.h"

class Texture;
struct Drag {
    Vec2 startPos;
    bool isPassed;
    std::set<Object*> passedObjs;
    float moveDist;
    Vec2 endPos;

    Vec2 prevCalcPos;

    int combo = 0;
    int predScore = 0;
    std::deque<Vec2> linePoses;
};

class Game_Scene :
    public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

private:
    float accSec;
    Drag* curDrag;
    int life;
    int maxLife;

    float lastLinePoint;

    int maxLineCount;
    float lineThreshold;
    float accLineT;

    bool slash;
    float slashGap;
    float accSlashSec;

    int slashCount;

    float fadeSec;
    float curFadeSec;

    Texture* heartTex;
    Texture* emptyHeartTex;
    Vec2 heartSize;
    float heartScale;
    float heartGap;
    Vec2 heartUIStart;

    Texture* focusModeTex;
    Texture* backgroundTex;
    int score;

    void AddScoreDrawCall(int val);
    vector<std::pair<int, float>> scoreDurPairs;

    float scoreDisplaySec;

    int maxCnt;
    float spawnSec;
public:
    
    int curCnt;

    
    

    const int& GetLife() const { return life; }
    void SetLife(int value) { life = value; }

    void DecreaseLife(int value);

    void AddScore(int value);
};

