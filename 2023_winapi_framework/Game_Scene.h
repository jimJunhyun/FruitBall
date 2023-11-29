#pragma once
#include "Scene.h"

struct Drag {
    Vec2 startPos;
    bool isPassed;
    //std::set<Object*> passedObjs;
    float moveDist;
    Vec2 endPos;

    Vec2 prevCalcPos;
};

class Game_Scene :
    public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

private:
    float accSec = 0;
    Drag* curDrag;
    RECT spawnRange;
public:
    float spawnSec = 0.5f;
    int maxCnt = 17;
    int curCnt = 0;
};

