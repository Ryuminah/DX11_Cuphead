#include "Skill.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/DragonAnimation.h"
#include "Engine.h"

CSkill::CSkill() : m_bIsFired(false), m_PhaseNumber(1)
{

}

CSkill::CSkill(const CSkill& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CSkill::~CSkill()
{

}

void CSkill::Start()
{
	CGameObject::Start();
}

bool CSkill::Init()
{
	CGameObject::Init();

	return true;
}

void CSkill::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSkill::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSkill::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CSkill::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CSkill* CSkill::Clone()
{
	return new CSkill(*this);
}








