#pragma once
#include "BackGround.h"

class ScreenFX :
    public CBackGround
{
	friend class CScene;

protected:
	ScreenFX();
	ScreenFX(const ScreenFX& obj);
	virtual ~ScreenFX();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual ScreenFX* Clone();
};

