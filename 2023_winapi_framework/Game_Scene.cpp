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
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"

void Game_Scene::Init()
{
	life = maxLife;
	score = 0;
	curDrag = nullptr;
	srand((unsigned int)time(NULL));
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::FRUIT, OBJECT_GROUP::FRUIT);
	heartTex = ResMgr::GetInst()->TexLoad(L"Heart", L"Texture\\HeartBitmap.bmp");
	emptyHeartTex = ResMgr::GetInst()->TexLoad(L"EmptyHeart", L"Texture\\HeartBitmapEmpty.bmp");
	heartScale = 0.2f;
	heartSize = Vec2( heartTex->GetWidth(), heartTex->GetHeight()) * heartScale;
	heartGap = 35;
	heartUIStart = { (float)(WINDOW_WIDTH) - ((heartSize.x + heartGap) * maxLife), 0.0f };
	fadeSec = 1.0f;

	focusModeTex = ResMgr::GetInst()->TexLoad(L"FocusMode", L"Texture\\FocusMode.bmp");
	backgroundTex = ResMgr::GetInst()->TexLoad(L"BackGround", L"Texture\\Poolball.bmp");
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
			fruit->SetVelocity({(1 - (rand() % 3)) * 1000 + 600, (1 - (rand() % 3)) * 1000 + 600});

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
		curFadeSec += fDT;
		curFadeSec = min(curFadeSec, fadeSec);
		SetTimescale(1 - (curFadeSec / fadeSec) * 0.75f);
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
						Fruits* fruit = static_cast<Fruits*>(fruits[i]);
						if (fruit) {
							fruit->Pause();
							if (curDrag->passedObjs.insert(fruit).second) {
								if (fruit->GetType() == FRUITS::ROTTENFRUIT) {
									score -= 100;
									DecreaseLife(1);
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
		}
	}
	if (KEY_UP(KEY_TYPE::LBUTTON)) {
		curFadeSec = 0;
		SetTimescale(1);
		if (curDrag) {
			curDrag->endPos = GETMOUSEPOSITION();
			
			score += max((curDrag->combo * 2) * curDrag->predScore / (curDrag->moveDist * 0.05f), 0);

			lastLinePoint = 0;

			slash = true;
			
			
		}
	}
	
}

void Game_Scene::Render(HDC _dc)
{
	StretchBlt(_dc, -1, -1, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, backgroundTex->GetDC(), 0, 0, backgroundTex->GetWidth(), backgroundTex->GetHeight(), SRCCOPY);

	if (curDrag) {
		HBRUSH b = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH prevBrush = (HBRUSH)SelectObject(_dc, b);
		RECT_RENDER(-1, -1, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, _dc);
		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 128 * (curFadeSec / fadeSec);
		AlphaBlend(_dc, 0, 0, WINDOW_WIDTH , WINDOW_HEIGHT , focusModeTex->GetDC(), 0, 0, focusModeTex->GetWidth(), focusModeTex->GetHeight(), bf);

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

	if (slash) {
		std::set<Object*>::iterator slashIter = curDrag->passedObjs.begin();
		accSlashSec += fDT;
		if (accSlashSec > slashGap) {
			slashCount += 1;
			if (slashCount > curDrag->passedObjs.size()) {
				
			}
		}
		MoveToEx(_dc, curDrag->startPos.x, curDrag->startPos.y	, nullptr);
		for (int i = 0; i < slashCount; i++)
		{
			LineTo(_dc, (*slashIter)->GetPos().x, (*slashIter)->GetPos().y);

		}
		//������ ��ġ�� �߱�
		//������� �����ؼ� �ε巴��
		/*else {
			LineTo(_dc, curDrag->endPos.x, curDrag->endPos.y);
			curDrag = nullptr;
			slash = false;
		}*/
	}

	wchar_t buffer[50];
	wsprintf(buffer, L"Score : %d", score);
	TextOut(_dc, 20, 20, buffer, wcslen(buffer));
	
	for (int i = 0; i < maxLife; i++)
	{
		Vec2 pos(heartUIStart + Vec2(i * (heartGap + heartSize.x), 0.0f));
		if (i < life) {
			TransparentBlt(_dc, pos.x, pos.y, heartSize.x, heartSize.y, heartTex->GetDC(), 0, 0,heartTex->GetWidth(),heartTex->GetHeight(), RGB(255, 0, 255));
		}
		else {
			TransparentBlt(_dc, pos.x, pos.y, heartSize.x, heartSize.y, emptyHeartTex->GetDC(), 0, 0, heartTex->GetWidth(), heartTex->GetHeight(), RGB(255, 0, 255));
		}
	}

	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}

void Game_Scene::DecreaseLife(int value)
{
	life -= value;
	if (life <= 0) {

		//SceneMgr::GetInst()->LoadScene(L"GameOverScene");
	}
}
