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
#include "Core.h"

void Game_Scene::Init()
{
	life = maxLife;
	score = 0;
	curDrag = nullptr;
	srand((unsigned int)time(NULL));
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::FRUIT, OBJECT_GROUP::FRUIT);
}

void Game_Scene::Update()
{
	Scene::Update();
	if (!curDrag && curCnt < maxCnt) {
		accSec += fDT;
		if (accSec > spawnSec) {
			accSec = 0;
			Fruits* fruit = new Fruits( static_cast<FRUITS>(rand() % (int)FRUITS::MAX), 0.1f, this);
			fruit->SetPos({ rand() % 1280, rand() % 720 });
			fruit->SetVelocity({(1 - (rand() % 3)) * 400 + 200, (1 - (rand() % 3)) * 400 + 200});

			AddObject(fruit, OBJECT_GROUP::FRUIT);
			++curCnt;
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
			accLineT += fDT;

			curDrag->moveDist += (Vec2(GETMOUSEPOSITION()) - curDrag->prevCalcPos).Length();
			curDrag->prevCalcPos = GETMOUSEPOSITION();

			if (accLineT >= lineThreshold) {
				curDrag->linePoses.push_front(GETMOUSEPOSITION());
				lastLinePoint = curDrag->moveDist;
				accLineT = 0;
			}
			if (curDrag->linePoses.size() > maxLineCount) {
				curDrag->linePoses.pop_back();
			}

			if (curDrag->moveDist > DRAGTHRESHOLD) {
				vector<Object*> fruits = GetGroupObject(OBJECT_GROUP::FRUIT);
				
				for (UINT i = 0; i < fruits.size(); i++)
				{
					Vec2 pos = fruits[i]->GetCollider()->GetFinalPos();
					Vec2 mPos = GETMOUSEPOSITION();
					float dist = (pos - mPos).Length();
					Vec2 colScale = fruits[i]->GetCollider()->GetScale();
					if (colScale.x >= dist) {

						curDrag->isPassed = true;
						fruits[i]->EnterCollision(nullptr, nullptr);

						if (static_cast<Fruits*>(fruits[i])->GetType() == FRUITS::ROTTENFRUIT) {
							score -= 100;
							life -= 1;
						}
						else {
							curDrag->combo += 1;
							Vec2 v = fruits[i]->GetVelocity();
							curDrag->predScore += v.Length() * 2;
						}
						
						
					}
				}
			}
			

		}
		
	}
	if (KEY_UP(KEY_TYPE::LBUTTON)) {
		if (curDrag) {
			curDrag->endPos = GETMOUSEPOSITION();
			
			score += max((curDrag->combo * 2) * curDrag->predScore / (curDrag->moveDist * 0.05f), 0);

			lastLinePoint = 0;
			curDrag = nullptr;
		}
	}
}

void Game_Scene::Render(HDC _dc)
{
	if (curDrag) {
		HBRUSH b = (HBRUSH)GetStockObject(GRAY_BRUSH);
		HBRUSH prevBrush = (HBRUSH)SelectObject(_dc, b);
		RECT_RENDER(-1, -1, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, _dc);
		SelectObject(_dc, prevBrush);
		DeleteObject(b);

		HPEN p = CreatePen(PS_DASH, maxLineCount, RGB(255, 255, 255));
		HPEN prevPen = (HPEN)SelectObject(_dc, p);
		if (curDrag->linePoses.size() > 0) {
			MoveToEx(_dc, curDrag->linePoses.front().x, curDrag->linePoses.front().y, nullptr);
			for (int i = 0; i < curDrag->linePoses.size(); ++i)
			{
				HPEN p = CreatePen(PS_DASH, maxLineCount-i, RGB(255, 255, 255));
				SelectObject(_dc, p);
				LineTo(_dc, curDrag->linePoses[i].x, curDrag->linePoses[i].y);
				DeleteObject(p);
			}
		}
		DeleteObject(p);
		SelectObject(_dc, prevPen);
	}
	wchar_t buffer[50];
	wsprintf(buffer, L"Score : %d", score);
	TextOut(_dc, 20, 20, buffer, wcslen(buffer));
	
	for (int i = 0; i < maxLife; i++)
	{
		if (i < life) {

		}
		else {

		}
	}

	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
