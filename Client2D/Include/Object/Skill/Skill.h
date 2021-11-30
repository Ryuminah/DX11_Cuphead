#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

enum class Phase
{
	Phase1, Phase2, Phase3
};


// ������ ����� ���ϵ��� ����� ����
class CSkill :
    public CGameObject
{
protected:
	CSkill();
	CSkill(const CSkill& obj);
	virtual ~CSkill();

protected:
	static int RepeatCount;		// ������� ��� �ݺ��ߴ���
	static int TotalRepeatNumber;	// �� ��� �ݺ��Ҳ���


protected:
	class CCharacter* m_pSkillOwner;

protected:
	//std::string	m_SkillName;
	bool	m_bIsStarted;		// ������ ���� �ִ���
	bool	m_bIsActive;		// ���� Ȱ��ȭ ���� ��ų����
	bool	m_bIsEnd;			// ���� �������ϴ���

	float	m_CoolTime;			// �� �ʵڿ� �ٽ� ��� ��������
	Phase	m_PhaseNumber;		// �� ����� ����ϴ� ��ų����

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

	void SetTotalRepeatNumber(int repeatNumber)
	{
		TotalRepeatNumber = repeatNumber;
	}

	void SetbIsEnd(bool IsEnd)
	{
		m_bIsEnd = IsEnd;
	}

	static void AddRepeatCount()
	{
		++RepeatCount;
	}
	
	static bool IsRepeatEnd()
	{
		return RepeatCount == TotalRepeatNumber;
	}

	static void ResetRepeatInfo()
	{
		RepeatCount = 0;
		TotalRepeatNumber = 0;
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

