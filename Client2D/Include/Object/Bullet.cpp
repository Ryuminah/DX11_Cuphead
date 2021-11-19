#include "Bullet.h"
#include "Scene/Scene.h"
#include "../Animation2D/BulletAnimation.h"

CBullet::CBullet() :
    m_Range(1280.f), m_Speed(900.f)
{
    m_bIsFire = false;
    m_bIsHit = false;
}

CBullet::CBullet(const CBullet& obj) :
    CGameObject(obj)
{
    m_Collider = (CColliderBox2D*)FindSceneComponent("BulletCollider");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
    m_bIsFire = false;
    m_bIsHit = false;
}

CBullet::~CBullet()
{
}

void CBullet::Start()
{
    CGameObject::Start();
    
    // 처음 셋팅한 방향대로만 이동
    if (m_BulletDirection== Direction::RIGHT)
    {
        m_Animation->ChangeAnimation("Bullet_Loop_R");
    }

    if (m_BulletDirection == Direction::LEFT)
    {
        m_Animation->ChangeAnimation("Bullet_Loop_L");
    }

    SetPrevWorldPos(GetPrevWorldPos());
}

bool CBullet::Init()
{
    CGameObject::Init();

    m_Collider = CreateSceneComponent<CColliderBox2D>("BulletCollider");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite->CreateAnimation2D<CBulletAnimation>();
    m_Animation = m_Sprite->GetAnimation2D();

    SetRootComponent(m_Sprite);

    m_Sprite->SetRelativeScale(700.f, 700.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    //m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 0.01f);

    m_Collider->SetExtent(30,10);
    m_Collider->SetPivot(0.5f, 0.5f, 0.5f);

    m_Collider->SetColliderType(Collider_Type::Static);
    m_Collider->SetCollisionProfile("Bullet");

    m_Sprite->AddChild(m_Collider);

    m_Collider->AddCollisionCallbackFunction<CBullet>(Collision_State::Begin, this,
        &CBullet::CollisionBegin);

    m_Animation->SetFrameEndFunction<CBullet>(this, &CBullet::AnimationFrameEnd);

    SetUseBlockMovement(false);
    SetPhysicsSimulate(false);
    SetDefaultZ(0.1f);
    m_bIsFire = true;
    
    return true;
}

void CBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (m_bIsFire)
    {
        float Distance = m_Speed * DeltaTime;

        if (m_BulletDirection == Direction::RIGHT)
        {
            AddRelativePos(GetAxis(AXIS_X) * Distance);
        }
        
        if (m_BulletDirection == Direction::LEFT)
        {
            AddRelativePos(GetAxis(AXIS_X) * -Distance);
        }

        m_Range -= abs(Distance);

        if (GetWorldPos().x < GetPrevWorldPos().x)
        {
            int a = 0;
        }

        // 사정거리를 벗어나면
        if (m_Range <= 0.f)
        {
            Active(false);
            m_bIsFire = false;
            m_bIsHit = false;
        }
    }
}

void CBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CBullet* CBullet::Clone()
{
    return new CBullet(*this);
}

void CBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    
    m_bIsHit = true;
}

void CBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
    Active(false);

    m_bIsHit = false;
    m_bIsFire = false;
}

void CBullet::AnimationFrameEnd(const std::string& Name)
{
 
}

void CBullet::SetBulletDirection(Direction FirstDirection)
{
    m_BulletDirection = FirstDirection;
}
