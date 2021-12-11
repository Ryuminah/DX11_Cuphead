#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/FG_LoadingAnim.h"
#include "FG_Loading.h"

FG_Loading::FG_Loading()
{

}

FG_Loading::FG_Loading(const FG_Loading& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FG_Loading");
}

FG_Loading::~FG_Loading()
{
}

void FG_Loading::Start()
{
	CBackGround::Start();
}

bool FG_Loading::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("FG_Loading");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativePos(1180.f, 20.0f, 0.f);
	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);

	m_Sprite->CreateAnimation2D<FG_LoadingAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("FG_Loading");

	return true;
}

void FG_Loading::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void FG_Loading::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void FG_Loading::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void FG_Loading::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

FG_Loading* FG_Loading::Clone()
{
	return new FG_Loading(*this);
}
