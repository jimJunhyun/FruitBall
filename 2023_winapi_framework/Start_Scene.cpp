#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Button.h"
void Start_Scene::Init()
{
	Btn1 = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"GameScene");
		}
	, L"게임 시작");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	Btn2 = new Button([]()
		{

		}, L"게임 설명");
	Btn2->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 60 })));
	Btn2->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn2, OBJECT_GROUP::UI);

	Btn3 = new Button([]() { SendMessage(Core::GetInst()->GetHwnd(), WM_CLOSE, 0, 0); }, L"게임 종료");
	Btn3->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 120 })));
	Btn3->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn3, OBJECT_GROUP::UI);
}

void Start_Scene::Update()
{
	Scene::Update();
	/*if (KEY_DOWN(KEY_TYPE::LBUTTON)) {
		SceneMgr::GetInst()->LoadScene(L"GameScene");
	}*/
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
