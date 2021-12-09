#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/BG_TitleSceneAnim.h"
#include "BG_TitleScene.h"

BG_TitleScene::BG_TitleScene()
{

}

BG_TitleScene::BG_TitleScene(const BG_TitleScene& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_DragonMap");
}

BG_TitleScene::~BG_TitleScene()
{
}

void BG_TitleScene::Start()
{
	CBackGround::Start();
}

bool BG_TitleScene::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_TitleScene");
	m_CupheadSprite = CreateSceneComponent<CSpriteComponent>("BG_Cuphead");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_CupheadSprite);

	m_Sprite->SetRelativePos(640.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 720.f, 1.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Sprite->CreateAnimation2D<BG_TitleSceneAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("BG_TitleScene");

	// Cuphead&Mugman Sprite
	m_CupheadSprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_CupheadSprite->SetRelativeScale(1093.f, 614.f, 1.f);
	m_CupheadSprite->SetRender2DType(Render_Type_2D::RT2D_Default);

	m_CupheadSprite->CreateAnimation2D<BG_TitleSceneAnim>();
	m_CupheadAnim = m_CupheadSprite->GetAnimation2D();
	m_CupheadAnim->ChangeAnimation("BG_Cuphead");

	return true;
}

void BG_TitleScene::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void BG_TitleScene::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void BG_TitleScene::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_TitleScene::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_TitleScene* BG_TitleScene::Clone()
{
	return new BG_TitleScene(*this);
}
