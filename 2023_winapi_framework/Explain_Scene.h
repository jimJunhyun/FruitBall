#pragma once
#include "Scene.h"

class Explain_Scene :
	public Scene
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
	virtual void Release() override;

private:
	HFONT defaultFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("MS Shell Dlg"));
};

