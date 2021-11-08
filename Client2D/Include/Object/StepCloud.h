#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CStepCloud :
    public CGameObject
{
	friend class CScene;

protected:
	CStepCloud();
	CStepCloud(const CStepCloud& obj);
	virtual ~CStepCloud();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D>	m_Collider;
	CSharedPtr<CColliderBox2D>	m_TestCollider;

	class CAnimation2D*			m_Animation;

private: // Move


private:


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStepCloud* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);


public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
};
