#pragma once
#include "Scene.h"
class Game_Scene :
    public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

private:
    float accSec = 0;

    vector<Object*> objs;
public:
    float spawnSec = 1.0f;
};

