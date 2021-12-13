#pragma once
#include "BackGround.h"

class BG_TutorialMap :
    public CBackGround
{
	friend class CScene;

private:
	float m_Speed;

protected:
	BG_TutorialMap();
	BG_TutorialMap(const BG_TutorialMap& obj);
	virtual ~BG_TutorialMap();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_TutorialMap* Clone();
};

