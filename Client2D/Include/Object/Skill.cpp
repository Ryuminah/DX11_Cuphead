#include "Skill.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/DragonAnimation.h"
#include "Engine.h"
#include "Character.h"

int CSkill::RepeatCount = 1;

CSkill::CSkill() : m_bIsActive(false), m_PhaseNumber(Phase::Phase1),
	m_CoolTime(0.f), m_bIsStarted(false),
	m_pSkillOwner(nullptr)
{

}

CSkill::CSkill(const CSkill& obj) : CGameObject(obj)
{

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

	if (m_bIsActive)
	{
		// 아직 시작하지 않았다면 시작 함수 호출
		if (!m_bIsStarted)
		{
			SkillStart(DeltaTime);
		}

		SkillActive(DeltaTime);

		// 화면 밖을 나갔다면 스킬 종료
		Vector2 Out = { -100.f, -900.f };
		if (GetRelativePos().x < Out.x || GetRelativePos().y < Out.y)
		{
			SkillEnd(DeltaTime);
		}
	}

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

void CSkill::ResetSkillInfo()
{
	m_bIsActive = false;
	m_CoolTime = 0.f;
}


// Override
void CSkill::SkillStart(float DeltaTime)
{
}

void CSkill::SkillActive(float DeltaTime)
{

}

void CSkill::SkillEnd(float DeltaTime)
{
	// 현재 위치가 화면을 넘어간다면 삭제.
	m_pSkillOwner->SkillEnd(GetName());
	Active(false);
	
}








