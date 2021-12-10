#include "Character.h"

CCharacter::CCharacter() :m_HitCount(0), m_bIsAttack(false), m_bIsMove(false), m_bIsInvincible(false),
							m_Speed(550.f), m_bCanMove(true), m_bCanDamaged(true) ,m_bCanAttack(true)
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

void CCharacter::Hit()
{
	
}

void CCharacter::HitEnd()
{
}

void CCharacter::SkillEnd(std::string SkillName)
{
	
}

void CCharacter::Invincible()
{
	m_Sprite->GetMaterial(0)->SetBaseColor(0.99f, 0.99f, 0.99f, 0.5f);
	m_bCanDamaged = false;
	m_bIsInvincible = true;
}

void CCharacter::InvincibleEnd()
{
	m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_bCanDamaged = true;
	m_bIsInvincible = false;
}
