#include "MeteorSmoke.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/DragonAnimation.h"

CMeteorSmoke::CMeteorSmoke()
{

}

CMeteorSmoke::CMeteorSmoke(const CMeteorSmoke& obj) :
	CEffect(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("MeteorSmoke");
}

CMeteorSmoke::~CMeteorSmoke()
{
}

void CMeteorSmoke::Start()
{
	CEffect::Start();
	SetDefaultZ(0.5f);
}

bool CMeteorSmoke::Init()
{
	CEffect::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("MeteorSmoke");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(240.f, 240.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_MeteorSmoke");

	m_Animation->SetFrameEndFunction<CMeteorSmoke>(this, &CMeteorSmoke::AnimEnd);

	return true;
}

void CMeteorSmoke::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CMeteorSmoke::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CMeteorSmoke::Collision(float DeltaTime)
{
	CEffect::Collision(DeltaTime);
}

void CMeteorSmoke::Render(float DeltaTime)
{
	CEffect::Render(DeltaTime);
}

CMeteorSmoke* CMeteorSmoke::Clone()
{
	return new CMeteorSmoke(*this);
}

void CMeteorSmoke::AnimEnd(const std::string& Name)
{
	// 애니메이션이 종료되면 바로 삭제
	Active(false);
}

