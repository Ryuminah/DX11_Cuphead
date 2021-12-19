#include "BulletDeath.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BulletAnimation.h"

CBulletDeath::CBulletDeath()
{

}

CBulletDeath::CBulletDeath(const CBulletDeath& obj) :
	CEffect(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BulletDeath");
}

CBulletDeath::~CBulletDeath()
{
}

void CBulletDeath::Start()
{
	CEffect::Start();
	SetDefaultZ(0.5f);
}

bool CBulletDeath::Init()
{
	CEffect::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BulletDeath");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(280.f, 280.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CBulletAnimation>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Bullet_Death");

	m_Animation->SetFrameEndFunction<CBulletDeath>(this, &CBulletDeath::AnimEnd);

	return true;
}

void CBulletDeath::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CBulletDeath::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CBulletDeath::Collision(float DeltaTime)
{
	CEffect::Collision(DeltaTime);
}

void CBulletDeath::Render(float DeltaTime)
{
	CEffect::Render(DeltaTime);
}

CBulletDeath* CBulletDeath::Clone()
{
	return new CBulletDeath(*this);
}

void CBulletDeath::AnimEnd(const std::string& Name)
{
	Active(false);
}

