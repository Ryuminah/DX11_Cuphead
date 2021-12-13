#include "LoadingThread.h"
#include "MainScene.h"
#include "TutorialScene.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CLoadingThread::CLoadingThread() : m_bIsMainScene(false), m_bIsTutorialScene(false)
{
}

CLoadingThread::~CLoadingThread()
{

}

void CLoadingThread::Run()
{
	CScene* Scene = CSceneManager::GetInst()->CreateScene();
	Scene->SetSceneMode<CMainScene>();

	/*if (m_bIsMainScene)
	{
	}

	if (m_bIsTutorialScene)
	{
		Scene->SetSceneMode<CTutorialScene>();
	}*/

	CSceneManager::GetInst()->SetNextScene(Scene);
}
