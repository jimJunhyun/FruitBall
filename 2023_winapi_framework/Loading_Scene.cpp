#include "pch.h"
#include "Loading_Scene.h"
#include "Core.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Button.h"
#include "TimeMgr.h"
#include "Object.h"


void Loading_Scene::Init()
{
	m_tFruitballLogo = ResMgr::GetInst()->TexLoad(L"Logo", L"Texture\\FruitballLogo.bmp");

	m_vLogo = Vec2(Core::GetInst()->GetResolution().x / 2 - m_tFruitballLogo->GetWidth() / 2, Core::GetInst()->GetResolution().y / 2 - m_tFruitballLogo->GetHeight() / 2 - 100);
}

void Loading_Scene::Update()
{
	if (m_vLogo.y >= Core::GetInst()->GetResolution().y - 1500)
		m_vLogo.y += fDT * 1000.f * -1;
	else
		SceneMgr::GetInst()->LoadScene(L"GameScene");

}

void Loading_Scene::Render(HDC _dc)
{

	TransparentBlt(_dc, m_vLogo.x, m_vLogo.y, m_tFruitballLogo->GetWidth(), m_tFruitballLogo->GetHeight(), m_tFruitballLogo->GetDC(), 0, 0, m_tFruitballLogo->GetWidth(), m_tFruitballLogo->GetHeight(), RGB(255, 0, 255));
}

void Loading_Scene::Release()
{
}
