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
	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

void Fruits::Update()
{
	Object::Update();
}

void Fruits::Render(HDC _dc)
{
	HDC rotatedImgDC = CreateCompatibleDC(_dc);
	POINT* points = new POINT[3]; //ÁÂ»ó ¿ì»ó ÁÂÇÏ
	points[0] = { (long)GetPos().x, (long)GetPos().y}; //######################################
	points[1] = { (long)(GetPos().x + GetScale().x + (sin(angle))), (long)GetPos().y};
	points[1] = { (long)(GetPos().x + (sin(angle) * GetScale().x)), (long)GetPos().y};
	//PlgBlt(rotatedImgDC, )
	//TransparentBlt(_dc, )
}

void Fruits::EnterCollision(Collider* _pOther)
{
	Object::EnterCollision(_pOther);
}

void Fruits::ExitCollision(Collider* _pOther)
{
	Object::ExitCollision(_pOther);
}

