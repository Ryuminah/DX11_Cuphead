#include "TutorialScene.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "LoadingThread.h"
#include "ThreadManager.h"
#include "../Object/Character/Mugman.h"
#include "../Object/BackGround/FG_Loading.h"
#include "../Object/BackGround/BG_KettleHouse.h"
#include "../Object/Collision/GroundCollider.h"
#include "Scene/SceneManager.h"
#include "LoadingScene.h"
#include "../Object/BackGround/BG_Tutorial.h"
#include "../Object/BackGround/BG_TutorialMap.h"
#include "../Object/BackGround/FG_Tutorial.h"




CTutorialScene::CTutorialScene()
{

}

CTutorialScene::~CTutorialScene()
{
}

bool CTutorialScene::Init()
{
	CreateTutorialAnim();
	CreateMugmanAnim();
	CreateWeaponAnim();
	CreateTutorialMap();

	// ´ó±Û¸µ ¿Ö »ý±â´© °íÃÆ´© &^^
	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	CMugman::bUseCamera = true;
	pMugman->SetRelativePos(300.f, 120.f, 0.f);


	return true;
}

void CTutorialScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->SetSceneMode<CLoadingScene>(false);
	}
}

void CTutorialScene::CreateTutorialMap()
{
	BG_Tutorial* pBG_Tutorial = m_pScene->SpawnObject<BG_Tutorial>("BG_Tutorial");
	FG_Tutorial* pFGWidget = m_pScene->GetViewport()->AddWindow<FG_Tutorial>("FG_Tutorial");
	BG_TutorialMap* pTutorialMap = m_pScene->SpawnObject<BG_TutorialMap>("BG_TutorialMap");

	CGroundCollider* pGroundCollider = m_pScene->SpawnObject<CGroundCollider>("Ground");
	pGroundCollider->SetIsTutorialScene(true);
}

void CTutorialScene::CreateTutorialAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Tutorial");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Tutorial",
		"BG_Tutorial", TEXT("BackGround/Tutorial/BG_Tutorial.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Tutorial",
		Vector2(0.f, 0.f), Vector2(1024.f, 576.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Tutorial");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Tutorial",
		"FG_Tutorial", TEXT("BackGround/Tutorial/FG_Tutorial.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Tutorial",
		Vector2(0.f, 0.f), Vector2(1024.f, 576.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Parry_Off");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Parry_Off",
		"Parry_Off", TEXT("BackGround/Tutorial/Parry_Off.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Parry_Off",
		Vector2(0.f, 0.f), Vector2(45.f, 48.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Parry_On");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Parry_On",
		"Parry_On", TEXT("BackGround/Tutorial/Parry_On.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Parry_On",
		Vector2(0.f, 0.f), Vector2(73.f, 71.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Pyramid_Body");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Pyramid_Body",
		"Pyramid_Body", TEXT("BackGround/Tutorial/Pyramid_Body.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Pyramid_Body",
		Vector2(0.f, 0.f), Vector2(282.f, 303.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Pyramid_Head");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Pyramid_Head",
		"Pyramid_Head", TEXT("BackGround/Tutorial/Pyramid_Head.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Pyramid_Head",
		Vector2(0.f, 0.f), Vector2(222.f, 243.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("TutorialMap");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("TutorialMap",
		"TutorialMap", TEXT("BackGround/Tutorial/TutorialMap.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("TutorialMap",
		Vector2(0.f, 0.f), Vector2(6730.f, 720.f));
}

void CTutorialScene::CreateMugmanAnim()
{
	// Idle
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_R",
		"Mugman_Idle_R", TEXT("Mugman/Mugman_Idle_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Idle_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_L",
		"Mugman_Idle_L", TEXT("Mugman/Mugman_Idle_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Idle_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	// Run
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Normal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Normal_R",
		"Mugman_Run_Normal_R", TEXT("Mugman/Mugman_Run_Normal_R.png"));
	for (int i = 0; i < 16.f; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Normal_R",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Normal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Normal_L",
		"Mugman_Run_Normal_L", TEXT("Mugman/Mugman_Run_Normal_L.png"));
	for (int i = 0; i < 16.f; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Normal_L",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	// Shoot_Run
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_R",
		"Mugman_Run_Shoot_R", TEXT("Mugman/Mugman_Run_Shoot_R.png"));
	for (int i = 0; i < 16.f; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_R",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_L",
		"Mugman_Run_Shoot_L", TEXT("Mugman/Mugman_Run_Shoot_L.png"));
	for (int i = 0; i < 16.f; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_L",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	// Shoot_Normal
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_R",
		"Mugman_Shoot_R", TEXT("Mugman/Mugman_Shoot_R.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_R",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_L",
		"Mugman_Shoot_L", TEXT("Mugman/Mugman_Shoot_L.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_L",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 200.f));
	}

	// Jump
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_R",
		"Mugman_Jump_R", TEXT("Mugman/Mugman_Jump_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Jump_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_L",
		"Mugman_Jump_L", TEXT("Mugman/Mugman_Jump_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Jump_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	// Aim
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Aim_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Aim_R",
		"Mugman_Aim_R", TEXT("Mugman/Mugman_Aim_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Aim_R",
			Vector2(i * 140.f, 0), Vector2((i + 1) * 140.f, 170.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Aim_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Aim_L",
		"Mugman_Aim_L", TEXT("Mugman/Mugman_Aim_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Aim_L",
			Vector2(i * 140.f, 0), Vector2((i + 1) * 140.f, 170.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_R",
		"Mugman_AimUp_R", TEXT("Mugman/Mugman_AimUp_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_L",
		"Mugman_AimUp_L", TEXT("Mugman/Mugman_AimUp_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_R",
		"Mugman_AimDown_R", TEXT("Mugman/Mugman_AimDown_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimDown_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_L",
		"Mugman_AimDown_L", TEXT("Mugman/Mugman_AimDown_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimDown_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_Digonal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_Digonal_R",
		"Mugman_AimUp_Digonal_R", TEXT("Mugman/Mugman_AimUp_Digonal_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_Digonal_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_Digonal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_Digonal_L",
		"Mugman_AimUp_Digonal_L", TEXT("Mugman/Mugman_AimUp_Digonal_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimUp_Digonal_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_Digonal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_Digonal_R",
		"Mugman_AimDown_Digonal_R", TEXT("Mugman/Mugman_AimDown_Digonal_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimDown_Digonal_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_Digonal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_Digonal_L",
		"Mugman_AimDown_Digonal_L", TEXT("Mugman/Mugman_AimDown_Digonal_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_AimDown_Digonal_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	// Dash
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_R",
		"Mugman_Dash_R", TEXT("Mugman/Mugman_Dash_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Dash_R",
			Vector2(i * 330.f, 0), Vector2((i + 1) * 330.f, 330.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_L",
		"Mugman_Dash_L", TEXT("Mugman/Mugman_Dash_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Dash_L",
			Vector2(i * 330.f, 0), Vector2((i + 1) * 330.f, 330.f));
	}

	// Parry
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Parry_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Parry_R",
		"Mugman_Parry_R", TEXT("Mugman/Mugman_Parry_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Parry_R",
			Vector2(i * 150.f, 0), Vector2((i + 1) * 150.f, 150.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Parry_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Parry_L",
		"Mugman_Parry_L", TEXT("Mugman/Mugman_Parry_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Parry_L",
			Vector2(i * 150.f, 0), Vector2((i + 1) * 150.f, 150.f));
	}

	// Hit
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Hit_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Hit_R",
		"Mugman_Hit_R", TEXT("Mugman/Mugman_Hit_R.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Hit_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 230.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Hit_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Hit_L",
		"Mugman_Hit_L", TEXT("Mugman/Mugman_Hit_L.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Hit_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 230.f));
	}

	// Death
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Death");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Death",
		"Mugman_Death", TEXT("Mugman/Mugman_Death.png"));
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Death",
				Vector2(x * 200.f, y * 230.f), Vector2((x + 1) * 200.f, (y + 1) * 230.f));
		}
	}

	// vfx
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dust");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dust",
		"Mugman_Dust", TEXT("Mugman/Mugman_Dust.png"));
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Dust",
				Vector2(x * 140.f, y * 140.f), Vector2((x + 1) * 140.f, (y + 1) * 140.f));
		}
	}

	// Duck
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_L",
		"Mugman_Duck_L", TEXT("Mugman/Mugman_Duck_L.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Duck_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_Loop_L",
		"Mugman_Duck_Loop_L", TEXT("Mugman/Mugman_Duck_Loop_L.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Duck_Loop_L",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_R",
		"Mugman_Duck_R", TEXT("Mugman/Mugman_Duck_R.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Duck_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_Loop_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_Loop_R",
		"Mugman_Duck_Loop_R", TEXT("Mugman/Mugman_Duck_Loop_R.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Duck_Loop_R",
			Vector2(i * 200.f, 0), Vector2((i + 1) * 200.f, 200.f));
	}
}

void CTutorialScene::CreateWeaponAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Loop_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Loop_R",
		"Bullet_Loop_R", TEXT("Weapon/Bullet_Loop_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Bullet_Loop_R",
			Vector2(i * 180.f, 0), Vector2((i + 1) * 180.f, 40.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Loop_L",
		"Bullet_Loop_L", TEXT("Weapon/Bullet_Loop_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Bullet_Loop_L",
			Vector2(i * 180.f, 0), Vector2((i + 1) * 180.f, 40.f));
	}
}


