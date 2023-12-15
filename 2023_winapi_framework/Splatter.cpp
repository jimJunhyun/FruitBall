#include "pch.h"
#include "Splatter.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "ResMgr.h"

Splatter::Splatter(Scene* level) 
	: Object(level)
	, lifetime(1)
	, curScale(0)
	, shrinkStartTime(0.01f)
{
	myTex = ResMgr::GetInst()->TexLoad(L"Splat", L"Texture\\FruitSplat.bmp");
	initScale = Vec2(myTex->GetWidth(), myTex->GetHeight());
	SetScale(Vec2(initScale * curScale));

}

Splatter::~Splatter()
{
}

void Splatter::Update()
{
	if (lifetime == 1) {
		curScale = 0;
	}
	else if (lifetime == 0) {
		curScale = 0;
		SetDead();
	}
	else {
		if (lifetime < shrinkStartTime) {
			curScale = pow(2, 10 * (lifetime - shrinkStartTime));
		}
		else if (lifetime < 0.5f) {
			curScale = -16 * pow(lifetime, 5) + 1;
		}
		else {
			curScale = -16 * pow(lifetime - 1, 5);
		}
	}
	SetScale(initScale * curScale);
	lifetime -= fDT;
}

void Splatter::Render(HDC dc)
{
	TransparentBlt(dc, GetPos().x - GetScale().x / 2, GetPos().y - GetScale().y / 2, GetScale().x, GetScale().y, myTex->GetDC(), 0, 0, myTex->GetWidth(), myTex->GetHeight(), RGB(255, 0, 255));
	//TRANSPARENTBLT_INPOS(dc, myTex->GetDC(), myTex);
}
