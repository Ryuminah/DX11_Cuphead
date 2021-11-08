#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "Scene/Viewport.h"
#include "../Object/Mugman.h"
#include "../Object/DragonMap.h"
#include "../Object/StepCloud.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateMaterial();
	CreateAnimationSequence2D();
	CreateParticle();

	m_pScene->GetResource()->LoadSound("UI", false, "ButtonMouseOn",
		"TeemoSmile.mp3");
	m_pScene->GetResource()->LoadSound("UI", false, "ButtonClick",
		"TeemoStartClicck.mp3");

	// Create GameObject
	CDragonMap* pDragonMap = m_pScene->SpawnObject<CDragonMap>("DragonMap");
	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	CStepCloud* pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");


	return true;
}

void CMainScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateMaterial("PlayerChild");
	m_pScene->GetResource()->AddMaterialTexture("PlayerChild", "PlayerChild",
		TEXT("Teemo.jpg"));

	m_pScene->GetResource()->CreateMaterial("BG_Normal");
	m_pScene->GetResource()->AddMaterialTexture("BG_Normal", "BG_Normal",
		TEXT("BG_Normal.png"));
}

void CMainScene::CreateAnimationSequence2D()
{
	CreateMugmanAnim();
	CreateStepCloudAnim();
}

void CMainScene::CreateParticle()
{
}

void CMainScene::CreateMugmanAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_R",
		"Mugman_Idle_R", TEXT("Mugman/Mugman_Idle_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Idle_R",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_L",
		"Mugman_Idle_L", TEXT("Mugman/Mugman_Idle_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Idle_L",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_R",
		"Mugman_Run_Shoot_R", TEXT("Mugman/Mugman_Run_Shoot_R.png"));
	for (int i = 0; i < 16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_R",
			Vector2(i * 200, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_L",
		"Mugman_Run_Shoot_L", TEXT("Mugman/Mugman_Run_Shoot_L.png"));
	for (int i = 0; i < 16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_L",
			Vector2(i * 200, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_R",
		"Mugman_Shoot_R", TEXT("Mugman/Mugman_Shoot_R.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_R",
			Vector2(i * 200, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_L",
		"Mugman_Shoot_L", TEXT("Mugman/Mugman_Shoot_L.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_L",
			Vector2(i * 200, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_R",
		"Mugman_Jump_R", TEXT("Mugman/Mugman_Jump_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Jump_R",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_L",
		"Mugman_Jump_L", TEXT("Mugman/Mugman_Jump_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Jump_L",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_R",
		"Mugman_AimUp_R", TEXT("Mugman/Mugman_AimUp_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_R",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_L",
		"Mugman_AimUp_L", TEXT("Mugman/Mugman_AimUp_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_L",
			Vector2(i * 200, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_R",
		"Mugman_Dash_R", TEXT("Mugman/Mugman_Dash_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Dash_R",
			Vector2(i * 330, 0), Vector2((i + 1) * 330.f, 330.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_L",
		"Mugman_Dash_L", TEXT("Mugman/Mugman_Dash_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Dash_L",
			Vector2(i * 330, 0), Vector2((i + 1) * 330.f, 330.f));
	}
}

void CMainScene::CreateStepCloudAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down",
		"Cloud_Down", TEXT("Cloud_Down.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down",
			Vector2(i * 250, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down_Idle",
		"Cloud_Down_Idle", TEXT("Cloud_Down_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down_Idle",
			Vector2(i * 250, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Idle",
		"Cloud_Idle", TEXT("Cloud_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Idle",
			Vector2(i * 250, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Up");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Up",
		"Cloud_Up", TEXT("Cloud_Up.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Up",
			Vector2(i * 250, 0), Vector2((i + 1) * 250.f, 250.f));
	}
}
