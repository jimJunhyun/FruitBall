#pragma once
#include "Scene.h"
#include "Button.h"
class Start_Scene :
	public Scene
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;

private:
	Button* Btn1;
	Button* Btn2;
	Button* Btn3;
};

