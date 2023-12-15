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


	obj = new TextBox(L"���� �÷���", 80);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 - 130 })));
	obj->SetScale(Vec2(1000.f, 500.f));
	AddObject(obj, OBJECT_GROUP::UI);


	obj = new TextBox(L"ȭ�鿡 ��Ÿ���� ���ϵ��� ��ܿ��� �Ʒ������� �������ϴ�.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 - 50 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"���콺�� Ŭ���ϰ� �巡���Ͽ� ������ �ڸ��ϴ�.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 10 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"������ �߶󳻸� ������ ȹ���մϴ�.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 70 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new TextBox(L"�׷��� ���� ������ �ڸ��� ������ ����� �� �ֽ��ϴ�.", 20);
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 , Core::GetInst()->GetResolution().y / 2 + 130 })));
	obj->SetScale(Vec2(1000.f, 720.f));
	AddObject(obj, OBJECT_GROUP::UI);

	Button* Btn = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"StartScene");
		}
	, L"���ư���");
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
