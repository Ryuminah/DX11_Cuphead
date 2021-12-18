#include "BulletSpawn.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BulletAnimation.h"

CBulletSpawn::CBulletSpawn()
{

}

CBulletSpawn::CBulletSpawn(const CBulletSpawn& obj) :
	CEffect(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BulletSpawn");
}

CBulletSpawn::~CBulletSpawn()
{
}

void CBulletSpawn::Start()
{
	CEffect::Start();
	SetDefaultZ(0.5f);
}

bool CBulletSpawn::Init()
{
	CEffect::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BulletSpawn");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(180.f, 180.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CBulletAnimation>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Bullet_Spawn");

	m_Animation->SetFrameEndFunction<CBulletSpawn>(this, &CBulletSpawn::AnimEnd);

	return true;
}

void CBulletSpawn::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CBulletSpawn::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CBulletSpawn::Collision(float DeltaTime)
{
	CEffect::Collision(DeltaTime);
}

void CBulletSpawn::Render(float DeltaTime)
{
	CEffect::Render(DeltaTime);
}

CBulletSpawn* CBulletSpawn::Clone()
{
	return new CBulletSpawn(*this);
}

void CBulletSpawn::AnimEnd(const std::string& Name)
{
	Active(false);
}

