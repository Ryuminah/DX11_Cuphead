#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CStepCloud :
    public CGameObject
{
	friend class CScene;

public:
	static bool	m_bIsStageStart;

public:
	// 가장 마지막으로 생성된 메테오가 위였는지 아래였는지.
	static Direction LastDirection;

protected:
	CStepCloud();
	CStepCloud(const CStepCloud& obj);
	virtual ~CStepCloud();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D>	m_Collider;

	class CAnimation2D*			m_Animation;

private:
	// Move
	float m_MoveTime;
	float m_MoveDistance;
	Vector3 m_FirstPosition;
	

	bool	m_bIsPlayerOn;

public:
	float GetMoveDistance();

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
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);


};

