#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

enum class Phase
{
	Phase1, Phase2, Phase3
};


// 보스가 사용할 패턴들의 기반을 제공
class CSkill :
    public CGameObject
{
protected:
	CSkill();
	CSkill(const CSkill& obj);
	virtual ~CSkill();

protected:
	static int RepeatCount;		// 반복 횟수

protected:
	class CCharacter* m_pSkillOwner;

protected:
	//std::string	m_SkillName;
	bool	m_bIsStarted;		// 시작한 적이 있는지
	bool	m_bIsActive;		// 현재 활성화 중인 스킬인지
	float	m_CoolTime;			// 몇 초뒤에 다시 사용 가능한지
	Phase	m_PhaseNumber;		// 몇 페이즈에 사용하는 스킬인지

public:
	bool GetIsFired()
	{
		return m_bIsActive;
	}

	float GetCoolTime()
	{
		return m_CoolTime;
	}

	Phase GetPhaseNumber()
	{
		return m_PhaseNumber;
	}

public:
	void SetIsActive(bool IsActive)
	{
		m_bIsActive = IsActive;
	}

	void SetCoolTime(float _coolTime)
	{
		m_bIsActive = _coolTime;
	}

	void SetPhaseNumber(Phase _phaseNumber)
	{
		m_PhaseNumber = _phaseNumber;
	}

	void SetSkillInfo(float CoolTime, Phase PhaseNumber)
	{
		m_CoolTime = CoolTime;
		m_PhaseNumber = PhaseNumber;
	}

	void SetSkillOwner(CCharacter* SkillOwner)
	{
		m_pSkillOwner = SkillOwner;
	}

	void SetRepeatCount(int repeatCount)
	{
		RepeatCount = repeatCount;
	}

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);
	virtual void SkillEnd(float DeltaTime);


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSkill* Clone();

public:
	void ResetSkillInfo();
};

