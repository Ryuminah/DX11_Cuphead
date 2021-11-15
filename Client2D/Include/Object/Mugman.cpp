#include "Mugman.h"
#include "../Animation2D/MugmanAnimation2D.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Bullet.h"

CMugman::CMugman() :
	m_bIsGround(true),
	m_bCanJump(true),
	m_bIsJump(false),
	m_bCanDash(true),
	m_bIsDash(false),
	m_bIsFall(false),
	m_JumpTime(0.f),
	m_JumpVelocity(50.f),
	m_JumpAccel(90.f),
	m_DashSpeed(50.f),
	m_DashTime(0.0f),
	m_ShootTime(0.1f),
	m_State(Mugman_State::Idle)
	
{

}

CMugman::CMugman(const CMugman& obj) : CFightObject(obj)
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
	CFightObject::Init();

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
	CInput::GetInst()->AddKeyCallback<CMugman>("Dash", KT_Down, this, &CMugman::Dash);

	SetDefaultZ(0.1f);
	SetPhysicsSimulate(true);
	SetUseBlockMovement(true);
	SetPrevDirection(Direction::RIGHT);

	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::Begin, this, &CMugman::CollisionBegin);


	return true;
}

void CMugman::Update(float DeltaTime)
{
	CFightObject::Update(DeltaTime);

	// ���� ���� ���
	if (m_bIsJump)
	{
		//y=-GA*V+b���� (a: �߷°��ӵ�, b: �ʱ� �����ӵ�)
		//���� : y = (-GA/2)*t*t + (V*t) ������ ��´�.(t: �����ð�, y: ������Ʈ�� ����)
		//��ȭ�� ���� height�� ���� ���� m_posY�� ���Ѵ�.
		
		m_JumpTime += GetGravityAccel() * DeltaTime;

			// ó�� �� ��� ���� ���ϰ� ������.
		if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100);
		}

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpVelocity) + (m_JumpAccel* m_JumpTime);
		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)* DeltaTime);
		
		m_JumpAccel -= GetGravityAccel() * DeltaTime;

		// ���� ��� ������ ���� ������ ����
		if (m_bIsGround)
		{ 
			JumpEnd();
		}
	}

	// �뽬 ���� ���
	if (m_bIsDash)
	{
		m_DashTime += GetGravityAccel() * DeltaTime;

		float DashVelocity = (m_DashTime * m_DashTime * GetGravity() * -0.5) + (m_DashSpeed * m_DashTime);

		if (m_PrevDirection == Direction::RIGHT)
		{
			AddRelativePos(GetAxis(AXIS_X) * (m_Speed + DashVelocity) * DeltaTime);
		}

		if (m_PrevDirection == Direction::LEFT)
		{
			AddRelativePos(GetAxis(AXIS_X) * -(m_Speed + DashVelocity) * DeltaTime);
		}

		m_DashSpeed -= GetGravityAccel() * DeltaTime;

		if (DashVelocity <= 0.f)
		{
			DashEnd();
			SetPhysicsSimulate(false);

			m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);


			m_State = Mugman_State::Idle;
		}
	}

	CheckShootTime(DeltaTime);
}

void CMugman::PostUpdate(float DeltaTime)
{
	CFightObject::PostUpdate(DeltaTime);
}

void CMugman::Collision(float DeltaTime)
{
	CFightObject::Collision(DeltaTime);
}

void CMugman::Render(float DeltaTime)
{
	CFightObject::Render(DeltaTime);
}

CMugman* CMugman::Clone()
{
	return new CMugman(*this);
}

void CMugman::Animation2DNotify(const std::string& Name)
{
	CFightObject::Animation2DNotify(Name);
}

void CMugman::MoveUp(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump)
	{
		return;
	}

	m_Animation->ChangeAnimation("Mugman_AimUp_R");

	//AddRelativePos(GetAxis(AXIS_Y) * m_Speed * DeltaTime);
}

void CMugman::MoveDown(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump)
	{
		return;
	}

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

	if (!m_bIsJump)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_R");
	}

	AddRelativePos(GetAxis(AXIS_X)* m_Speed* DeltaTime);

}

void CMugman::MoveLeft(float DeltaTime)
{
	if (m_bIsDash || !m_bCanMove)
	{
		return;
	}

	m_State = Mugman_State::Run;
	
	// �������� �ƴ� ����
	if (!m_bIsJump)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
	}

	AddRelativePos(GetAxis(AXIS_X) * -m_Speed * DeltaTime);
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
	m_bIsJump = true;
	m_bIsGround = false;
	SetPhysicsSimulate(true);
	SetUseBlockMovement(false);

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
	if (!m_bCanAttack)
	{
		return;
	}

	CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Shoot_R");
		pBullet->SetPrevDirection(Direction::RIGHT);
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Shoot_L");
		pBullet->SetPrevDirection(Direction::LEFT);
	}

	pBullet->SetRelativePos(m_Muzzle->GetWorldPos());
	//pBullet->SetRelativeRotation(GetWorldRotation());

	m_bCanAttack = false;
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
		// �������̶�� ������ ��� ����.
		JumpEnd();
	}

	m_State = Mugman_State::Dash;
	m_bIsDash = true;
	m_bCanMove = false;
	m_bCanAttack = false;
	m_bCanDash = false;
	m_bCanJump = false;
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

void CMugman::CheckJump()
{
	// ���϶��� ���� ����.
	
}

void CMugman::JumpEnd()
{
	m_State = Mugman_State::Idle;
	m_bCanJump = true;
	m_bCanAttack = true;

	m_bIsGround = true;
	m_bIsJump = false;
	m_JumpVelocity = 50.f;
	m_JumpTime = 0.0f;
	m_JumpAccel = 90.f;

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_R");

	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_L");
	}

	SetUseBlockMovement(true);
}

void CMugman::DashEnd()
{
	m_State = Mugman_State::Idle;
	m_bCanDash = true;
	m_bCanJump = true;
	m_bCanMove = true;
	m_bCanAttack = true;
	m_bIsDash = false;
	m_bIsGround = true;
	m_DashSpeed = 80.f;
	m_DashTime = 0.f;

	Vector2 CurDirection = { GetWorldPos().x - GetPrevWorldPos().x , GetWorldPos().y - GetPrevWorldPos().y };
	if (CurDirection.x > 0)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_R");

	}

	if (CurDirection.x < 0)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_L");
	}

	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

}

void CMugman::CheckShootTime(float DeltaTime)
{
	m_ShootTime -= DeltaTime;

	if (m_ShootTime <= 0.0f)
	{
		m_bCanAttack = true;
		m_ShootTime = 0.1f;
	}
}

void CMugman::OnStepCloud(float MoveZ, float CloudY)
{
	// �浹ü�� ������ ������ �Ǵ��� ��, ���� �ε��ƴٸ� return, ���� �ε��ƴٸ� ���ߴ� ó��
	// �������̶�� �������� ����.
	if (m_bIsJump)
	{
		return; 
	}

	// �������� �� ��ġ�� �� �������� ������
	if (CloudY < GetWorldPos().y)
	{
		AddRelativePos(-MoveZ, 0.f, 0.f);
	}
	
	
}



void CMugman::CollisionBegin(const HitResult& result, CCollider* Collider)
{	
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		// �ö󰡰� �ִ� ���̶�� �浹���� ����
		if (GetWorldPos().y - GetPrevWorldPos().y > 0)
		{
			return;
		}
		
		m_bIsGround = true;
		SetPhysicsSimulate(false);
	}

	// ���� ������ �ݸ���
	if (result.DestCollider->GetName() == "GroundCollider")
	{
		SetUseBlockMovement(true);
		JumpEnd();
	}
}

void CMugman::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}



