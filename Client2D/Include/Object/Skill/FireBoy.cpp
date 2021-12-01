#include "FireBoy.h"
#include <time.h>
#include "../Character/Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Character/Dragon.h"
#include "../Effect/MeteorSmoke.h"

float CFireboy::AttackUnitCoolTime = 0.f;

CFireboy::CFireboy() :
	m_Speed(600.f),
	m_JumpPower(50.f),m_JumpAccel(50.f),m_JumpTime(0.f),
	m_bIsJump(false),m_bIsAttackUnit(false),m_bIsAttack(false),
	m_JumpCastCount(0), m_JumpDirection(Direction::RIGHT)
{

}

CFireboy::CFireboy(const CFireboy& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("Fireboy");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("FireBoyCollider");
	m_Rotation = FindSceneComponent("Rotation");
}

CFireboy ::~CFireboy()
{

}

void CFireboy::Start()
{
	CSkill::Start();
}

bool CFireboy::Init()
{
	CSkill::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Fireboy");
	m_Collider = CreateSceneComponent<CColliderBox2D>("FireBoyCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(110.f, 160.f, 1.f);
	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);

	m_Collider->SetExtent(50.f, 50.f);
	m_Collider->SetCollisionProfile("Skill");
	m_Collider->SetColliderType(Collider_Type::Static);

	//m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Fireboy_Idle");



	m_Animation->SetFrameEndFunction<CFireboy>(this, &CFireboy::AnimFrameEnd);

	SetUseBlockMovement(false);
	SetPhysicsSimulate(false);

	return true;
}

void CFireboy::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

}

void CFireboy::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CFireboy::Collision(float DeltaTime)
{
	CSkill::Collision(DeltaTime);
}

void CFireboy::Render(float DeltaTime)
{
	CSkill::Render(DeltaTime);
}

CFireboy* CFireboy::Clone()
{
	return new CFireboy(*this);
}


void CFireboy::SkillStart(float DeltaTime)
{
	srand((unsigned int)time(NULL));

	if (m_bIsAttackUnit)
	{
		m_Sprite->GetMaterial(0)->SetBaseColor(0.5f, 0.f, 0.1f, 0.2f);
		m_Sprite->SetDefaultZ(0.1f);
		m_CoolTime = 1.f;
	}

	m_bIsStarted = true;
}

void CFireboy::SkillActive(float DeltaTime)
{
	MoveCheck(DeltaTime);
	JumpCheck(DeltaTime);
	TimeCheck(DeltaTime);

	// ȭ�� ���� �����ٸ� ���� ���� 
	Vector2 DefaultOut = { -200.f, -200.f };

	if (GetRelativePos().x <= DefaultOut.x || GetRelativePos().y <= DefaultOut.y)
	{
		m_bIsEnd = true;
	}
}

void CFireboy::SkillEnd(float DeltaTime)
{
	m_bIsAttack = false;
	m_bIsJump = false;
	SetPhysicsSimulate(false);
}

void CFireboy::MoveCheck(float DeltaTime)
{
	// �������� ������ ������������

	if (m_bIsAttack)
	{
		return;
	}

	// ���� ������ ������ ���ݹ��� ���� ���Դٸ�
	if (m_bIsAttackUnit && GetRelativePos().x >= 700.f)
	{
		m_bIsAttack= true;
		m_Sprite->SetRelativeScale(130.f, 160.f, 0.f);
		m_Animation->ChangeAnimation("Fireboy_Cast");
	}

	else
	{
		AddRelativePos(GetAxis(AXIS_X) * 200.f * DeltaTime);
	}
}

void CFireboy::JumpCheck(float DeltaTime)
{
	// ������ �� ��� ������ ����
	if (m_bIsJump)
	{
		m_JumpTime += GetGravityAccel() * 0.6f * DeltaTime;

		// ó�� �� ��� ���� ���ϰ� ������.
	/*	if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}*/

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpPower) + (m_JumpAccel * m_JumpTime);
		if (jumpHeight <0.f)
		{
			jumpHeight *= 0.4f;
		}

		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)*DeltaTime);

		m_JumpAccel -= GetGravity() * 0.6f * DeltaTime;

		// �÷��̾ ������ �� �����ʿ� ���� ���
		if (m_JumpDirection == Direction::RIGHT)
		{
			AddRelativePos(GetAxis(AXIS_X) * 400.f * DeltaTime);
		}

		else
		{
			AddRelativePos(GetAxis(AXIS_X) * -400.f * DeltaTime);
		}
	}

	
}

void CFireboy::TimeCheck(float DeltaTime)
{
	// �����ϴ� ���ָ� ��Ÿ���� üũ�Ѵ�.
	if (!m_bIsAttackUnit)
	{
		return;
	}

	// ������������ ���� �������� �ʾҴٸ�
	//if (m_bIsAttack && !m_bIsJump)
	//{
	//	m_CoolTime -= DeltaTime;
	//}

	// ���� �������� �ʾ����� ĳ������ �����ٸ�.
	if (!m_bIsJump && m_JumpCastCount >= 3)
	{
		m_bIsJump = true;
		SetPhysicsSimulate(true);

		// �ٱ� ������ ���� ������ Ȯ�����ش�.
		if (CMugman::PlayerPos.x >= GetWorldPos().x)
		{
			m_JumpDirection = Direction::RIGHT;
			m_Animation->ChangeAnimation("Fireboy_Jump_Start");
		}

		else
		{
			m_JumpDirection = Direction::LEFT;
			m_Animation->ChangeAnimation("Fireboy_Jump_Start");

		}

		// Y ���̸�ŭ.
		float YDistance = CMugman::PlayerPos.y - GetWorldPos().y;
		m_JumpPower += YDistance * 0.2f;
		
		// Set JumpPower Limit
		if (m_JumpPower >150.f)
		{
			m_JumpPower = 150.f;
		}
	}
}

void CFireboy::AnimFrameEnd(const std::string& Name)
{
	if (Name == "Fireboy_Cast")
	{
		m_Animation->ChangeAnimation("Fireboy_Cast_Loop");
	}

	if (Name == "Fireboy_Cast_Loop")
	{
		++m_JumpCastCount;
	}

	if (Name == "Fireboy_Jump_Start")
	{
		if (m_JumpDirection == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Fireboy_Jump_Loop_R");
		}

		else
		{
			m_Animation->ChangeAnimation("Fireboy_Jump_Loop_L");
		}
	}
}


