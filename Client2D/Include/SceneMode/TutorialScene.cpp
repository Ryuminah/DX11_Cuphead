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
#include "../UI/KettleHouse/BubbleTextWidget.h"
#include "../Object/BackGround/ScreenFX.h"




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
	CreateElderKettleAnim();
	CreateSound();
	CreateTutorialMap();

	// ´ó±Û¸µ ¿Ö »ý±â´© °íÃÆ´© &^^
	CMugman* pMugman = m_pScene->SpawnObject<CMugman>("Mugman");
	CMugman::bUseCamera = true;
	pMugman->SetRelativePos(300.f, 120.f, 0.f);

	ScreenFX* pScreenFX = m_pScene->SpawnObject<ScreenFX>("ScreenFX");

	return true;
}

void CTutorialScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001 || BG_TutorialMap::IsExit)
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

	m_pScene->GetResource()->CreateAnimationSequence2D("FieryFrolic");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FieryFrolic",
		"FieryFrolic", TEXT("BackGround/Tutorial/FieryFrolic.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("FieryFrolic",
		Vector2(0.f, 0.f), Vector2(240.f, 60.f));
}

void CTutorialScene::CreateMugmanAnim()
{
	// Idle
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_R",
		"Mugman_Idle_R", TEXT("Mugman/Mugman_Idle_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Idle_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Idle_L",
		"Mugman_Idle_L", TEXT("Mugman/Mugman_Idle_L.png"));


	// Run
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Normal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Normal_R",
		"Mugman_Run_Normal_R", TEXT("Mugman/Mugman_Run_Normal_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Normal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Normal_L",
		"Mugman_Run_Normal_L", TEXT("Mugman/Mugman_Run_Normal_L.png"));
	
	// Shoot_Run
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_R",
		"Mugman_Run_Shoot_R", TEXT("Mugman/Mugman_Run_Shoot_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Run_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Run_Shoot_L",
		"Mugman_Run_Shoot_L", TEXT("Mugman/Mugman_Run_Shoot_L.png"));
	

	// Shoot_Normal
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_R",
		"Mugman_Shoot_R", TEXT("Mugman/Mugman_Shoot_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Shoot_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Shoot_L",
		"Mugman_Shoot_L", TEXT("Mugman/Mugman_Shoot_L.png"));


	// Jump
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_R",
		"Mugman_Jump_R", TEXT("Mugman/Mugman_Jump_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Jump_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Jump_L",
		"Mugman_Jump_L", TEXT("Mugman/Mugman_Jump_L.png"));


	// Aim
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Aim_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Aim_R",
		"Mugman_Aim_R", TEXT("Mugman/Mugman_Aim_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Aim_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Aim_L",
		"Mugman_Aim_L", TEXT("Mugman/Mugman_Aim_L.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_R",
		"Mugman_AimUp_R", TEXT("Mugman/Mugman_AimUp_R.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_L",
		"Mugman_AimUp_L", TEXT("Mugman/Mugman_AimUp_L.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_R",
		"Mugman_AimDown_R", TEXT("Mugman/Mugman_AimDown_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_L",
		"Mugman_AimDown_L", TEXT("Mugman/Mugman_AimDown_L.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_Digonal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_Digonal_R",
		"Mugman_AimUp_Digonal_R", TEXT("Mugman/Mugman_AimUp_Digonal_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimUp_Digonal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimUp_Digonal_L",
		"Mugman_AimUp_Digonal_L", TEXT("Mugman/Mugman_AimUp_Digonal_L.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_Digonal_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_Digonal_R",
		"Mugman_AimDown_Digonal_R", TEXT("Mugman/Mugman_AimDown_Digonal_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_AimDown_Digonal_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_AimDown_Digonal_L",
		"Mugman_AimDown_Digonal_L", TEXT("Mugman/Mugman_AimDown_Digonal_L.png"));


	// Dash
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_R",
		"Mugman_Dash_R", TEXT("Mugman/Mugman_Dash_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dash_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dash_L",
		"Mugman_Dash_L", TEXT("Mugman/Mugman_Dash_L.png"));
	

	// Parry
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Parry_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Parry_R",
		"Mugman_Parry_R", TEXT("Mugman/Mugman_Parry_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Parry_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Parry_L",
		"Mugman_Parry_L", TEXT("Mugman/Mugman_Parry_L.png"));


	// Hit
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Hit_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Hit_R",
		"Mugman_Hit_R", TEXT("Mugman/Mugman_Hit_R.png"));
	
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Hit_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Hit_L",
		"Mugman_Hit_L", TEXT("Mugman/Mugman_Hit_L.png"));
	

	// Death
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Death");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Death",
		"Mugman_Death", TEXT("Mugman/Mugman_Death.png"));
	

	// vfx
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Dust");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Dust",
		"Mugman_Dust", TEXT("Mugman/Mugman_Dust.png"));
	

	// Duck
	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_L",
		"Mugman_Duck_L", TEXT("Mugman/Mugman_Duck_L.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_Loop_L",
		"Mugman_Duck_Loop_L", TEXT("Mugman/Mugman_Duck_Loop_L.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_R",
		"Mugman_Duck_R", TEXT("Mugman/Mugman_Duck_R.png"));
	

	m_pScene->GetResource()->CreateAnimationSequence2D("Mugman_Duck_Loop_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Mugman_Duck_Loop_R",
		"Mugman_Duck_Loop_R", TEXT("Mugman/Mugman_Duck_Loop_R.png"));
	
}

void CTutorialScene::CreateWeaponAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Loop_R");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Loop_R",
		"Bullet_Loop_R", TEXT("Weapon/Bullet_Loop_R.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Loop_L");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Loop_L",
		"Bullet_Loop_L", TEXT("Weapon/Bullet_Loop_L.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Spawn");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Spawn",
		"Bullet_Spawn", TEXT("Weapon/Bullet_Spawn.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Bullet_Death");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Bullet_Death",
		"Bullet_Death", TEXT("Weapon/Bullet_Death.png"));

}

void CTutorialScene::CreateElderKettleAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_KettleHouse");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_KettleHouse",
		"BG_KettleHouse", TEXT("BackGround/BG_KettleHouse.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("FG_KettleHouse");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FG_KettleHouse",
		"FG_KettleHouse", TEXT("BackGround/FG_KettleHouse.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Arrow");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Arrow",
		"Arrow", TEXT("ElderHouse/Arrow.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("BubbleTail");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BubbleTail",
		"BubbleTail", TEXT("ElderHouse/BubbleTail.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("SpeechBubble");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SpeechBubble",
		"SpeechBubble", TEXT("ElderHouse/SpeechBubble.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("Z");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Z",
		"Z", TEXT("ElderHouse/Z.png"));


	m_pScene->GetResource()->CreateAnimationSequence2D("TutorialZ");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("TutorialZ",
		"TutorialZ", TEXT("ElderHouse/TutorialZ.png"));



	m_pScene->GetResource()->CreateAnimationSequence2D("ElderKettle_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("ElderKettle_Idle",
		"ElderKettle_Idle", TEXT("ElderHouse/ElderKettle_Idle.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("FadeIn");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FadeIn",
		"FadeIn", TEXT("BackGround/FadeIn.png"));

	m_pScene->GetResource()->CreateAnimationSequence2D("FadeOut");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("FadeOut",
		"FadeOut", TEXT("BackGround/FadeIn.png"));

}

void CTutorialScene::CreateSound()
{
	m_pScene->GetResource()->LoadSound("Effect", false, "MUS_Tutorial",
		"BGM/MUS_Tutorial.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "Menu_Move",
		"Menu_Move.wav");

	//PlayerSound
	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_dash",
		"Mugman/sfx_player_dash.wav");

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_hit",
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

	m_pScene->GetResource()->LoadSound("Effect", false, "sfx_player_parry",
		"Mugman/sfx_player_parry.wav");
}


