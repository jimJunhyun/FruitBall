#include "pch.h"
#include "Gameover_Scene.h"
#include "SceneMgr.h"
#include "Core.h"
#include "Button.h"
#include "Fruits.h"
#include "TimeMgr.h"

void Gameover_Scene::Init()
{
	countDown = 10;

	/*for (int i = 0; i < 10; i++)
	{
		Fruits* fruit = new Fruits(rand() % 2, static_cast<FRUITS>(rand() % (int)FRUITS::MAX), 0.1f);
		fruit->SetPos({ rand() % 1280, rand() % 720 });

		AddObject(fruit, OBJECT_GROUP::UI);
	}*/

	Button* Btn1 = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"StartScene");
		}
	, L"돌아가기");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 200 })));
	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	TextBox* TB1 = new TextBox(L"GameOver", 200);
	TB1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	TB1->SetScale(Vec2(1280.f, 720.f));
	AddObject(TB1, OBJECT_GROUP::UI);



	TB2 = new TextBox(text + L"초후 돌아가기", 30);
	TB2->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 + 300, Core::GetInst()->GetResolution().y / 2 + 200 })));
	TB2->SetScale(Vec2(1280.f, 720.f));
	AddObject(TB2, OBJECT_GROUP::UI);
}

void Gameover_Scene::Update()
{

	time += fDT;

	if (time >= 1.f)
	{
		--countDown;
		time = 0;
	}

	if (countDown == 0)
		SceneMgr::GetInst()->LoadScene(L"StartScene");
	else
	{
		text = std::to_wstring(countDown);
		TB2->SetText(text + L"초후 돌아가기");
		Scene::Update();
	}
}

void Gameover_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	SetBkMode(_dc, 1);
}

void Gameover_Scene::Release()
{
	Scene::Release();
}
