#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"

class CBackGround :
    public CGameObject
{
	friend class CScene;

protected:
	CBackGround();
	CBackGround(const CBackGround& obj);
	virtual ~CBackGround();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_BackGroundImage;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBackGround* Clone();
};

