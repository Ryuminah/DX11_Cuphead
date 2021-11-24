#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"

class FG_Cloud :
    public CGameObject
{
	friend class CScene;

protected:
	FG_Cloud();
	FG_Cloud(const FG_Cloud& obj);
	virtual ~FG_Cloud();

protected:
	CSharedPtr<CSpriteComponent> m_BackGround;
	class CAnimation2D* m_AnimImage;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual FG_Cloud* Clone();
};

