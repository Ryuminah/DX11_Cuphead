#pragma once
#include "../Skill/Tail.h"


class CMeteor :
    public CSkill
{
	friend class CScene;

public:
	static Vector3 StartPosition;
	static Direction LastDirection;
	static bool	bIsDouble;

protected:
	CMeteor();
	CMeteor(const CMeteor& obj);
	virtual ~CMeteor();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider;
	CSharedPtr<CSceneComponent>	m_Rotation;
	class CAnimation2D* m_Animation;

private:
	float	m_SmokeTime;			// 연기 생성 간격
	float	m_MaxY;
	float	m_MinY;
	Direction m_CurrentDirection;

	// x축이동
	Vector3 m_FirstPosition;

	// Y축 이동
	float	m_TimeToFrame;
	float	m_MoveY;
	float	m_Frame;
	float	m_MoveTime;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMeteor* Clone();

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);	// 스킬이 활성화 되었을때 어떤 동작을 해야하는지
	virtual void SkillEnd(float DeltaTime);	// 스킬이 활성화 되었을때 어떤 동작을 해야하는지
};

