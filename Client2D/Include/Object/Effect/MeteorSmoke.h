#pragma once
#include "Effect.h"

class CMeteorSmoke :
    public CEffect
{
	friend class CScene;

private:
	CMeteorSmoke();
	CMeteorSmoke(const CMeteorSmoke& obj);
	virtual ~CMeteorSmoke();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMeteorSmoke* Clone();

public:
	void AnimEnd(const std::string& Name);
};

