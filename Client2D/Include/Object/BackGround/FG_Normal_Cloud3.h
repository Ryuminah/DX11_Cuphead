#pragma once
#include "BackGround.h"

class FG_Normal_Cloud3 :
    public CBackGround
{
	friend class CScene;

protected:
	FG_Normal_Cloud3();
	FG_Normal_Cloud3(const FG_Normal_Cloud3& obj);
	virtual ~FG_Normal_Cloud3();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual FG_Normal_Cloud3* Clone();
};

