#include "FightObject.h"

CFightObject::CFightObject() :m_HP(3), m_Attack(1), m_bCanAttack(true),
							m_Speed(500.f), m_bCanMove(true)
{

}

CFightObject::CFightObject(const CFightObject& obj) : CGameObject(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CFightObject::~CFightObject()
{
}

void CFightObject::Start()
{
	CGameObject::Start();
}

bool CFightObject::Init()
{
	CGameObject::Init();

	// 아래의 동작들은 해당 클래스를 상속받은 곳에서 실행할 것
	//m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	//m_Collider = CreateSceneComponent<CColliderBox2D>("Body");

	//SetRootComponent(m_Sprite);

	//m_Sprite->SetRelativeScale(150.f, 150.f, 1.f);
	//m_Sprite->SetRelativePos(200.f, 300.f, 0.f);
	////m_Sprite->SetRelativeRotationZ(30.f);
	////m_Sprite->SetPivot(0.f, 0.5f, 0.f);


	//m_Collider->SetExtent(50.f, 50.f);
	//m_Collider->SetPivot(0.f, 0.5f, 0.f);
	//m_Collider->SetCollisionProfile("Player");

	//m_Sprite->AddChild(m_Collider);

	//애니메이션은 상속을 받은 unit이 생성될때 제작
	//m_Sprite->CreateAnimation2D<CMugmanAnimation2D>();

	//m_Animation2D = m_Sprite->GetAnimation2D();
	//m_Animation2D->ChangeAnimation("Mugman_Idle_R");

	return true;
}

void CFightObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CFightObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CFightObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CFightObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CFightObject* CFightObject::Clone()
{
	return new CFightObject(*this);
}