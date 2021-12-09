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
	// 배경에 필요한 모든 이미지, 애니메이션을 자식 컴포넌트로 가지고 있는다.
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

