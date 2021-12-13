#include "BG_Tutorial.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"

BG_Tutorial::BG_Tutorial()
{

}

BG_Tutorial::BG_Tutorial(const BG_Tutorial& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_Tutorial");
}

BG_Tutorial::~BG_Tutorial()
{
}

void BG_Tutorial::Start()
{
	CBackGround::Start();;
}

bool BG_Tutorial::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_Tutorial");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.0f, 0.0f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 720.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Sprite->CreateAnimation2D<CTutorialSceneAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("BG_Tutorial");

	return true;
}

void BG_Tutorial::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void BG_Tutorial::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void BG_Tutorial::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_Tutorial::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_Tutorial* BG_Tutorial::Clone()
{
	return new BG_Tutorial(*this);
}
