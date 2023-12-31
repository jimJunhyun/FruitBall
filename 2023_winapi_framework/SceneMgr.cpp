#include "pch.h"
#include "SceneMgr.h"
#include "Start_Scene.h"
#include "Game_Scene.h"
#include "Gameover_Scene.h"
#include "Explain_Scene.h"
#include "Loading_Scene.h"
void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	// �� ���
	RegisterScene(L"StartScene", std::make_shared<Start_Scene>());
	RegisterScene(L"GameScene", std::make_shared<Game_Scene>());
	RegisterScene(L"GameOverScene", std::make_shared<Gameover_Scene>());
	RegisterScene(L"ExplainScene", std::make_shared<Explain_Scene>());
	RegisterScene(L"LoadingScene", std::make_shared<Loading_Scene>());

	// ù �� ����
	LoadScene(L"StartScene");
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadScene(const wstring& _scenename)
{
	// ���� ������
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_scenename);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::RegisterScene(const wstring& _scenename, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), { _scenename, _scene });
}
