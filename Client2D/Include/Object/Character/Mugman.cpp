#include "Mugman.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/MugmanAnimation2D.h"
#include "Engine.h"
#include "Bullet.h"
#include "../Static/StepCloud.h"

Vector3 CMugman::PlayerPos = {0.f,0.f,0.f};
Vector3 CMugman::PlayerPrevPos = { 0.f, 0.f, 0.f };


CMugman::CMugman() :
	m_bIsGround(true),
	m_bIsJump(false),
	m_bIsFall(false),
	m_bIsDash(false),
	m_bCanJump(true),
	m_bCanDash(true),
	m_JumpTime(0.f), m_FallTime(0.f),
	m_JumpVelocity(50.f),
	m_JumpAccel(90.f),
	m_DashSpeed(100.f),
	m_DashTime(0.0f),
	m_ShootCool(0.2f),
	m_DashCool(0.5f)	
{
	m_BulletCount = 1;
}

CMugman::CMugman(const CMugman& obj) : CCharacter(obj)
{

	m_Sprite = (CSpriteComponent*)FindSceneComponent("Mugman");
	m_Collider = (CColliderBox2D*)FindSceneComponent("MugmanCollider");
	m_Rotation = FindSceneComponent("Rotation");
	m_Muzzle = FindSceneComponent("Muzzle");
	//m_Arm = (CSpringArm2D*)FindSceneComponent("Arm");
	//m_Camera = (CCamera*)FindSceneComponent("Camera");
}

CMugman::~CMugman()
{
}

void CMugman::Start()
{
	CGameObject::Start();
}

bool CMugman::Init()
{
	CCharacter::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Mugman");
	m_Collider = CreateSceneComponent<CColliderBox2D>("MugmanCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_Muzzle = CreateSceneComponent<CSceneComponent>("Muzzle");
	//m_Arm = CreateSceneComponent<CSpringArm2D>("Arm");
	//m_Camera = CreateSceneComponent<CCamera>("Camera");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);
	m_Sprite->SetRelativePos(640.f, 100.f, 0.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Muzzle);
	//m_Sprite->SetRelativeRotationZ(30.f);
	//m_Sprite->SetPivot(0.5f, 0.f, 0.f);

	m_Collider->SetExtent(45.f, 70.f);
	m_Collider->SetCollisionProfile("Player");
	m_Collider->SetColliderType(Collider_Type::Character);

	
	m_Muzzle->SetInheritRotZ(true);
	m_Muzzle->SetRelativePos(Vector3(20.f, 80.f, 0.f));
	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	//m_Arm->SetOffset(0.f, 0.f, 0.f);
	//m_Arm->SetInheritPosZ(false);

	//m_Sprite->AddChild(m_Arm);
	//m_Arm->AddChild(m_Camera);

	//CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));

	m_Sprite->CreateAnimation2D<CMugmanAnimation2D>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CMugman>(this, &CMugman::AnimationFrameEnd);
	m_Animation->ChangeAnimation("Mugman_Idle_R");

	//m_Sprite->AddChild(m_Rotation);
	//m_Sprite->AddChild(m_Muzzle);
	
	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	CInput::GetInst()->AddKeyCallback<CMugman>("MoveUp", KT_Push, this, &CMugman::MoveUp);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveDown", KT_Push, this, &CMugman::MoveDown);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Push, this, &CMugman::MoveRight);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Push, this, &CMugman::MoveLeft);
	CInput::GetInst()->AddKeyCallback<CMugman>("Jump", KT_Down, this, &CMugman::Jump);
	CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Push, this, &CMugman::Shoot);
	CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Up, this, &CMugman::ShootEnd);

	CInput::GetInst()->AddKeyCallback<CMugman>("Dash", KT_Down, this, &CMugman::Dash);

	SetPhysicsSimulate(true);
	SetUseBlockMovement(true);
	SetPrevDirection(Direction::RIGHT);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);

	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::Begin, this, &CMugman::CollisionBegin);
	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::Overlap, this, &CMugman::CollisionOverlap);
	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::End, this, &CMugman::CollisionEnd);

	SetDefaultZ(0.5);
	return true;
}

void CMugman::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	// Idle check
	AnimCheck(DeltaTime);

	// ���� �ƴ� ��� �������� �ִ��� üũ
	if (!m_bIsGround)
	{
		FallCheck(DeltaTime);
	}

	// ����
	JumpCheck(DeltaTime);

	// �뽬
	DashCheck(DeltaTime);

	// �ð� üũ
	TimeCheck(DeltaTime);

	SavePlayerPos();
}

void CMugman::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMugman::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CMugman::Render(float DeltaTime)
{
	CCharacter::Render(DeltaTime);
}

CMugman* CMugman::Clone()
{
	return new CMugman(*this);
}

void CMugman::Animation2DNotify(const std::string& Name)
{
	CCharacter::Animation2DNotify(Name);
}

void CMugman::MoveUp(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump || !m_bIsGround)
	{
		return;
	}

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_AimUp_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_AimUp_L");
	}

	m_bIsMove = true;

	//AddRelativePos(GetAxis(AXIS_Y) * m_Speed * DeltaTime);
}

void CMugman::MoveDown(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump || !m_bIsGround)
	{
		return;
	}

	m_bIsMove = true;
	//AddRelativePos(GetAxis(AXIS_Y) * -m_Speed * DeltaTime);
}

void CMugman::MoveRight(float DeltaTime)
{
	// ���� ���̶�� �ִϸ��̼��� ��ü���� �ʴ´�.
	// ������̶�� Ű �Է��� ���� �ʴ´�.
	if (m_bIsDash || !m_bCanMove)
	{
		return;
	}

	m_State = Mugman_State::Run;

	// �̹� �������� ���� Anim�� �ٽ� ó������ ����ϸ� �ȵǹǷ� ���� ó��.
	if (!m_bIsJump && m_bIsGround)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_R");
	}

	AddRelativePos(GetAxis(AXIS_X)* m_Speed* DeltaTime);
	m_bIsMove = true;

}

void CMugman::MoveLeft(float DeltaTime)
{
	if (m_bIsDash || !m_bCanMove)
	{
		return;
	}

	m_State = Mugman_State::Run;
	
	// �������� �ƴ� ����
	if (!m_bIsJump && m_bIsGround)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
	}

	AddRelativePos(GetAxis(AXIS_X) * -m_Speed * DeltaTime);
	m_bIsMove = true;
}

void CMugman::Jump(float DeltaTime)
{
	// ���� �� �� ���� ���¶�� ��ȯ
	if (!m_bCanJump)
	{
		return;
	}

	// ������ ������ ���
	m_State = Mugman_State::Jump;
	m_PosY = GetRelativePos().y; // ó�� Y�� ����
	m_bCanAttack = false;
	m_bCanJump = false;

	m_bIsFall = false;
	m_bIsJump = true;
	m_bIsGround = false;

	ResetPhysicsSimulate();
	SetPhysicsSimulate(true);

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Jump_R");

	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Jump_L");
	}

}

void CMugman::Shoot(float DeltaTime)
{
	if (!m_bCanAttack || m_bIsDash || m_bIsFall || m_bIsJump)
	{
		return;
	}

	if (m_BulletCount > 0 )
	{
		m_bCanAttack = false;
		m_bIsAttack = true;
		--m_BulletCount;

		CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");

		// �������̿��ٸ� Animation�� �ٽ� �ٲ��� ����.

		if (m_PrevDirection == Direction::RIGHT)
		{
			m_Muzzle->SetRelativePos(20.f, 80.f, 0.f);
			m_Animation->ChangeAnimation("Mugman_Shoot_R");
			pBullet->SetBulletDirection(Direction::RIGHT);
		}

		if (m_PrevDirection == Direction::LEFT)
		{
			m_Muzzle->SetRelativePos(-20.f, 80.f, 0.f);
			m_Animation->ChangeAnimation("Mugman_Shoot_L");
			pBullet->SetBulletDirection(Direction::LEFT);
		}

		pBullet->SetRelativePos(m_Muzzle->GetWorldPos());
	}

	
	//pBullet->SetRelativeRotation(GetWorldRotation());

}

void CMugman::Dash(float DeltaTime)
{
	// ��ð� ������ ��Ȳ���� �Ǵ�
	if (!m_bCanDash)
	{
		return;
	}

	// �����ϴٸ� �������̰ų� �������� �ִ��� �Ǵ�
	if (m_bIsJump)
	{
		JumpEnd();
	}

	m_State = Mugman_State::Dash;
	m_bIsDash = true;

	m_bCanMove = false;
	m_bCanAttack = false;
	m_bCanDash = false;
	m_bCanJump = false;
	
	ResetPhysicsSimulate();
	SetPhysicsSimulate(true);

	// ���� ��������Ʈ ũ��� ������
	m_Sprite->SetRelativeScale(330.f, 330.f, 1.f);

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Dash_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Dash_L");
	}
}

void CMugman::ShootEnd(float DeltaTime)
{
	m_bIsAttack = false;
}

//void CMugman::Triple(float DeltaTime)
//{
//	float   Angle = GetWorldRotation().z - 30.f;
//
//	for (int i = 0; i < 3; ++i)
//	{
//		CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");
//
//		pBullet->SetRelativePos(m_Muzzle->GetWorldPos());
//		pBullet->SetRelativeRotation(GetWorldRotation());
//		pBullet->SetRelativeRotationZ(Angle);
//		pBullet->SetCollisionProfile("PlayerAttack");
//
//		Angle += 30.f;
//	}
//}


void CMugman::AnimationFrameEnd(const std::string& Name)
{
	// ���� �ִϸ��̼��� Dash�� ���
}

void CMugman::JumpCheck(float DeltaTime)
{
	if (m_bIsJump)
	{
		//m_bCanAttack = false;
		//y=-GA*V+b���� (a: �߷°��ӵ�, b: �ʱ� �����ӵ�)
		//���� : y = (-GA/2)*t*t + (V*t) ������ ��´�.(t: �����ð�, y: ������Ʈ�� ����)
		//��ȭ�� ���� height�� ���� ���� m_posY�� ���Ѵ�.

		m_JumpTime += GetGravityAccel() * DeltaTime;

		// ó�� �� ��� ���� ���ϰ� ������.
		if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpVelocity) + (m_JumpAccel * m_JumpTime);
		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)*DeltaTime);

		m_JumpAccel -= GetGravityAccel() * DeltaTime;
	}

	// ���� ���� �ƴ� ���
	else
	{
		JumpEnd();
	}
}

void CMugman::FallCheck(float DeltaTime)
{
	if (m_bIsDash)
	{
		return;
	}

	if (m_bIsFall)
	{
		m_FallTime+= GetGravityAccel() * DeltaTime;
		float FallHeight = (GetGravityAccel()) * m_FallTime * DeltaTime * 5;
		AddRelativePos(GetAxis(AXIS_Y) * -FallHeight);
	}
}

void CMugman::DashCheck(float DeltaTime)
{
	if (m_bIsDash)
	{
		m_DashTime += GetGravityAccel() * DeltaTime;

		float DashVelocity = static_cast<float>((m_DashTime * m_DashTime * GetGravity() * -0.5) + (m_DashSpeed * m_DashTime));

		if (m_PrevDirection == Direction::RIGHT)
		{
			AddRelativePos(GetAxis(AXIS_X) * (m_Speed + DashVelocity) * DeltaTime);
		}

		if (m_PrevDirection == Direction::LEFT)
		{
			AddRelativePos(GetAxis(AXIS_X) * -(m_Speed + DashVelocity) * DeltaTime);
		}

		m_DashSpeed -= GetGravityAccel() * DeltaTime;

		// ��ð� �����ٸ� ����
		if (DashVelocity <= 0.f)
		{
			DashEnd();
		}
	}

}


void CMugman::JumpEnd()
{
	// ���� ����� �� ���� ����
	m_bIsJump = false;
	m_JumpVelocity = 50.f;
	m_JumpTime = 0.0f;
	m_JumpAccel = 90.f;
}

void CMugman::DashEnd()
{
	m_State = Mugman_State::Idle;
	m_DashSpeed = 100.f;
	m_DashTime = 0.f;

	m_bIsDash = false;
	m_bCanJump = true;
	m_bCanMove = true;
	m_bCanAttack = true;

	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

	// ����� ���� �������� üũ
	if (!m_bIsGround && !m_bIsJump)
	{
		m_bIsFall = true;

		if (GetPrevDirection() == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_R");

		}

		if (GetPrevDirection() == Direction::LEFT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_L");
		}

		return;
	}


	if (GetPrevDirection() == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_R");

	}

	if (GetPrevDirection() == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_L");
	}


}

void CMugman::OnGround()
{
	// ���� ������� �����ϰų� ���� ������ ��� �ൿ�� ó��
	m_FallTime = 0.f;

	m_bIsFall = false;
	m_bIsJump = false;
	m_bIsGround = true;
	m_bIsAttack = false;

	m_bCanJump = true;
	m_bCanAttack = true;
	m_bCanDash = true;
	
	SetPhysicsSimulate(false);
	SetUseBlockMovement(true);

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_R");

	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_L");
	}
}

void CMugman::TimeCheck(float DeltaTime)
{
	m_ShootCool -= DeltaTime;
	m_DashCool -= DeltaTime;

	if (m_ShootCool < 0.0f)
	{
		m_bCanAttack = true;
		m_ShootCool = 0.2f;
		m_BulletCount = 1;
	}

	if (m_DashCool < 0.0f)
	{
		m_bCanDash = true;
		m_DashCool = 1.f;
	}
}

void CMugman::AnimCheck(float DeltaTime)
{
	m_bIsMove = false;

	// �����̶� �̵��ߴٸ� ����
	Vector2 PrevWorldPos = { GetPrevWorldPos().x , GetPrevWorldPos().y };
	Vector2 WorldPos = { GetWorldPos().x , GetWorldPos().y };

	// �������ٸ�
	if (PrevWorldPos != WorldPos)
	{
		return;
	}

	if (!m_bIsAttack && !m_bIsDash && !m_bIsFall && !m_bIsJump && !m_bIsMove)
	{
		if (GetPrevDirection() == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Mugman_Idle_R");
		}

		if (GetPrevDirection() == Direction::LEFT)
		{
			m_Animation->ChangeAnimation("Mugman_Idle_L");
		}
	}

	
}

void CMugman::SavePlayerPos()
{
	PlayerPos = GetWorldPos();
	PlayerPrevPos = GetPrevWorldPos();

}

void CMugman::OnStepCloud(float MoveZ, float CloudY)
{
	// �������϶��� ��zz��z��z zŸzzzzz����zz��
	if (m_bIsJump)
	{
		return; 
	}

	if (CloudY < GetWorldPos().y)
	{
		AddRelativePos(-MoveZ, 0.f, 0.f);
	}
}

void CMugman::InAir()
{
	// �������� �����Ҷ�
	m_bIsFall = true;
	m_bIsJump = false;
	m_bIsGround = false;
	m_bIsAttack = false;

	m_bCanAttack = false;
	m_bCanJump = false;

	if (!m_bIsDash)
	{
		ResetPhysicsSimulate();
		SetPhysicsSimulate(true);
		SetUseBlockMovement(true);

		if (m_PrevDirection == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_R");

		}

		if (m_PrevDirection == Direction::LEFT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_L");
		}
	}
}



void CMugman::CollisionBegin(const HitResult& result, CCollider* Collider)
{	
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		CStepCloud* pStepCloud = (CStepCloud*)result.DestCollider->GetOwner();

		// �ö󰡰� �ִ� ���̶�� �浹���� ����
		if (m_bIsJump && GetWorldPos().y > GetPrevWorldPos().y)
		{
			SetUseBlockMovement(false);
			return;
		}

		// �������� �� ��ġ�� �� �������� ������ ���������� �Ǵ�.
		if (pStepCloud->GetWorldPos().y < GetWorldPos().y)
		{
			OnStepCloud(pStepCloud->GetMoveDistance(), pStepCloud->GetWorldPos().y);
			OnGround();
		}
	}

	// ���� ������ �ݸ���
	if (result.DestCollider->GetName() == "GroundCollider")
	{
		OnGround();
	}

	if (result.DestCollider->GetName() == "DragonCollider")
	{
		if (!m_bIsGround)
		{
			InAir();
		}
	}
}

void CMugman::CollisionOverlap(const HitResult& result, CCollider* Collider)
{
	// ���� �ݸ����� ������� ĳ���� �ݸ����� �̵���Ŵ
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		CStepCloud* pStepCloud = (CStepCloud*)result.DestCollider->GetOwner();
		OnStepCloud(pStepCloud->GetMoveDistance(), pStepCloud->GetWorldPos().y);
	}

	if (result.DestCollider->GetName() == "GroundCollider")
	{
		//m_bIsGround = true;
	}
}

void CMugman::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	// �������� �ƴ϶�� �������� ������ ����.
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		if (!m_bIsJump && GetWorldPos().y  > result.DestCollider->GetWorldPos().y)
		{
			InAir();
		}
	}
}



