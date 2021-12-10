#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "Scene/Viewport.h"
#include "../Object/Character/Mugman.h"
#include "../Object/Character/Dragon.h"
#include "../Object/Static/StepCloud.h"
#include "../Object/Collision/GroundCollider.h"
#include "../Object/BackGround/BG_DragonMap.h"
#include "../Object/BackGround/FG_Normal_Cloud1.h"
#include "../Object/BackGround/FG_Normal_Cloud2.h"
#include "../Object/BackGround/FG_Normal_Cloud3.h"




CMainScene::CMainScene() : m_pGameStart(false) , m_WaitTime(2.f)
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

	//m_pScene->GetResource()->LoadSound("UI", false, "ButtonMouseOn",
	//	"TeemoSmile.mp3");
	//m_pScene->GetResource()->LoadSound("UI", false, "ButtonClick",
	//	"TeemoStartClicck.mp3");

	// Create BackGround
	CreateBackGround();

	// Create GameObject
	CGroundCollider* pGroundCollider= m_pScene->SpawnObject<CGroundCollider>("Ground");
	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	CDragon* pDragon = m_pScene->SpawnObject<CDragon>("Dragon");

	CreateStepCloud();

	return true;
}


void CMainScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateMaterial("PlayerChild");
	m_pScene->GetResource()->AddMaterialTexture("PlayerChild", "PlayerChild",
		TEXT("Teemo.jpg"));
}

void CMainScene::CreateAnimationSequence2D()
{
	CreateMugmanAnim();
	CreateStepCloudAnim();
	CreateWeaponAnim();
	CreateDragonAnim();
	CreateBackGroundImage();
}

void CMainScene::CreateParticle()
{
}

void CMainScene::CreateMugmanAnim()
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
}

void CMainScene::CreateStepCloudAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down",
		"Cloud_Down", TEXT("Cloud_Down.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down_Idle",
		"Cloud_Down_Idle", TEXT("Cloud_Down_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down_Idle",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Idle",
		"Cloud_Idle", TEXT("Cloud_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Idle",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Up");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Up",
		"Cloud_Up", TEXT("Cloud_Up.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Up",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 70.f));
	}
}

void CMainScene::CreateWeaponAnim()
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

void CMainScene::CreateDragonAnim()
{
	//Phase1
	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Idle",
		"Dragon_Idle", TEXT("Enemy/Dragon_Idle.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int i = 0; i < 8; ++i)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Idle",
				Vector2(i * 870.f, y * 870.f), Vector2((i + 1) * 870.f, (y + 1) * 870.f));
		}
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Peashot_Start");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Peashot_Start",
		"Dragon_Peashot_Start", TEXT("Enemy/Dragon_Peashot_Start.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Peashot_Start",
			Vector2(i * 900.f, 0), Vector2((i + 1) * 900.f, 900.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Peashot_Attack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Peashot_Attack",
		"Dragon_Peashot_Attack", TEXT("Enemy/Dragon_Peashot_Attack.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int i = 0; i < 8; ++i)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Peashot_Attack",
				Vector2(i * 900.f, y * 870.f), Vector2((i + 1) * 900.f, (y + 1) * 900.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Peashot_End");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Peashot_End",
		"Dragon_Peashot_End", TEXT("Enemy/Dragon_Peashot_End.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Peashot_End",
			Vector2(i * 900.f, 0), Vector2((i + 1) * 900.f, 900.f));
	}
	
	
	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Tail");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Tail",
		"Dragon_Tail", TEXT("Enemy/Dragon_Tail.png"));
	for (int i = 0; i < 12; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Tail",
			Vector2(i * 330.f, 0), Vector2((i + 1) * 330.f, 870.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Meteor_Start");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Meteor_Start",
		"Dragon_Meteor_Start", TEXT("Enemy/Dragon_Meteor_Start.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int i = 0; i < 8; ++i)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Meteor_Start",
				Vector2(i * 900.f, y * 870.f), Vector2((i + 1) * 900.f, (y + 1) * 900.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Meteor_Attack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Meteor_Attack",
		"Dragon_Meteor_Attack", TEXT("Enemy/Dragon_Meteor_Attack.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Meteor_Attack",
			Vector2(i * 900.f, 0), Vector2((i + 1) * 900.f, 900.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Meteor_End");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Meteor_End",
		"Dragon_Meteor_End", TEXT("Enemy/Dragon_Meteor_End.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Meteor_End",
			Vector2(i * 900.f, 0), Vector2((i + 1) * 900.f, 900.f));
	}


	// Phase2
	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Dash");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Dash",
		"Dragon_Dash", TEXT("Enemy/Phase2/Dragon_Dash.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Dash",
				Vector2(x * 480.f, y * 130.f), Vector2((x + 1) * 480.f, (y + 1) * 130.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Idle2");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Idle2",
		"Dragon_Idle2", TEXT("Enemy/Phase2/Dragon_Idle2.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Idle2",
				Vector2(x * 670.f, y * 600.f), Vector2((x + 1) * 670.f, (y + 1) * 600.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Tounge_Start");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Tounge_Start",
		"Dragon_Tounge_Start", TEXT("Enemy/Phase2/Dragon_Tounge_Start.png"));
	for (int y = 0; y < 7; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Tounge_Start",
				Vector2(x * 1180.f, y * 150.f), Vector2((x + 1) * 1180.f, (y + 1) * 150.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Tounge_Loop");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Tounge_Loop",
		"Dragon_Tounge_Loop", TEXT("Enemy/Phase2/Dragon_Tounge_Loop.png"));
	for (int i = 0; i < 2; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Tounge_Loop",
			Vector2(i * 1180.f, 0), Vector2((i + 1) * 1180.f, 150.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Idle",
		"Fireboy_Idle", TEXT("Enemy/Phase2/Fireboy_Idle.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Idle",
				Vector2(x * 110.f, y * 160.f), Vector2((x + 1) * 110.f, (y + 1) * 160.f));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Cast");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Cast",
		"Fireboy_Cast", TEXT("Enemy/Phase2/Fireboy_Cast.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Cast",
			Vector2(i * 130.f, 0), Vector2((i + 1) * 130.f, 160.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Cast_Loop");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Cast_Loop",
		"Fireboy_Cast_Loop", TEXT("Enemy/Phase2/Fireboy_Cast_Loop.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Cast_Loop",
			Vector2(i * 130.f, 0), Vector2((i + 1) * 130.f, 160.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Jump_Start");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Jump_Start",
		"Fireboy_Jump_Start", TEXT("Enemy/Phase2/Fireboy_Jump_Start.png"));
	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Jump_Start",
			Vector2(i * 130.f, 0), Vector2((i + 1) * 130.f, 160.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Jump_Loop_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Jump_Loop_R",
		"Fireboy_Jump_Loop_R", TEXT("Enemy/Phase2/Fireboy_Jump_Loop_R.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Jump_Loop_R",
			Vector2(i * 130.f, 0), Vector2((i + 1) * 130.f, 160.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Fireboy_Jump_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Fireboy_Jump_Loop_L",
		"Fireboy_Jump_Loop_L", TEXT("Enemy/Phase2/Fireboy_Jump_Loop_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Fireboy_Jump_Loop_L",
			Vector2(i * 130.f, 0), Vector2((i + 1) * 130.f, 160.f));
	}



	// Dragon sfx
	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Peashot_Ring");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Peashot_Ring",
		"Dragon_Peashot_Ring", TEXT("Enemy/Dragon_Peashot_Ring.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Peashot_Ring",
			Vector2(i * 100.f, 0), Vector2((i + 1) * 100.f, 140.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Peashot_Ring_Pink");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Peashot_Ring_Pink",
		"Dragon_Peashot_Ring_Pink", TEXT("Enemy/Dragon_Peashot_Ring_Pink.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Peashot_Ring_Pink",
			Vector2(i * 100.f, 0), Vector2((i + 1) * 100.f, 140.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_Meteor");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_Meteor",
		"Dragon_Meteor", TEXT("Enemy/Dragon_Meteor.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_Meteor",
			Vector2(i * 240.f, 0), Vector2((i + 1) * 240.f, 240.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Dragon_MeteorSmoke");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Dragon_MeteorSmoke",
		"Dragon_MeteorSmoke", TEXT("Enemy/Dragon_MeteorSmoke.png"));
	for (int y = 0; y < 5; ++y)
	{
		for (int i = 0; i < 7; ++i)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Dragon_MeteorSmoke",
				Vector2(i * 240.f, y * 240.f), Vector2((i + 1) * 240.f, (y + 1) * 240.f));
		}
	}
}

void CMainScene::CreateStepCloud()
{
	CStepCloud* pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(150.f, 190.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(170.f, 500.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(415.f, 350.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(460.f, 120.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(690.f, 530.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(810.f, 180.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(1000.f, 360.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(1300.f, 450.f, 0.f);

	/*pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetRelativePos(1450.f, 400.f, 0.f);*/

}

void CMainScene::CreateBackGround()
{
	BG_DragonMap* pDragonMap = m_pScene->SpawnObject<BG_DragonMap>("BG_DragonMap");
	FG_Normal_Cloud1* pFGCloud1 = m_pScene->SpawnObject<FG_Normal_Cloud1>("FG_Cloud1");
	FG_Normal_Cloud2* pFGCloud2 = m_pScene->SpawnObject<FG_Normal_Cloud2>("FG_Cloud2");
	FG_Normal_Cloud3* pFGCloud3 = m_pScene->SpawnObject<FG_Normal_Cloud3>("FG_Cloud3");
}

void CMainScene::CreateBackGroundImage()
{
	// UV 애니메이션을 위해 Sequence로 생성함
	// Foreground Normal 
	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Normal_Cloud1");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Normal_Cloud1",
		"FG_Normal_Cloud1", TEXT("BackGround/FG_Normal_Cloud1.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Normal_Cloud1",
		Vector2(0.f, 0.f), Vector2(1381.f, 84.f));
	
	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Normal_Cloud2");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Normal_Cloud2",
		"FG_Normal_Cloud2", TEXT("BackGround/FG_Normal_Cloud2.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Normal_Cloud2",
		Vector2(0.f, 0.f), Vector2(1561.f, 185.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Normal_Cloud3");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Normal_Cloud3",
		"FG_Normal_Cloud3", TEXT("BackGround/FG_Normal_Cloud3.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Normal_Cloud3",
		Vector2(0.f, 0.f), Vector2(1513.f, 198.f));

	// Night
	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Night_Cloud1");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Night_Cloud1",
		"FG_Night_Cloud1", TEXT("BackGround/FG_Night_Cloud1.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Night_Cloud1",
		Vector2(0.f, 0.f), Vector2(859.f, 54.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Night_Cloud2");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Night_Cloud2",
		"FG_Night_Cloud2", TEXT("BackGround/FG_Night_Cloud2.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Night_Cloud2",
		Vector2(0.f, 0.f), Vector2(971.f, 114.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_Night_Cloud3");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_Night_Cloud3",
		"FG_Night_Cloud3", TEXT("BackGround/FG_Night_Cloud3.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FG_Night_Cloud3",
		Vector2(0.f, 0.f), Vector2(934.f, 124.f));


	// BackGround
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_Cloud1");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_Cloud1",
		"BG_Normal_Cloud1", TEXT("BackGround/BG_Normal_Cloud1.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_Cloud1",
		Vector2(0.f, 0.f), Vector2(1565.f, 279.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_Cloud2");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_Cloud2",
		"BG_Normal_Cloud2", TEXT("BackGround/BG_Normal_Cloud2.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_Cloud2",
		Vector2(0.f, 0.f), Vector2(1945.f, 286.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_Cloud3");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_Cloud3",
		"BG_Normal_Cloud3", TEXT("BackGround/BG_Normal_Cloud3.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_Cloud3",
		Vector2(0.f, 0.f), Vector2(2047.f, 374.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_Cloud4");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_Cloud4",
		"BG_Normal_Cloud4", TEXT("BackGround/BG_Normal_Cloud4.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_Cloud4",
		Vector2(0.f, 0.f), Vector2(1931.f, 318.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_Cloud5");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_Cloud5",
		"BG_Normal_Cloud5", TEXT("BackGround/BG_Normal_Cloud5.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_Cloud5",
		Vector2(0.f, 0.f), Vector2(1870.f, 342.f));



	
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Normal_DragonMap");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Normal_DragonMap",
		"BG_Normal_DragonMap", TEXT("BackGround/BG_Normal_DragonMap.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Normal_DragonMap",
		Vector2(0.f, 0.f), Vector2(1280.f, 720.f));
}
