#pragma once
#include "BackGround.h"

class FG_Loading :
    public CBackGround
{
	friend class CScene;

private:
	FG_Loading();
	FG_Loading(const FG_Loading& obj);
	virtual ~FG_Loading();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual FG_Loading* Clone();
};

