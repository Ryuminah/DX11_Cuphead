#pragma once
#include "BackGround.h"
#include "Component/ColliderBox2D.h"


class CElderKettle :
    public CBackGround
{
	friend class CScene;

public:
	static bool IsTutorialOpen;
private:
	CSharedPtr<CColliderBox2D> m_DialogCollider;
	CSharedPtr<CColliderBox2D> m_TutorialCollider;

	CSharedPtr<CSpriteComponent> m_Sign;
	class CAnimation2D* m_SignAnim;
	class CSpeechBubble* m_SpeechBubble;

private:
	bool m_bCanDialogStart;
	bool m_bCanTutorialStart;
	bool m_bIsDialog;				// 플레이어와 충돌중일때만 활성화
	bool m_bIsTutorial;				// 플레이어와 충돌중일때만 활성화

	int m_DialogCount;

protected:
	CElderKettle();
	CElderKettle(const CElderKettle& obj);
	virtual ~CElderKettle();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CElderKettle* Clone();

public:
	void EventCollisionBegin(const HitResult& result, CCollider* Collider);
	void EventCollisionOverlap(const HitResult& result, CCollider* Collider);
	void EventCollisionEnd(const HitResult& result, CCollider* Collider);
	void AnimEnd(const std::string& Name);

public:
	void CreateSpeechBubble();
	void Interaction(float DeltaTime);
	void DialogCheck();
};

