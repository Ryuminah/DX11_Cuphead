#pragma once
#include "GameObject.h"
#include "Component/ColliderBox2D.h"

// 낙사 방지용 콜리전이 ㄴ아니라 땅에닿으면 체력 플레이어 히트체크 ++
class CGroundCollider :
    public CGameObject
{
	friend class CScene;

protected:
	CGroundCollider();
	CGroundCollider(const CGroundCollider& obj);
	virtual ~CGroundCollider();

private:
	CSharedPtr<CColliderBox2D>	m_TestCollider;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGroundCollider* Clone();

public:

};

