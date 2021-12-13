#pragma once
#include "BackGround.h"
#include "Component/ColliderBox2D.h"

class BG_TutorialMap :
    public CBackGround
{
	friend class CScene;

// 맵에서 충돌해야할 모든 콜리전들을 여기서 전부 제작한다.
private:
	// Only Block
	CSharedPtr<CColliderBox2D>	m_Jump;
	CSharedPtr<CColliderBox2D>	m_Descend;
	CSharedPtr<CColliderBox2D>	m_ParryBox;
	CSharedPtr<CColliderBox2D>	m_ParryCylinder;
	CSharedPtr<CColliderBox2D>	m_Lock;

	// Interaction
	CSharedPtr<CColliderBox2D>	m_Pyramid;			// Attack
	CSharedPtr<CColliderBox2D>	m_ParryOne;
	CSharedPtr<CColliderBox2D>	m_ParryTwo;
	CSharedPtr<CColliderBox2D>	m_ParryThree;
	CSharedPtr<CColliderBox2D>	m_Exit;				// Skill과 같은 상호작용

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

public:
	void CreateCollision();
};

