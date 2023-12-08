#include "pch.h"
#include "TextBox.h"

TextBox::TextBox(wstring _text)
{
	m_sText = _text;
}

TextBox::~TextBox()
{
}

void TextBox::Update()
{
}

void TextBox::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };
	//RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	HFONT hFont, OldFont;
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
	OldFont = (HFONT)SelectObject(_dc, hFont);
	DrawText(_dc, m_sText.c_str(), -1, &rt
		, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(_dc, OldFont);
}
