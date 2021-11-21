#include "Dragon.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/DragonAnimation.h"
#include "Engine.h"

CDragon::CDragon() : m_CurrentPhase(Phase::Phase1)
{

}

CDragon::CDragon(const CDragon& obj) : CCharacter(obj)
{

	m_Sprite = (CSpriteComponent*)FindSceneComponent("Dragon");
	m_Collider = (CColliderBox2D*)FindSceneComponent("DragonCollider");
	//m_Rotation = FindSceneComponent("Rotation");
	//m_Muzzle = FindSceneComponent("Muzzle");
}

CDragon::~CDragon()
{
}

void CDragon::Start()
{
	CGameObject::Start();
}

bool CDragon::Init()
{
	CCharacter::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Dragon");
	m_Collider = CreateSceneComponent<CColliderBox2D>("DragonCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_Muzzle = CreateSceneComponent<CSceneComponent>("Muzzle");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(870.f, 870.f, 1.f);
	m_Sprite->SetRelativePos(1200.f, -120.f, 0.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Muzzle);

	m_Collider->SetExtent(250.f, 400.f);
	m_Collider->SetCollisionProfile("Enemy");
	m_Collider->SetColliderType(Collider_Type::Character);
	//m_Collider->SetPivot(0.5f, 0.f, 0.f);

	m_Muzzle->SetInheritRotZ(true);
	m_Muzzle->SetRelativePos(Vector3(20.f, 80.f, 0.f));
	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimationFrameEnd);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	SetDefaultZ(0.1f);
	SetPhysicsSimulate(false);
	SetUseBlockMovement(false);
	SetPrevDirection(Direction::LEFT);

	m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::Begin, this, &CDragon::CollisionBegin);
	//m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::Overlap, this, &CDragon::CollisionOverlap);
	//m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::End, this, &CDragon::CollisionEnd);


	return true;
}

void CDragon::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CDragon::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CDragon::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CDragon::Render(float DeltaTime)
{
	CCharacter::Render(DeltaTime);
}

CDragon* CDragon::Clone()
{
	return new CDragon(*this);
}

void CDragon::Animation2DNotify(const std::string& Name)
{
	CCharacter::Animation2DNotify(Name);
}

void CDragon::AnimationFrameEnd(const std::string& Name)
{
	// 현재 애니메이션이 Dash일 경우
}

void CDragon::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetName() == "BulletCollider")
	{
		HitCheck();
		m_Sprite->GetMaterial(0)->SetMaterialTimerBaseColor(1.f, 0.f, 0.f, 0.5f);
		m_Sprite->GetMaterial(0)->UseMaterialTimer(0.01f);

		int check = m_HitCount;
		
	}
}






