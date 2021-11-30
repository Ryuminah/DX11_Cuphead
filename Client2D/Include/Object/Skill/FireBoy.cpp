#include "FireBoy.h"
#include <time.h>
#include "../Character/Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Character/Dragon.h"
#include "../Effect/MeteorSmoke.h"

CFireBoy::CFireBoy() :
	m_Speed(600.f),
	m_JumpPower(130.f),m_JumpAccel(50.f),m_JumpTime(0.f),
	m_bIsJump(false),m_bIsAttackUnit(true),m_bIsAttack(false),
	m_JumpCastCount(0), m_JumpDirection(Direction::RIGHT)
{

}

CFireBoy::CFireBoy(const CFireBoy& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("FireBoy");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FireBoyCollider");
	m_Rotation = FindSceneComponent("Rotation");
}

CFireBoy ::~CFireBoy()
{

}

void CFireBoy::Start()
{
	CSkill::Start();
}

bool CFireBoy::Init()
{
	CSkill::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("FireBoy");
	m_Collider = CreateSceneComponent<CColliderBox2D>("FireBoyCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);

	m_Collider->SetExtent(50.f, 50.f);
	m_Collider->SetCollisionProfile("Skill");
	m_Collider->SetColliderType(Collider_Type::Static);

	//m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_Meteor");

	//m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);


	//m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimationFrameEnd);

	SetUseBlockMovement(false);
	SetPhysicsSimulate(false);
	SetDefaultZ(0.1f);

	return true;
}

void CFireBoy::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	MoveCheck(DeltaTime);
	JumpCheck(DeltaTime);
	TimeCheck(DeltaTime);
}

void CFireBoy::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CFireBoy::Collision(float DeltaTime)
{
	CSkill::Collision(DeltaTime);
}

void CFireBoy::Render(float DeltaTime)
{
	CSkill::Render(DeltaTime);
}

CFireBoy* CFireBoy::Clone()
{
	return new CFireBoy(*this);
}


void CFireBoy::SkillStart(float DeltaTime)
{
	srand((unsigned int)time(NULL));

	if (m_bIsAttackUnit)
	{
		m_Sprite->GetMaterial(0)->SetBaseColor(0.5f, 0.f, 0.1f, 0.2f);
		m_CoolTime = 2.f;
	}
	m_bIsStarted = true;

}

void CFireBoy::SkillActive(float DeltaTime)
{

	// 화면 밖을 나갔다면 종료 종료 
	Vector2 DefaultOut = { -200.f, -200.f };

	if (GetRelativePos().x <= DefaultOut.x || GetRelativePos().y <= DefaultOut.y)
	{
		m_bIsEnd = true;
	}
}

void CFireBoy::SkillEnd(float DeltaTime)
{
	m_bIsAttack = false;
	m_bIsJump = false;
	SetPhysicsSimulate(false);
}

void CFireBoy::MoveCheck(float DeltaTime)
{
	if (m_bIsAttack)
	{
		return;
	}

	if (GetRelativePos().x >= 700.f)
	{
		m_bIsAttack= true;

		if (CMugman::PlayerPos.x >= GetWorldPos().x)
		{
			m_JumpDirection = Direction::RIGHT;
		}

		else
		{
			m_JumpDirection = Direction::LEFT;
		}
	}

	else
	{
		AddRelativePos(GetAxis(AXIS_X) * m_Speed * DeltaTime);
	}
}

void CFireBoy::JumpCheck(float DeltaTime)
{
	// 점프중 일 경우 점프를 적용
	if (m_bIsJump)
	{
		m_JumpTime += GetGravityAccel() * 0.4f * DeltaTime;

		// 처음 뛸 경우 힘을 강하게 적용함.
	/*	if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}*/

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpPower) + (m_JumpAccel * m_JumpTime);
		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)*DeltaTime);

		m_JumpAccel -= GetGravityAccel() * 0.4f * DeltaTime;

		// 플레이어가 나보다 더 오른쪽에 있을 경우
		if (m_JumpDirection == Direction::RIGHT)
		{
			AddRelativePos(GetAxis(AXIS_X) * 350.f * DeltaTime);
		}

		else
		{
			AddRelativePos(GetAxis(AXIS_X) * -350.f * DeltaTime);

		}
	}

	
}

void CFireBoy::TimeCheck(float DeltaTime)
{
	// 공격하는 유닛만 쿨타임을 체크한다.
	if (!m_bIsAttackUnit)
	{
		return;
	}

	// 공격중이지만 아직 점프하지 않았다면
	if (m_bIsAttack && !m_bIsJump)
	{
		m_CoolTime -= DeltaTime;
	}

	if (m_CoolTime <0.f)
	{
		m_bIsJump = true;
		m_CoolTime = 0.f;
		SetPhysicsSimulate(true);
		//m_Animation->ChangeAnimation("FireBoy_Attack");
	}
}


