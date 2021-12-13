#pragma once
#include "GameObject.h"
#include "Component/ColliderBox2D.h"

// ���� ������ �ݸ����� ���ƴ϶� ���������� ü�� �÷��̾� ��Ʈüũ ++
class CGroundCollider :
    public CGameObject
{
	friend class CScene;

protected:
	CGroundCollider();
	CGroundCollider(const CGroundCollider& obj);
	virtual ~CGroundCollider();

private:
	CSharedPtr<CColliderBox2D>	m_TestCollider;
	bool m_bIsTutorialScene;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGroundCollider* Clone();

public:
	void SetIsTutorialScene(bool IsTutorial)
	{
		m_bIsTutorialScene = IsTutorial;
	}
};

