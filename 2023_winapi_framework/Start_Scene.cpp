#include "pch.h"
#include "Start_Scene.h"
#include "Core.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Button.h"
void Start_Scene::Init()
{
	m_tFruitballLogo = ResMgr::GetInst()->TexLoad(L"Logo", L"Texture\\FruitballLogo.bmp");

	Button* Btn1 = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"LoadingScene");
		}
	, L"게임 시작");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 100 })));
	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	Button* Btn2 = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"ExplainScene");
		}, L"게임 설명");
	Btn2->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 150 })));
	Btn2->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn2, OBJECT_GROUP::UI);

	Button* Btn3 = new Button([]()
		{
			//SceneMgr::GetInst()->LoadScene(L"GameOverScene");
			SendMessage(Core::GetInst()->GetHwnd(), WM_CLOSE, 0, 0);
		}, L"게임 종료");
	Btn3->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 200 })));
	Btn3->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn3, OBJECT_GROUP::UI);
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->LoadSound(L"BgndMusic", L"Sound\\BgndMusic.mp3", true);
	ResMgr::GetInst()->Play(L"BgndMusic");
}

void Start_Scene::Update()
{
	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	m_vLogo = Vec2(Core::GetInst()->GetResolution().x / 2 - m_tFruitballLogo->GetWidth() / 2, Core::GetInst()->GetResolution().y / 2 - m_tFruitballLogo->GetHeight() / 2 - 100);
	TransparentBlt(_dc, m_vLogo.x, m_vLogo.y, m_tFruitballLogo->GetWidth(), m_tFruitballLogo->GetHeight(), m_tFruitballLogo->GetDC(), 0, 0, m_tFruitballLogo->GetWidth(), m_tFruitballLogo->GetHeight(), RGB(255, 0, 255));
}

void Start_Scene::Release()
{
	Scene::Release();
}
