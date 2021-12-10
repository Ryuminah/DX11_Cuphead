#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

// ������ �ϴ� ���ֿ��� �ʿ��� �����Ϳ� ����� ���� �� ���� Ŭ����

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
	int		m_HitCount;			// ��� ĳ���͵��� ü�� ��� Ÿ���� �����
	float	m_Speed;		
	bool	m_bCanAttack;		// ������ �� �ִ���
	bool	m_bCanMove;			// ������ �� �ִ� ��Ȳ����
	bool	m_bCanDamaged;		// �������� �Դ� ��������

	bool	m_bIsAttack;
	bool	m_bIsMove;
	bool	m_bIsInvincible;		// ���� ���� ��������


public:
	virtual void Hit();
	virtual void HitEnd();
	virtual void SkillEnd(std::string SkillName);

public:
	virtual void Invincible();
	virtual void InvincibleEnd();
};

