#include "Character.h"

CCharacter::CCharacter() :m_HitCount(0), m_bCanAttack(true), m_bIsAttack(false), m_bIsMove(false),
							m_Speed(500.f), m_bCanMove(true)
{

}

CCharacter::CCharacter(const CCharacter& obj) : CGameObject(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CCharacter::~CCharacter()
{

}

void CCharacter::Start()
{
	CGameObject::Start();
}

bool CCharacter::Init()
{
	CGameObject::Init();

	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CCharacter::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCharacter::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CCharacter::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CCharacter* CCharacter::Clone()
{
	return new CCharacter(*this);
}

void CCharacter::HitCheck()
{
	m_HitCount ++;
}

void CCharacter::SkillEnd(std::string SkillName)
{
	
}
