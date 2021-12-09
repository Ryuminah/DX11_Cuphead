#include "Dust.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/MugmanAnimation2D.h"

CDust::CDust()
{

}

CDust::CDust(const CDust& obj) :
	CEffect(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Dust");
}

CDust::~CDust()
{
}

void CDust::Start()
{
	CEffect::Start();
	SetDefaultZ(0.5f);
}

bool CDust::Init()
{
	CEffect::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Dust");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(140.f, 140.f, 1.f);

	m_Sprite->CreateAnimation2D<CMugmanAnimation2D>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Mugman_Dust");

	m_Animation->SetFrameEndFunction<CDust>(this, &CDust::AnimEnd);

	return true;
}

void CDust::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CDust::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CDust::Collision(float DeltaTime)
{
	CEffect::Collision(DeltaTime);
}

void CDust::Render(float DeltaTime)
{
	CEffect::Render(DeltaTime);
}

CDust* CDust::Clone()
{
	return new CDust(*this);
}

void CDust::AnimEnd(const std::string& Name)
{
	// 애니메이션이 종료되면 바로 삭제
	Active(false);
}

