#pragma once
#include "BackGround.h"
#include "Component/ColliderBox2D.h"

class BG_TutorialMap :
    public CBackGround
{
	friend class CScene;

// �ʿ��� �浹�ؾ��� ��� �ݸ������� ���⼭ ���� �����Ѵ�.
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
	CSharedPtr<CColliderBox2D>	m_Exit;				// Skill�� ���� ��ȣ�ۿ�

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

