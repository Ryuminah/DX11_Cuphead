#include "TitleScene.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "../UI/TitleScene/TitleSceneWidget.h"
#include "../Object/BackGround/BG_TitleScene.h"
#include "Scene/SceneManager.h"
#include "KettleHouseScene.h"



CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::CreateTitleSceneAnim()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("BG_TitleScene");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_TitleScene",
		"BG_TitleScene", TEXT("BackGround/BG_TitleScene.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_TitleScene",
		Vector2(0.f, 0.f), Vector2(1280.f, 720.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("BG_Cuphead");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BG_Cuphead",
		"BG_Cuphead", TEXT("BackGround/BG_Cuphead.png"));
	m_pScene->GetResource()->AddAnimationSequence2DFrame("BG_Cuphead",
		Vector2(0.f, 0.f), Vector2(1093.f, 614.f));
}

void CTitleScene::CreateElderKettleAnim()
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
				Vector2(x * 512.f, y * 288.f), Vector2((x - 1) * 512.f, (y - 1) * 288.f));
		}
	}
}

bool CTitleScene::Init()
{
	//m_pScene->GetResource()->LoadSound("UI", false, "ButtonMouseOn",
	//	"TeemoSmile.mp3");
	//m_pScene->GetResource()->LoadSound("UI", false, "ButtonClick",
	//	"TeemoStartClicck.mp3");

	CreateTitleSceneAnim();

	BG_TitleScene* pTitleScene = m_pScene->SpawnObject<BG_TitleScene>("BG_TitleScene");
	CTitleSceneWidget* Widget = m_pScene->GetViewport()->AddWindow<CTitleSceneWidget>("TitleSceneWidget");

	return true;
}

void CTitleScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->SetSceneMode<CKettleHouseScene>(false);
	}
}
