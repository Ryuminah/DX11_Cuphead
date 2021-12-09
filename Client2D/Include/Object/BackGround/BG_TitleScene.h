#pragma once
#include "BackGround.h"

class BG_TitleScene :
    public CBackGround
{
	friend class CScene;

protected:
	BG_TitleScene();
	BG_TitleScene(const BG_TitleScene& obj);
	virtual ~BG_TitleScene();

private:
	// ��濡 �ʿ��� ��� �̹���, �ִϸ��̼��� �ڽ� ������Ʈ�� ������ �ִ´�.
	CSharedPtr<CSpriteComponent> m_CupheadSprite;
	class CAnimation2D* m_CupheadAnim;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual BG_TitleScene* Clone();
};

