#include "pch.h"
#include "Game_Scene.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "Fruits.h"

void Game_Scene::Init()
{
	srand((unsigned int)time(NULL));
}

void Game_Scene::Update()
{
	Scene::Update();
	accSec += fDT;
	if (accSec > spawnSec) {
		accSec = 0;
		Fruits* fruit = new Fruits(rand() % 2, static_cast<FRUITS>(rand() % (int)FRUITS::MAX));
		fruit->SetPos({ rand() % 1280, rand() % 720});
		fruit->SetScale({ 100, 100 });
		fruit->CreateCollider();
		fruit->GetCollider()->SetScale({ 100, 100 });
		
		AddObject(fruit, OBJECT_GROUP::FRUIT);
	}
}

void Game_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
