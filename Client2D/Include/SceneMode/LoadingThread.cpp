#include "LoadingThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CLoadingThread::CLoadingThread()
{
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	// 현재 로딩씬이 존재하지 않음....
	CScene* Scene = CSceneManager::GetInst()->CreateScene();

	Scene->SetSceneMode<CMainScene>();

	CSceneManager::GetInst()->SetNextScene(Scene);
}
