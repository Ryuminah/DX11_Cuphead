#pragma once
#include "Effect.h"

class CBulletSpawn :
    public CEffect
{
	friend class CScene;

private:
	CBulletSpawn();
	CBulletSpawn(const CBulletSpawn& obj);
	virtual ~CBulletSpawn();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBulletSpawn* Clone();

public:
	void AnimEnd(const std::string& Name);
};

