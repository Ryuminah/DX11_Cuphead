#pragma once
#include "BackGround.h"

class FG_Tutorial :
    public CBackGround
{
	friend class CScene;

protected:
	FG_Tutorial();
	FG_Tutorial(const FG_Tutorial& obj);
	virtual ~FG_Tutorial();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual FG_Tutorial* Clone();
};

