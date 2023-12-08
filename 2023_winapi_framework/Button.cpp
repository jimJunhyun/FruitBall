#include "pch.h"
#include "Button.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include <string>
#include "SceneMgr.h"

Button::Button(void(*_action)(), wstring _text)
	: m_pTex(nullptr)
{
	m_pAction = _action;
	m_sText = _text;
}

Button::~Button()
{
}

void Button::Update()
{
	if (KEY_UP(KEY_TYPE::LBUTTON))
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		POINT _pMousePoint;
		//GETMOUSEPOSITION();

		RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };

		if (PtInRect(&rt, GETMOUSEPOSITION()))
		{
			m_pAction();
		}
	}
}

void Button::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	DrawText(_dc, m_sText.c_str(), -1, &rt
		, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
