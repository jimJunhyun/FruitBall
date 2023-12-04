#pragma once
#include "Scene.h"

struct Drag {
    Vec2 startPos;
    bool isPassed;
    //std::set<Object*> passedObjs;
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
    float accSec = 0;
    Drag* curDrag;
    int life;
    int maxLife =3;

    float lastLinePoint = 45;

    int maxLineCount = 20;
    float lineThreshold = 0.01f;
    float accLineT;
public:
    float spawnSec = 0.5f;
    int maxCnt = 17;
    int curCnt = 0;

    int score;
    

    const int& GetLife() const { return life; }
    void SetLife(int value) { life = value; }

    void AddScore(int value) { score += value; }
};

