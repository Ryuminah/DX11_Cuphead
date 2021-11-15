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

	// �Ʒ��� ���۵��� �ش� Ŭ������ ��ӹ��� ������ ������ ��
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

	//�ִϸ��̼��� ����� ���� unit�� �����ɶ� ����
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