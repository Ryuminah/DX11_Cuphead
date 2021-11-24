#include "FG_Cloud.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/ForeGroundAnim.h"

FG_Cloud::FG_Cloud()
{

}

FG_Cloud::FG_Cloud(const FG_Cloud& obj) :
	CGameObject(obj)
{
	m_BackGround = (CSpriteComponent*)FindSceneComponent("FG_Cloud");
}

FG_Cloud::~FG_Cloud()
{
}

void FG_Cloud::Start()
{
	CGameObject::Start();
}

bool FG_Cloud::Init()
{
	CGameObject::Init();

	m_BackGround = CreateSceneComponent<CSpriteComponent>("FG_Cloud");
	m_BackGround->CreateAnimation2D<CForeGroundAnim>();
	m_AnimImage = m_BackGround->GetAnimation2D();

	SetRootComponent(m_BackGround);
	m_BackGround->SetRelativePos(640.f, 0.0f, 0.f);
	m_BackGround->SetRelativeScale(1381.f, 84.f, 1.f);

	//UV Flow
	m_BackGround->SetAnimation2DEnable(false);
	m_BackGround->SetUVFlow2DEnable(true);
	m_BackGround->SetUVFlow2DSpeed(0.3f);
	m_BackGround->SetUVFlow2DDirection(true);
	
	//m_BackGround->SetUVFlowSpeed(10.f);
	m_BackGround->SetRender2DType(Render_Type_2D::RT2D_Particle);

	m_AnimImage->ChangeAnimation("FG_Cloud");

	return true;
}

void FG_Cloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void FG_Cloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void FG_Cloud::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void FG_Cloud::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

FG_Cloud* FG_Cloud::Clone()
{
	return new FG_Cloud(*this);
}
