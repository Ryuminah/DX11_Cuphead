#pragma once
#include "Character.h"
#include "Skill.h"

enum PHASE1 {PEASHOT, METEOR, TAIL};

struct SkillData
{
	std::string	SkillName;	
	bool	IsActive;

	SkillData(std::string _skillName)
	{
		SkillName = _skillName;
		IsActive = false;
	}
};

class CDragon :
    public CCharacter
{
	friend class CScene;

protected:
	CDragon();
	CDragon(const CDragon& obj);
	virtual ~CDragon();

private:
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_GunPoint;		// �ѱ�
	std::vector<SkillData>		m_vecSkill;

private:
	Phase	m_CurrentPhase;
	int		m_NextPattern;			// ���� ������ �̱�� ����
	float	m_NextAttackTime;
	float	m_TailTime;				// ������ �ֱ������� ����

	std::string	m_LastSkillName;	// ���� ���������� ����� ��ų


private:
	// basic Movement


private:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDragon* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimFrameEnd(const std::string& Name);

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);

public:
	void PhaseOne();
	void Peashot();
	void Meteor();
	void Tail();

	void AttackEnd();


	void ChangeSkill();
	void SelectNextSkill();

	virtual void SkillEnd(std::string SkillName);
	void TimeCheck(float DeltaTime);

};

