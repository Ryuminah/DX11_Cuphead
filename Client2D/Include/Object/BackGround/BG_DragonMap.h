#pragma once
#include "GameObject.h"
#include "BackGround.h"
#include "Component/SpriteComponent.h"

class BG_CDragonMap :
    public CBackGround
{
	friend class CScene;

public:
	static bool bIsNight;

protected:
	BG_CDragonMap();
	BG_CDragonMap(const BG_CDragonMap& obj);
	virtual ~BG_CDragonMap();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_CDragonMap* Clone();
};

