#include "pch.h"
#include "Fruits.h"
#include "ResMgr.h"
#include "EnumToStringer.h"
#include "Texture.h"
#include "Collider.h"


Fruits::Fruits(bool rottenMode, FRUITS type, float scale)
{
	Init(rottenMode, type, scale);
}

Fruits::~Fruits()
{
}

void Fruits::Init(bool rottenMode, FRUITS type, float scale)
{
	rotten = rottenMode;
	fruitMode = type;
	wchar_t fileNameBuffer[50];
	wsprintf(fileNameBuffer, L"Texture\\%s.bmp", EnumToStringer::GetInst()->GetFruitName(type).c_str());

	myTexture = ResMgr::GetInst()->TexLoad(EnumToStringer::GetInst()->GetFruitName(type), fileNameBuffer);

	SetScale(Vec2( myTexture->GetWidth() * scale, myTexture->GetHeight() * scale ));
	CreateCollider(COLLIDER_TYPE::CIRCLE);
	GetCollider()->SetScale(Vec2(GetScale().x, GetScale().x));
}

void Fruits::Update()
{
	Object::Update();
	if (GetPos().x + GetScale().x >= WINDOW_WIDTH) {
		Vec2 curVel = GetVelocity();
		curVel.x = -curVel.x;
		SetVelocity(curVel);
	}
	if (GetPos().y + GetScale().y >= WINDOW_HEIGHT) {
		Vec2 curVel = GetVelocity();
		curVel.y = -curVel.y;
		SetVelocity(curVel);
	}
}

void Fruits::Render(HDC _dc)
{
	TRANSPARENTBLT_INPOS(_dc, myTexture->GetDC(), myTexture);
}

void Fruits::EnterCollision(Collider* _pOther, CollisionInfo* info)
{
	if (_pOther == nullptr)
		SetDead();
	else {
		//Vec2 collidePoint = 
	}
	Object::EnterCollision(_pOther, info);
}

void Fruits::ExitCollision(Collider* _pOther)
{
	Object::ExitCollision(_pOther);
}
