#include "pch.h"
#include "Explain_Scene.h"
#include "Core.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Button.h"
#include "TextBox.h"

void Explain_Scene::Init()
{
	TextBox* obj = new TextBox(L"", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	obj->SetScale(Vec2(1000.f, 500.f));
	obj->DrawShape();
	AddObject(obj, OBJECT_GROUP::UI);


	obj = new TextBox(L"게임 플레이", 80);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 - 130 })));
	obj->SetScale(Vec2(1000.f, 500.f));
	AddObject(obj, OBJECT_GROUP::UI);


	obj = new TextBox(L"화면에 나타나는 과일들이 상단에서 아래쪽으로 떨어집니다.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 - 50 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"마우스를 클릭하고 드래그하여 과일을 자릅니다.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 10 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"과일을 잘라내면 점수를 획득합니다.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 70 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"그러나 썩은 과일을 자르면 게임이 종료될 수 있습니다.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 130 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	Button* Btn = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"StartScene");
		}
	, L"돌아가기");
	Btn->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 200 })));
	Btn->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn, OBJECT_GROUP::UI);
}

void Explain_Scene::Update()
{
	Scene::Update();
}

void Explain_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	SetBkMode(_dc, 0);
}

void Explain_Scene::Release()
{
	Scene::Release();
}
