#include "pch.h"
#include "Fruits.h"
#include "ResMgr.h"
#include "EnumToStringer.h"
#include "Texture.h"



Fruits::Fruits(bool rottenMode, FRUITS type)
{
	Init(rottenMode, type);
}

Fruits::~Fruits()
{
}

void Fruits::Init(bool rottenMode, FRUITS type)
{
	rotten = rottenMode;
	fruitMode = type;
	wchar_t fileNameBuffer[50];
	wsprintf(fileNameBuffer, L"%d", fruitMode);
	
	myTexture = ResMgr::GetInst()->TexLoad(EnumToStringer::GetInst()->GetFruitName(type), fileNameBuffer);
}

void Fruits::Update()
{
	Object::Update();
}

void Fruits::Render(HDC _dc)
{
	TRANSPARENTBLT_INPOS(_dc, myTexture);
	
}

void Fruits::EnterCollision(Collider* _pOther)
{
}

void Fruits::ExitCollision(Collider* _pOther)
{
}

