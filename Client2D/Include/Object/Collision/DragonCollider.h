#pragma once
#include "GameObject.h"
#include "Component/ColliderBox2D.h"

// 용 콜리전
class CDragonCollider :
    public CGameObject
{
	friend class CDragon;
	friend class CScene;

protected:
	CDragonCollider();
	CDragonCollider(const CDragonCollider& obj);
	virtual ~CDragonCollider();

private:
	class CDragon* m_pDragon;
	CSharedPtr<CColliderBox2D>	m_Collider;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDragonCollider* Clone();

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
};


