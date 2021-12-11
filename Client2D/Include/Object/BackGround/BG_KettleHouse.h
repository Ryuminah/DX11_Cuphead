#pragma once
#include "BackGround.h"

// FG까지 전부 출력
class BG_KettleHouse :
    public CBackGround
{
	friend class CScene;

protected:
	BG_KettleHouse();
	BG_KettleHouse(const BG_KettleHouse& obj);
	virtual ~BG_KettleHouse();

private:
	// 배경에 필요한 모든 이미지, 애니메이션을 자식 컴포넌트로 가지고 있는다.
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

