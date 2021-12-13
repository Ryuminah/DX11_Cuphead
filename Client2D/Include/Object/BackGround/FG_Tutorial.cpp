#include "FG_Tutorial.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"

FG_Tutorial::FG_Tutorial()
{

}

FG_Tutorial::FG_Tutorial(const FG_Tutorial& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FG_Tutorial");
}

FG_Tutorial::~FG_Tutorial()
{
}

void FG_Tutorial::Start()
{
	CBackGround::Start();;
}

bool FG_Tutorial::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("FG_Tutorial");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.0f, 0.0f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 720.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	m_Sprite->CreateAnimation2D<CTutorialSceneAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("FG_Tutorial");

	return true;
}

void FG_Tutorial::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void FG_Tutorial::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void FG_Tutorial::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void FG_Tutorial::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

FG_Tutorial* FG_Tutorial::Clone()
{
	return new FG_Tutorial(*this);
}
