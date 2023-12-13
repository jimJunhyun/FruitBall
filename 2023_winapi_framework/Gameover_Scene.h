#pragma once
#include "Scene.h"
#include "TextBox.h"

class Gameover_Scene :
	public Scene
{

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
	virtual void Release() override;

private:
	TextBox* TB2;
	int countDown = 10;
	float time = 0;
	wstring text = std::to_wstring(countDown);
};
