#pragma once
#include "Effect.h"

class CDust :
    public CEffect
{
	friend class CScene;

private:
	CDust();
	CDust(const CDust& obj);
	virtual ~CDust();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDust* Clone();

public:
	void AnimEnd(const std::string& Name);
};

