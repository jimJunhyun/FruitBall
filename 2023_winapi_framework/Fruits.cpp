#include "pch.h"
#include "Fruits.h"
#include "ResMgr.h"
#include "EnumToStringer.h"
#include "Texture.h"
#include "Collider.h"


Fruits::Fruits( FRUITS type, float scale)
{
	Init(type, scale);
}

Fruits::~Fruits()
{
}

void Fruits::Init( FRUITS type, float scale)
{
	fruitMode = type;
	wchar_t fileNameBuffer[50];
	wsprintf(fileNameBuffer, L"Texture\\%s.bmp", EnumToStringer::GetInst()->GetFruitName(type).c_str());

	myTexture = ResMgr::GetInst()->TexLoad(EnumToStringer::GetInst()->GetFruitName(type), fileNameBuffer);

	SetScale(Vec2( myTexture->GetWidth() * scale, myTexture->GetHeight() * scale ));
	CreateCollider(COLLIDER_TYPE::CIRCLE);
	GetCollider()->SetScale(Vec2(GetScale().x, GetScale().x) * 0.5f);
	GetCollider()->SetOffSetPos(Vec2(GetScale().x, GetScale().y) * 0.5f);
}

void Fruits::Update()
{
	Object::Update();
	if (GetPos().x + GetScale().x >= WINDOW_WIDTH) {
		Vec2 vel = GetVelocity();
		if (vel.x > 0) {
			AddForce(Vec2(-2, 0) * abs(vel.x));
		}
	}
	else if (GetPos().x <= 0) {
		Vec2 vel = GetVelocity();
		if (vel.x < 0) {
			AddForce(Vec2(2, 0) * abs(vel.x));
		}
	}
	if (GetPos().y + GetScale().y >= WINDOW_HEIGHT) {
		Vec2 vel = GetVelocity();
		if (vel.y > 0) {
			AddForce(Vec2(0, -2) * abs(vel.y));
		}
	}
	else if (GetPos().y <= 0) {
		Vec2 vel = GetVelocity();
		if (vel.y < 0) {
			AddForce(Vec2(0, 2) * abs(vel.y));
		}
	}
}

void Fruits::Render(HDC _dc)
{
	TRANSPARENTBLT_INPOS(_dc, myTexture->GetDC(), myTexture);
	Component_Render(_dc);
}

void Fruits::EnterCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info)
{
	if (_pOther == nullptr)
		SetDead();
	Object::EnterCollision(_pOther, info);
}

void Fruits::ExitCollision(Collider* _pOther)
{
	Object::ExitCollision(_pOther);
}
