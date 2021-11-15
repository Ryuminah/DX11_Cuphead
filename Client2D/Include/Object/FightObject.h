#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"


// ������ �ϴ� ���ֿ��� �ʿ��� �����Ϳ� ����� ���� �� ���� Ŭ����

class CFightObject :
    public CGameObject
{
	friend class CScene;

protected:
	CFightObject();
	CFightObject(const CFightObject& obj);
	virtual ~CFightObject();

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
	virtual CFightObject* Clone();

protected:
	int m_HP;
	int m_Attack;

	// ���߿� ������ �������� ����
	float m_Speed;
	bool m_bCanAttack;	// ����������
	bool m_bCanMove;	// ������ �� �ִ� ��Ȳ����



public:
	// ������ �ʿ��� �Լ�

};

