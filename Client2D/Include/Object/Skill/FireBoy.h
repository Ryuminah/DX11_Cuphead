#pragma once
#include "Skill.h"

class CFireBoy :
    public CSkill
{
	friend class CScene;

protected:
	CFireBoy();
	CFireBoy(const CFireBoy& obj);
	virtual ~CFireBoy();

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
	virtual CFireBoy* Clone();

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);	// ��ų�� Ȱ��ȭ �Ǿ����� � ������ �ؾ��ϴ���
	virtual void SkillEnd(float DeltaTime);	// ��ų�� ��Ȱ��ȭ �Ǿ����� � ������ �ؾ��ϴ���

public:
	void MoveCheck(float DeltaTime);
	void JumpCheck(float DeltaTime);
	void TimeCheck(float DeltaTime);
};

