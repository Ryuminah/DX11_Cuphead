#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "Scene/Viewport.h"
#include "../Object/Mugman.h"
#include "../Object/DragonMap.h"
#include "../Object/StepCloud.h"
#include "../Object/GroundCollider.h"
#include "../Object/Dragon.h"



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
	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	CDragonMap* pDragonMap = m_pScene->SpawnObject<CDragonMap>("DragonMap");
	CGroundCollider* pGroundCollider= m_pScene->SpawnObject<CGroundCollider>("Ground");
	CDragon* pDragon = m_pScene->SpawnObject<CDragon>("Dragon");

	CreateStepCloud();

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
	CreateWeaponAnim();
	CreateDragonAnim();
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

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_R",
		"Mugman_Run_Shoot_R", TEXT("Mugman/Mugman_Run_Shoot_R.png"));
	for (int i = 0; i < 16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_R",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_L",
		"Mugman_Run_Shoot_L", TEXT("Mugman/Mugman_Run_Shoot_L.png"));
	for (int i = 0; i < 16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Run_Shoot_L",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_R",
		"Mugman_Shoot_R", TEXT("Mugman/Mugman_Shoot_R.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_R",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200, 200.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_L",
		"Mugman_Shoot_L", TEXT("Mugman/Mugman_Shoot_L.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Mugman_Shoot_L",
			Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200, 200.f));
	}

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
}

void CMainScene::CreateStepCloudAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down",
		"Cloud_Down", TEXT("Cloud_Down.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Down_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Down_Idle",
		"Cloud_Down_Idle", TEXT("Cloud_Down_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Down_Idle",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Idle",
		"Cloud_Idle", TEXT("Cloud_Idle.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Idle",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 250.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Cloud_Up");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Cloud_Up",
		"Cloud_Up", TEXT("Cloud_Up.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Cloud_Up",
			Vector2(i * 250.f, 0), Vector2((i + 1) * 250.f, 250.f));
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
			Vector2(i * 180.f, 0), Vector2((i + 1) * 180.f, 180.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Loop_L",
		"Bullet_Loop_L", TEXT("Weapon/Bullet_Loop_L.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Bullet_Loop_L",
			Vector2(i * 180.f, 0), Vector2((i + 1) * 180.f, 180.f));
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
}

void CMainScene::CreateStepCloud()
{
	CStepCloud* pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(150.f, 190.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(160.f, 570.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(420.f, 390.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(460.f, 120.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(690.f, 540.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(810.f, 180.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(1000.f, 370.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(1200.f, 600.f, 0.f);

	pStepCloud = m_pScene->SpawnObject<CStepCloud>("StepCloud");
	pStepCloud->SetWorldPos(1450.f, 400.f, 0.f);

}
