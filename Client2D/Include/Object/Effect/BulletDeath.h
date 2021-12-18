#pragma once
#include "Effect.h"

class CBulletDeath :
    public CEffect
{
	friend class CScene;

private:
	CBulletDeath();
	CBulletDeath(const CBulletDeath& obj);
	virtual ~CBulletDeath();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBulletDeath* Clone();

public:
	void AnimEnd(const std::string& Name);
};

