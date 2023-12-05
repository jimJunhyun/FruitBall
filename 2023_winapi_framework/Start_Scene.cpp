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
void Start_Scene::Init()
{

}

void Start_Scene::Update()
{
	Scene::Update();
	if (KEY_DOWN(KEY_TYPE::LBUTTON))
	{
		SceneMgr::GetInst()->LoadScene(L"GameScene");
	}


}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	GetClientRect(Core::GetInst()->GetHwnd(), &rt);
	wstring wstr = L"FuritBall";
	TextOut(_dc, start_btn.right/2 , start_btn.bottom , wstr.c_str(), wstr.length());
	Rectangle(_dc, start_btn.left, start_btn.top, start_btn.right, start_btn.bottom);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
