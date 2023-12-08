#pragma once
#include "Object.h"
class TextBox :
	public Object
{
public:
	TextBox(wstring _text);
	~TextBox();

public:
	void Update()override;
	void Render(HDC _dc)override;
	void SetText(wstring str) { m_sText = str; }

private:
	wstring m_sText;
};
