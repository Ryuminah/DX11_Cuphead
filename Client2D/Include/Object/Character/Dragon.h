#pragma once
#include "../Character/Character.h"
#include "../Skill/Skill.h"

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
	friend class CDragonCollider;

protected:
	CDragon();
	CDragon(const CDragon& obj);
	virtual ~CDragon();

private:
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_GunPoint;		// �ѱ�
	std::vector<SkillData>		m_vecSkill;
	class CDragonCollider*		m_pDragonCollider;
	class CSkill* m_CurrentSkill;

private:
	Phase	m_CurrentPhase;
	int		m_NextPattern;			// ���� ������ �̱�� ����
	float	m_NextAttackTime;
	float	m_TailTime;				// ������ �ֱ������� ����

	std::string	m_LastPattern;	// ���� ���������� ����� ��ų
	bool	m_IsAnimEnd;

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
	void ChangeAnimation(const std::string& Name);
	std::string GetCurrentSequenceName();
	bool GetIsFrameEnd();

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
	void CreateDragonCollider();

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

