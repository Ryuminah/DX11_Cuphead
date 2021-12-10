#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

// 전투를 하는 유닛에게 필요한 데이터와 기능을 제공 및 관리 클래스

class CCharacter :
    public CGameObject
{
	friend class CScene;

protected:
	CCharacter();
	CCharacter(const CCharacter& obj);
	virtual ~CCharacter();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider;
	class CAnimation2D* m_Animation;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCharacter* Clone();

protected:
	int		m_HitCount;			// 모든 캐릭터들은 체력 대신 타수로 계산함
	float	m_Speed;		
	bool	m_bCanAttack;		// 공격할 수 있는지
	bool	m_bCanMove;			// 움직일 수 있는 상황인지
	bool	m_bCanDamaged;		// 데미지를 입는 상태인지

	bool	m_bIsAttack;
	bool	m_bIsMove;
	bool	m_bIsInvincible;		// 현재 무적 상태인지


public:
	virtual void Hit();
	virtual void HitEnd();
	virtual void SkillEnd(std::string SkillName);

public:
	virtual void Invincible();
	virtual void InvincibleEnd();
};

