#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CBullet();
    CBullet(const CBullet& obj);
    virtual ~CBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Collider;
    class CAnimation2D* m_Animation;
    float       m_Range;     // ���� �Ÿ�
    bool        m_bIsFire;      // �߻� �ƴ���
    bool        m_bIsHit;        // ��� �¾Ҵ���
    float       m_Speed;

public:
    void SetRange(float Range)
    {
        m_Range = Range;
    }

    void SetCollisionProfile(const std::string& Name)
    {
        m_Collider->SetCollisionProfile(Name);
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
    void AnimationFrameEnd(const std::string& Name);
};

