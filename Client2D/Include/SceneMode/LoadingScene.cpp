#include "LoadingScene.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "LoadingThread.h"
#include "ThreadManager.h"
#include "../Object/BackGround/FG_Loading.h"

CLoadingScene::CLoadingScene()
{
}

CLoadingScene::~CLoadingScene()
{
}

bool CLoadingScene::Init()
{
	CreateLoadingAnim();

	// 로딩용 스레드를 생성한다.
	m_Thread = CThreadManager::GetInst()->CreateThread<CLoadingThread>("LoadingThread");
	FG_Loading* pLoading = m_pScene->SpawnObject<FG_Loading>("FG_Loading");

	m_Thread->SetLoop(false);
	m_Thread->Start();

	return true;
}

void CLoadingScene::CreateLoadingAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Loading");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Loading",
		"Loading", TEXT("BackGround/Loading.png"));
	for (int i = 0; i < 16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Loading",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}
}
