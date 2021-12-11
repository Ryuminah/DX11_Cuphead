#pragma once
#include "BackGround.h"

// FG���� ���� ���
class BG_KettleHouse :
    public CBackGround
{
	friend class CScene;

protected:
	BG_KettleHouse();
	BG_KettleHouse(const BG_KettleHouse& obj);
	virtual ~BG_KettleHouse();

private:
	// ��濡 �ʿ��� ��� �̹���, �ִϸ��̼��� �ڽ� ������Ʈ�� ������ �ִ´�.
	CSharedPtr<CSpriteComponent> m_FG_KettleHouse;
	class CAnimation2D* m_FG_KettleHouseImage;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_KettleHouse* Clone();
};

