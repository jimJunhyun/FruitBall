#include "pch.h"
#include "Game_Scene.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "Fruits.h"
#include "KeyMgr.h"
#include "ForceManager.h"
#include "SelectGDI.h"

void Game_Scene::Init()
{
	curDrag = nullptr;
	srand((unsigned int)time(NULL));
	
}

void Game_Scene::Update()
{
	Scene::Update();
	if (!curDrag) {
		accSec += fDT;
		if (accSec > spawnSec) {
			accSec = 0;
			Fruits* fruit = new Fruits(rand() % 2, static_cast<FRUITS>(rand() % (int)FRUITS::MAX), 0.1f);
			fruit->SetPos({ rand() % 1280, rand() % 720 });
			fruit->SetVelocity({ 100, 100 });

			AddObject(fruit, OBJECT_GROUP::FRUIT);
		}
	}
	

	if (KEY_DOWN(KEY_TYPE::LBUTTON)) {
		curDrag = new Drag;
		curDrag->startPos = GETMOUSEPOSITION();
		curDrag->prevCalcPos = curDrag->startPos;
		curDrag->moveDist = 0;
	}
	if (KEY_PRESS(KEY_TYPE::LBUTTON)) {
		if (curDrag) {
			curDrag->moveDist += (Vec2(GETMOUSEPOSITION()) - curDrag->prevCalcPos).Length();
			curDrag->prevCalcPos = GETMOUSEPOSITION();

			if (curDrag->moveDist > DRAGTHRESHOLD) {
				vector<Object*> fruits = GetGroupObject(OBJECT_GROUP::FRUIT);
				for (UINT i = 0; i < fruits.size(); i++)
				{
					if (PtInRect(&(fruits[i]->GetCollider()->GetRect()), GETMOUSEPOSITION())) {

						curDrag->isPassed = true;
						fruits[i]->EnterCollision(nullptr);
					}
				}
			}
			

		}
		
	}
	if (KEY_UP(KEY_TYPE::LBUTTON)) {
		if (curDrag) {
			curDrag->endPos = GETMOUSEPOSITION();
			curDrag = nullptr;
		}
	}
}

void Game_Scene::Render(HDC _dc)
{
	if (curDrag) {
		SelectGDI selecter(_dc, BRUSH_TYPE::GRAY);
		Rectangle(_dc, -1, -1, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1);
	}
	

	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
