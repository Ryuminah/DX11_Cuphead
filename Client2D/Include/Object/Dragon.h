#pragma once
#include "FightObject.h"

enum class Phase
{
	Phase1, Phase2, Phase3
};

class CDragon :
    public CFightObject
{
	friend class CScene;

protected:
	CDragon();
	CDragon(const CDragon& obj);
	virtual ~CDragon();

private:
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_Muzzle;

private:
	Phase	m_CurrentPhase;

private:
	// basic Movement
	bool m_bIsFall;

private:
	// Shooting
	float	m_ShootCool;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDragon* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:


public:
	void AnimationFrameEnd(const std::string& Name);

public: //Get Set

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
};

