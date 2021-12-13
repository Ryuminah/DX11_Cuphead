#include "GroundCollider.h"


CGroundCollider::CGroundCollider() : m_bIsTutorialScene(false)
{

}

CGroundCollider::CGroundCollider(const CGroundCollider& obj) : CGameObject(obj)
{
	m_TestCollider = (CColliderBox2D*)FindSceneComponent("GroundCollider");

}

CGroundCollider::~CGroundCollider()
{
}

void CGroundCollider::Start()
{
	CGameObject::Start();

	if (m_bIsTutorialScene)
	{
		m_TestCollider->SetExtent(3365.f, 60.f);
		m_TestCollider->SetRelativePos(0.f, 0.f, 0.f);
	}
}

bool CGroundCollider::Init()
{
	CGameObject::Init();

	m_TestCollider = CreateSceneComponent<CColliderBox2D>("GroundCollider");

	SetRootComponent(m_TestCollider);

	m_TestCollider->SetExtent(640.f, 20.f);
	m_TestCollider->SetPivot(0.0f, 0.0f, 0.f);
	m_TestCollider->SetRelativePos(0.f, 0.f, 0.f);
	m_TestCollider->SetCollisionProfile("Static");
	m_TestCollider->SetColliderType(Collider_Type::Static);

	SetUseBlockMovement(false);

	return true;
}

void CGroundCollider::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


}

void CGroundCollider::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CGroundCollider::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CGroundCollider::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CGroundCollider* CGroundCollider::Clone()
{
	return new CGroundCollider(*this);
}
