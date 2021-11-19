#pragma once
#include "GameObject.h"
#include "Component/ColliderBox2D.h"

// 보스가 사용할 패턴들
class CSkill :
    public CGameObject
{
protected:
	CSkill();
	CSkill(const CSkill& obj);
	virtual ~CSkill();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSceneComponent>	m_Rotation;
	CSharedPtr<CColliderBox2D> m_Collider;
	class CAnimation2D* m_Animation;

private:
	bool	m_bIsFired;			// 이미 나간 패턴인지
	int		m_PhaseNumber;		// 현재 페이즈에 해당하는지

public:
	bool GetIsFired()
	{
		return m_bIsFired;
	}

	int GetPhaseNumber()
	{
		return m_PhaseNumber;
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

