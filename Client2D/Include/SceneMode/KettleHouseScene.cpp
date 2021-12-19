#include "KettleHouseScene.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "LoadingThread.h"
#include "ThreadManager.h"
#include "../Object/Character/Mugman.h"
#include "../Object/BackGround/FG_Loading.h"
#include "../Object/BackGround/BG_KettleHouse.h"
#include "../Object/Collision/GroundCollider.h"
#include "Scene/SceneManager.h"
#include "LoadingScene.h"
#include "TutorialScene.h"
#include "../Object/BackGround/ElderKettle.h"
#include "../Object/BackGround/ScreenFX.h"


CKettleHouseScene::CKettleHouseScene()
{
	m_bTutorialOpen = false;
}

CKettleHouseScene::~CKettleHouseScene()
{
}

bool CKettleHouseScene::Init()
{
	CreateKettleHouseAnim();
	CreateMugmanAnim();
	CreateWeaponAnim();
	CreateSound();

	BG_KettleHouse* pKettleHouse = m_pScene->SpawnObject<BG_KettleHouse>("BG_KettleHouse");
	CGroundCollider* pGroundCollider = m_pScene->SpawnObject<CGroundCollider>("Ground");
	pGroundCollider->AddWorldPos(0.f, 50.f, 0.f);

	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	pMugman->SetIsFightScene(false);
	pMugman->SetRelativePos(100.f, 90.f, 0.f);

	CElderKettle* pElderKettle = m_pScene->SpawnObject<CElderKettle>("ElderKettle");
	pElderKettle->CreateSpeechBubble();

	ScreenFX* pScreenFX = m_pScene->SpawnObject<ScreenFX>("ScreenFX");


	return true;
}

void CKettleHouseScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001 || CElderKettle::IsTutorialOpen)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->SetSceneMode<CTutorialScene>(false);
	}
}

void CKettleHouseScene::CreateKettleHouseAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_KettleHouse");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_KettleHouse",
		"BG_KettleHouse", TEXT("BackGround/BG_KettleHouse.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_KettleHouse",
		Vector2(0.f, 0.f), Vector2(1280.f, 629.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_KettleHouse");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_KettleHouse",
		"FG_KettleHouse", TEXT("BackGround/FG_KettleHouse.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_KettleHouse",
		Vector2(0.f, 0.f), Vector2(1280.f, 629.f));

	CreateElderKettleAnim();
}

void CKettleHouseScene::CreateMugmanAnim()
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

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Intro");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Intro",
		"Mugman_Intro", TEXT("Mugman/Mugman_Intro.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 14; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Intro",
				Vector2(x * 200.f, y * 200.f), Vector2((x + 1) * 200.f, (y + 1) * 200.f));
		}
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

void CKettleHouseScene::CreateWeaponAnim()
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

	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Spawn");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Spawn",
		"Bullet_Spawn", TEXT("Weapon/Bullet_Spawn.png"));
	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Bullet_Spawn",
			Vector2(i * 180.f, 0), Vector2((i + 1) * 180.f, 180.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Death");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Death",
		"Bullet_Death", TEXT("Weapon/Bullet_Death.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Bullet_Death",
			Vector2(i * 280.f, 0), Vector2((i + 1) * 280.f, 280.f));
	}
}

void CKettleHouseScene::CreateElderKettleAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Arrow");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Arrow",
		"Arrow", TEXT("ElderHouse/Arrow.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Arrow",
			Vector2(i * 50.f, 0), Vector2((i + 1) * 50.f, 40.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("BubbleTail");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BubbleTail",
		"BubbleTail", TEXT("ElderHouse/BubbleTail.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BubbleTail",
		Vector2(0.f, 0.f), Vector2(29.f, 59.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("SpeechBubble");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SpeechBubble",
		"SpeechBubble", TEXT("ElderHouse/SpeechBubble.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("SpeechBubble",
		Vector2(0.f, 0.f), Vector2(677.f, 417.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Z");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Z",
		"Z", TEXT("ElderHouse/Z.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Z",
		Vector2(0.f, 0.f), Vector2(65.f, 65.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("TutorialZ");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("TutorialZ",
		"TutorialZ", TEXT("ElderHouse/TutorialZ.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("TutorialZ",
		Vector2(0.f, 0.f), Vector2(240.f, 60.f));


	m_pScene->GetResource()->CreateAnimationSequence2D("ElderKettle_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("ElderKettle_Idle",
		"ElderKettle_Idle", TEXT("ElderHouse/ElderKettle_Idle.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("ElderKettle_Idle",
			Vector2(i * 280.f, 0), Vector2((i + 1) * 280.f, 280.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("FadeIn");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FadeIn",
		"FadeIn", TEXT("BackGround/FadeIn.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("FadeIn",
				Vector2(x * 512.f, y * 288.f), Vector2((x + 1) * 512.f, (y + 1) * 288.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("FadeOut");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FadeOut",
		"FadeOut", TEXT("BackGround/FadeIn.png"));
	for (int y = 2; y > 0; --y)
	{
		for (int x = 8; x > 0; --x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("FadeOut",
				Vector2(x * 512.f, y * 288.f), Vector2((x -1) * 512.f, (y - 1) * 288.f));
		}
	}
}

void CKettleHouseScene::CreateSound()
{
	m_pScene->GetResource()->LoadSound("BGM", true, "MUS_ElderKettle",
		"BGM/MUS_ElderKettle.wav");

	m_pScene->GetResource()->LoadSound("Effect", false , "Menu_Move",
		"Menu_Move.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "Menu_CardUp",
		"Menu_CardUp.wav");

	//PlayerSound
	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_dash",
		"Mugman/sfx_player_dash.wav");

	m_pScene->GetResource()->LoadSound("Effect",false, "sfx_player_hit",
		"Mugman/sfx_player_hit.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_intro_cuphead",
		"Mugman/sfx_player_intro_cuphead.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_jump",
		"Mugman/sfx_player_jump.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_land",
		"Mugman/sfx_player_land.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_walk",
		"Mugman/sfx_player_walk.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_shoot_hit",
		"Mugman/sfx_player_shoot_hit.wav");

	m_pScene->GetResource()->LoadSound("Effect", true, "sfx_player_shoot_start",
		"Mugman/sfx_player_shoot_start.wav");

	m_pScene->GetResource()->SetVolume("BGM", 30);
	m_pScene->GetResource()->SetVolume("Effect", 30);

}




void CKettleHouseScene::SetTutorialOpen(bool TutorialOpen)
{
	m_bTutorialOpen = TutorialOpen;
}

