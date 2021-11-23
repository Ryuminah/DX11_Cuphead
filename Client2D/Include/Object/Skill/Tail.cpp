#include "Tail.h"
#include "../Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Dragon.h"


CTail::CTail() : m_WaitTime(2.f), m_MaxY(500.f), m_TailSpeed(800.f)
{

}

CTail::CTail(const CTail& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Rotation = FindSceneComponent("Rotation");
}

CTail ::~CTail()
{

}

void CTail::Start()
{
	CSkill::Start();
	SetRelativePos({ CMugman::PlayerPos.x ,-750.f, 0.f });
}

bool CTail::Init()
{
	CSkill::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Peashot");
	m_Collider = CreateSceneComponent<CColliderBox2D>("PeashotCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(300.f, 870.f, 1.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);


	m_Collider->SetExtent(100.f, 300.f);
	m_Collider->SetCollisionProfile("Enemy");
	m_Collider->SetColliderType(Collider_Type::Trigger);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_Tail");

	//m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimationFrameEnd);

	SetUseBlockMovement(false);
	SetDefaultZ(0.1f);
	return true;
}

void CTail::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);
}

void CTail::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CTail::Collision(float DeltaTime)
{
	CSkill::Collision(DeltaTime);
}

void CTail::Render(float DeltaTime)
{
	CSkill::Render(DeltaTime);
}

CTail* CTail::Clone()
{
	return new CTail(*this);
}


void CTail::SkillStart(float DeltaTime)
{
	// 플레이어의 X값을 가져온다
	SetRelativePos({ CMugman::PlayerPos.x ,-400.f, 0.f});
	SetUseForceRender(true);
	m_bIsStarted = true;
}

void CTail::SkillActive(float DeltaTime)
{
	// 아직 활성화 되지 않았다면 시간을 깎는다
	if (m_WaitTime > 0.f)
	{
		m_WaitTime -= DeltaTime;

		if (m_WaitTime < 0.f)
		{
			m_WaitTime = 0.f;
		}

		return;
	}

	if (GetRelativePos().y >= m_MaxY)
	{
		m_TailSpeed = -300.f;
		AddRelativePos(GetAxis(AXIS_Y) * m_TailSpeed * DeltaTime);
	}
	
	AddRelativePos(GetAxis(AXIS_Y) * m_TailSpeed * DeltaTime);
}



