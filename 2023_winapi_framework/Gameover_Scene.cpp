#include "pch.h"
#include "Gameover_Scene.h"
#include "SceneMgr.h"
#include "Core.h"
#include "Button.h"
#include "TextBox.h"

void Gameover_Scene::Init()
{
	Button* Btn1 = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"StartScene");
		}
	, L"돌아가기");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 200 })));
	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	TextBox* TB1 = new TextBox(L"hi");
	TB1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	TB1->SetScale(Vec2(100.f, 30.f));
	AddObject(TB1, OBJECT_GROUP::UI);
}

void Gameover_Scene::Update()
{
	Scene::Update();
}

void Gameover_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Gameover_Scene::Release()
{
	Scene::Release();
}
