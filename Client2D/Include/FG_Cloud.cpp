#include "FG_Cloud.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

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

	SetRootComponent(m_BackGround);
	m_BackGround->SetRelativePos(720.f, 0.0f, 0.f);
	m_BackGround->SetRelativeScale(1565.f, 279.f, 1.f);
	m_BackGround->SetMaterial(0, "FG_Cloud");

	m_BackGround->SetRender2DType(Render_Type_2D::RT2D_MAP);

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
