#pragma once
#include "GameObject.h"

// 이펙트 클래스
class CEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CEffect();
	CEffect(const CEffect& obj);
	virtual ~CEffect();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEffect* Clone();
};

