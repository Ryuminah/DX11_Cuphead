#include "FG_Normal_Cloud1.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround_CloudAnim.h"

FG_Normal_Cloud1::FG_Normal_Cloud1()
{

}

FG_Normal_Cloud1::FG_Normal_Cloud1(const FG_Normal_Cloud1& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FG_Normal_Cloud1");
}

FG_Normal_Cloud1::~FG_Normal_Cloud1()
{
}

void FG_Normal_Cloud1::Start()
{
	CBackGround::Start();

	//UV Flow
	// FG : Direction(true)	BG : Direction (false)
	m_Sprite->SetAnimation2DEnable(false);
	m_Sprite->SetUVFlow2DEnable(true);
	m_Sprite->SetUVFlow2DSpeed(0.2f);
	m_Sprite->SetUVFlow2DDirection(true);
	m_Sprite->GetMaterial(0)->SetOpacity(0.6f);
}

bool FG_Normal_Cloud1::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("FG_Normal_Cloud1");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(640.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1381.f, 84.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	m_Sprite->CreateAnimation2D<CBackGround_CloudAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("FG_Normal_Cloud1");

	return true;
}

void FG_Normal_Cloud1::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void FG_Normal_Cloud1::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void FG_Normal_Cloud1::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void FG_Normal_Cloud1::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

FG_Normal_Cloud1* FG_Normal_Cloud1::Clone()
{
	return new FG_Normal_Cloud1(*this);
}
