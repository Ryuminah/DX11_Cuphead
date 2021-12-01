#pragma once
#include "Skill.h"

class CFireboy :
    public CSkill
{
	friend class CScene;

public:
	// 시간을 랜덤으로 설정한 후, 
	static float	AttackUnitCoolTime;			// 공격 유닛 생성주기

protected:
	CFireboy();
	CFireboy(const CFireboy& obj);
	virtual ~CFireboy();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider;
	CSharedPtr<CSceneComponent>	m_Rotation;
	class CAnimation2D* m_Animation;

private:
	bool	m_bIsAttackUnit;
	bool	m_bIsAttack;

	bool	m_bIsJump;

	float	m_JumpTime;
	float	m_JumpPower;
	float	m_JumpAccel;

	float	m_Speed;
	int		m_JumpCastCount;
	
	Direction m_JumpDirection;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CFireboy* Clone();

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);	// 스킬이 활성화 되었을때 어떤 동작을 해야하는지
	virtual void SkillEnd(float DeltaTime);	// 스킬이 비활성화 되었을때 어떤 동작을 해야하는지

public:
	void MoveCheck(float DeltaTime);
	void JumpCheck(float DeltaTime);
	void TimeCheck(float DeltaTime);

	void AnimFrameEnd(const std::string& Name);
	
public:
	void SetAttackUnit(bool isAttackUnit)
	{
		m_bIsAttackUnit = isAttackUnit;
	}
};

