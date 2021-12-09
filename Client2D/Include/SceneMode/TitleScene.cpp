#include "TitleScene.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "../UI/TitleScene/TitleSceneWidget.h"
#include "../Object/BackGround/BG_TitleScene.h"


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
