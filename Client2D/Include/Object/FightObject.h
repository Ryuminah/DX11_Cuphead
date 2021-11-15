#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"


// 전투를 하는 유닛에게 필요한 데이터와 기능을 제공 및 관리 클래스

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

	// 나중에 움직임 전용으로 빼기
	float m_Speed;
	bool m_bCanAttack;	// 공격중인지
	bool m_bCanMove;	// 움직일 수 있는 상황인지



public:
	// 전투에 필요한 함수

};

