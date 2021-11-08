#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"

class CDragonMap :
    public CGameObject
{
	friend class CScene;

protected:
	CDragonMap();
	CDragonMap(const CDragonMap& obj);
	virtual ~CDragonMap();

protected:
	CSharedPtr<CSpriteComponent> m_BackGround;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDragonMap* Clone();
};

