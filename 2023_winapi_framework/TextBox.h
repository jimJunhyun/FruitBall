#pragma once
#include "Object.h"

class Scene;

class TextBox :
	public Object
{
public:
	TextBox(wstring _text, int _size, Scene* level = nullptr);
	~TextBox();

public:
	void Update()override;
	void Render(HDC _dc)override;
	void SetText(wstring str) { m_sText = str; }
	void DrawShape();

private:
	wstring m_sText;
	int m_iSize;
	HFONT hFont, OldFont;
	bool m_bIsDraw;
};
