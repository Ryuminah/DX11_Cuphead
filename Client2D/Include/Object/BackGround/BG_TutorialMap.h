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
	CSharedPtr<CColliderBox2D>	m_DescendWall;
	CSharedPtr<CColliderBox2D>	m_DescendCylinder;
	CSharedPtr<CColliderBox2D>	m_ParryBox;
	CSharedPtr<CColliderBox2D>	m_ParryCylinder;
	CSharedPtr<CColliderBox2D>	m_Lock;

	// Interaction
	CSharedPtr<CColliderBox2D>	m_Pyramid;			// Attack
	CSharedPtr<CColliderBox2D>	m_ParryOne;
	CSharedPtr<CColliderBox2D>	m_ParryTwo;
	CSharedPtr<CColliderBox2D>	m_ParryThree;
	CSharedPtr<CColliderBox2D>	m_Exit;				// Skill과 같은 상호작용

	// Other Sprite
	CSharedPtr<CSpriteComponent>	m_spritePyramidHead;
	CSharedPtr<CSpriteComponent>	m_spritePyramidBody;
	class CAnimation2D* m_PyramidHeadAnim;
	class CAnimation2D* m_PyramidBodyAnim;

	CSharedPtr<CSpriteComponent>	m_spriteParryOne;
	CSharedPtr<CSpriteComponent>	m_spriteParryTwo;
	CSharedPtr<CSpriteComponent>	m_spriteParryThree;
	class CAnimation2D* m_ParryOneAnim;
	class CAnimation2D* m_ParryTwoAnim;
	class CAnimation2D* m_ParryThreeAnim;


private:
	int m_PyramidHitCount;
	int m_ParryNumber;					// 현재 활성화 된 패링
	int m_ParrySuccessNumber;

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
	void PyramidDestroyCheck();
	void ParryCheck();
	void ParryModeOn(CColliderBox2D* parryCollision, CSpriteComponent* parrySprite, CAnimation2D* parryAnim);


public:
	void CreateCollision();
	void CreateParry();

public:
	void Pyramid_CollisionBegin(const HitResult& result, CCollider* Collider);
	void Parry_CollisionOverlap(const HitResult& result, CCollider* Collider);

	
};

