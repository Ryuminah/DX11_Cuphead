#pragma once
#include "Character.h"
#include "Skill.h"

class CDragon :
    public CCharacter
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


private:



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

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
};

