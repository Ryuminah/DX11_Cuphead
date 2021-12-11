#include "DragonCollider.h"
#include "../Character/Dragon.h"

CDragonCollider::CDragonCollider(): m_pDragon(nullptr)
{

}

CDragonCollider::CDragonCollider(const CDragonCollider& obj) : CGameObject(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("DragonCollider");

}

CDragonCollider::~CDragonCollider()
{
}

void CDragonCollider::Start()
{
	CGameObject::Start();
}

bool CDragonCollider::Init()
{
	CGameObject::Init();

	m_Collider = CreateSceneComponent<CColliderBox2D>("DragonCollider");

	SetRootComponent(m_Collider);

	m_Collider->SetExtent(50.f, 360.f);
	m_Collider->SetRelativePos(1000.f, 0.f, 0.f);
	m_Collider->SetCollisionProfile("Static");
	m_Collider->SetColliderType(Collider_Type::Character);

	SetUseBlockMovement(false);

	m_Collider->AddCollisionCallbackFunction<CDragonCollider>(Collision_State::Begin, this, &CDragonCollider::CollisionBegin);
	m_Collider->AddCollisionCallbackFunction<CDragonCollider>(Collision_State::Overlap, this, &CDragonCollider::CollisionOverlap);
	m_Collider->AddCollisionCallbackFunction<CDragonCollider>(Collision_State::End, this, &CDragonCollider::CollisionEnd);

	return true;
}

void CDragonCollider::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


}

void CDragonCollider::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDragonCollider::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDragonCollider::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CDragonCollider* CDragonCollider::Clone()
{
	return new CDragonCollider(*this);
}

void CDragonCollider::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetName() == "BulletCollider")
	{

		/*result.DestObject->SetUseBlockMovement(true);
		Vector3 prevPos = result.DestObject->GetPrevWorldPos();
		result.DestObject->SetWorldPos(prevPos);*/
	}
	m_pDragon->CollisionBegin(result, Collider);

}

void CDragonCollider::CollisionOverlap(const HitResult& result, CCollider* Collider)
{
	m_pDragon->CollisionOverlap(result, Collider);
}

void CDragonCollider::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	m_pDragon->CollisionEnd(result, Collider);

}
