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
	CSharedPtr<CSpriteComponent> m_GunPoint;		// 총구
	class CDragonCollider*		m_pDragonCollider;
	class CSkill* m_CurrentSkill;
	std::vector<SkillData>		m_vecSkill;
	std::string	  m_CurrentSkillName;

	class CAnimation2D* m_GunPointAnim;

private:
	Phase	m_CurrentPhase;
	int		m_NextPattern;			// 다음 패턴을 뽑기로 정함
	float	m_NextAttackTime;
	float	m_TailTime;				// 꼬리는 주기적으로 나옴

	std::string	m_LastPattern;	// 가장 마지막으로 사용한 스킬
	bool	m_IsAnimEnd;

private:
	bool	m_bIsPhaseStart;
	//bool	m_bIsPhaseEnd;



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
	void GunPointAnimEnd(const std::string& Name);
	void ChangeAnimation(const std::string& Name);
	std::string GetCurrentSequenceName();
	bool GetIsFrameEnd();

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
	void CreateDragonCollider();

public:
	int MakeRandomNumber();
	void PhaseOne();
	void PhaseEnd();

	void SetPhaseTwoOpening();
	void PhaseTwo(float DeltaTime);
	void Peashot();
	void Meteor();
	void Tail();

	void FireBoy();

	void AttackEnd();


	void ChangeSkill();
	void SelectNextSkill();

	virtual void SkillEnd(std::string SkillName);
	void TimeCheck(float DeltaTime);
	void PhaseEndCheck(float DeltaTime);

};

