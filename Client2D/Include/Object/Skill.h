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
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSceneComponent>	m_Rotation;
	CSharedPtr<CColliderBox2D> m_Collider;
	class CAnimation2D* m_Animation;

protected:
	bool	m_bIsFired;			// 이미 나간 패턴인지
	float	m_CoolTime;			// 몇 초뒤에 다시 사용 가능한지
	Phase	m_PhaseNumber;		// 현재 페이즈에 해당하는지

public:
	bool GetIsFired()
	{
		return m_bIsFired;
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
	void SetIsFired(bool _isFired)
	{
		m_bIsFired = _isFired;
	}

	void SetCoolTime(float _coolTime)
	{
		m_bIsFired = _coolTime;
	}

	void SetPhaseNumber(Phase _phaseNumber)
	{
		m_PhaseNumber = _phaseNumber;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSkill* Clone();

};

