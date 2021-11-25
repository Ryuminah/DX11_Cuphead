#pragma once
#include "../Skill/Tail.h"

// 눈깔빔
class CPeashot :
    public CSkill
{
	friend class CScene;

private:
	static float	RingAngle;
	static int		AllRingCount;


protected:
	CPeashot();
	CPeashot(const CPeashot& obj);
	virtual ~CPeashot();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider;
	CSharedPtr<CSceneComponent>	m_Rotation;
	class CAnimation2D* m_Animation;

private:
	float	m_RingSpeed;
	float	m_TimeInterval;			// 링 사이의 간격
	int		m_Number;				// 링 번호
	bool	m_bIsHead;
	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPeashot* Clone();

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);	// 스킬이 활성화 되었을때 어떤 동작을 해야하는지
	virtual void SkillEnd(float DeltaTime);	// 스킬이 활성화 되었을때 어떤 동작을 해야하는지



public:
	void SetIsHead(bool IsHead);
	void CreateChildRing();
	static void SetAllRingCount(int _allRingCount);

};

