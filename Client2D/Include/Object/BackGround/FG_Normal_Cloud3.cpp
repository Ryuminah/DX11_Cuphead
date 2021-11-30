#include "FG_Normal_Cloud3.h"
#include "Scene/Scene.h"
#include "../../Animation2D/BackGround_CloudAnim.h"
#include "Resource/Material.h"


FG_Normal_Cloud3::FG_Normal_Cloud3()
{

}

FG_Normal_Cloud3::FG_Normal_Cloud3(const FG_Normal_Cloud3& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FG_Normal_Cloud3");
}

FG_Normal_Cloud3::~FG_Normal_Cloud3()
{
}

void FG_Normal_Cloud3::Start()
{
	CBackGround::Start();

	//UV Flow
	// FG : Direction(true)	BG : Direction (false)
	m_Sprite->SetAnimation2DEnable(false);
	m_Sprite->SetUVFlow2DEnable(true);
	m_Sprite->SetUVFlow2DSpeed(0.05f);
	m_Sprite->SetUVFlow2DDirection(true);
}

bool FG_Normal_Cloud3::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("FG_Normal_Cloud3");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(640.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1561.f, 185.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	m_Sprite->CreateAnimation2D<CBackGround_CloudAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("FG_Normal_Cloud3");

	SetDefaultZ(0.9f);

	return true;
}

void FG_Normal_Cloud3::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void FG_Normal_Cloud3::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void FG_Normal_Cloud3::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void FG_Normal_Cloud3::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

FG_Normal_Cloud3* FG_Normal_Cloud3::Clone()
{
	return new FG_Normal_Cloud3(*this);
}
