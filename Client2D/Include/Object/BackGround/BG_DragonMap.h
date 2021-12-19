#pragma once
#include "GameObject.h"
#include "BackGround.h"
#include "Component/SpriteComponent.h"

class BG_DragonMap :
    public CBackGround
{
	friend class CScene;

public:
	static bool bIsEnd;

protected:
	BG_DragonMap();
	BG_DragonMap(const BG_DragonMap& obj);
	virtual ~BG_DragonMap();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_DragonMap* Clone();

public:
	void AnimFrameEnd(const std::string& Name);
};

