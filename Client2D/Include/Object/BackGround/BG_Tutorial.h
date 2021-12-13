#pragma once
#include "BackGround.h"

class BG_Tutorial :
    public CBackGround
{
	friend class CScene;

protected:
	BG_Tutorial();
	BG_Tutorial(const BG_Tutorial& obj);
	virtual ~BG_Tutorial();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_Tutorial* Clone();
};

