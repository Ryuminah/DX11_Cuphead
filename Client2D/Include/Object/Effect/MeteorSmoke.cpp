#include "MeteorSmoke.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Component/SpriteComponent.h"

CMeteorSmoke::CMeteorSmoke()
{

}

CMeteorSmoke::CMeteorSmoke(const CMeteorSmoke& obj) :
	CMeteorSmoke(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("CMeteorSmoke");
}

CMeteorSmoke::~CMeteorSmoke()
{
}

void CMeteorSmoke::Start()
{
	CMeteorSmoke::Start();
}

bool CMeteorSmoke::Init()
{
	CMeteorSmoke::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("CMeteorSmoke");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(640.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1381.f, 84.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	//m_Sprite->CreateAnimation2D<CBackGround_CloudAnim>();
	m_Animation= m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("CMeteorSmoke");

	return true;
}

void CMeteorSmoke::Update(float DeltaTime)
{
	CMeteorSmoke::Update(DeltaTime);
}

void CMeteorSmoke::PostUpdate(float DeltaTime)
{
	CMeteorSmoke::PostUpdate(DeltaTime);
}

void CMeteorSmoke::Collision(float DeltaTime)
{
	CMeteorSmoke::Collision(DeltaTime);
}

void CMeteorSmoke::Render(float DeltaTime)
{
	CMeteorSmoke::Render(DeltaTime);
}

CMeteorSmoke* CMeteorSmoke::Clone()
{
	return new CMeteorSmoke(*this);
}

