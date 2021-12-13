#include "Mugman.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/MugmanAnimation2D.h"
#include "Scene/CameraManager.h"
#include "Engine.h"
#include "Bullet.h"
#include "../Static/StepCloud.h"
#include  "../Effect/Dust.h"

Vector3 MuzzlePosition::Up = { 10.f, 50.f, 0.f };
Vector3 MuzzlePosition::Up_Digonal_R = { 20.f, 70.f, 0.f };
Vector3 MuzzlePosition::Up_Digonal_L = { -20.f, 70.f, 0.f };
Vector3 MuzzlePosition::Down_Duck_R = { 20.f, 10.f, 0.f };
Vector3 MuzzlePosition::Down_Duck_L = { -20.f, 10.f, 0.f };
Vector3 MuzzlePosition::Down_Digonal_R = { 45.f, 10.f, 0.f };
Vector3 MuzzlePosition::Down_Digonal_L = { -45.f, 10.f, 0.f };
Vector3 MuzzlePosition::Down = { 0.f, -40.f, 0.f };

Vector3 CMugman::PlayerPos = {0.f,0.f,0.f};
Vector3 CMugman::PlayerPrevPos = { 0.f, 0.f, 0.f };
bool	CMugman::bUseCamera = false;


CMugman::CMugman() :
	m_bIsGround(true),
	m_bIsJump(false),
	m_bIsFall(false),
	m_bIsDash(false),
	m_bIsDamaged(false),
	m_bIsParry(false),
	m_bIsAiming(false),
	m_bGameStart(false),
	m_ParryTime(0.f),m_ParryAccel(70.f), m_ParryVelocity(70.f), m_StartY(0.f),
	m_JumpTime(0.f),m_JumpVelocity(50.f),m_JumpAccel(90.f),
	m_FallTime(0.f),
	m_DashSpeed(70.f),m_DashTime(0.0f),
	m_ShootCool(0.2f),
	m_DashCool(0.5f),
	m_IntroTime(5.f),
	m_ParryCheckTime(0.f),
	m_InvincibleTime(0.f),
	m_TimeToFrame(0.f),
	m_Frame(0),
	m_MuzzleMaxY(50.f), m_DustTime(0.f),
	m_bIsDuck(false), m_bIsDuckLoop(false)
{
	m_BulletCount = 1;
	m_bCanAim = true;
	m_bCanJump = true;
	m_bCanAttack = true;
	m_bCanMove = true;
	m_bCanDash = true;
	m_bCanParry = false;
	m_bCanDuck = true;
	m_bParrySuccess = false;

	m_bIsFightScene = true;
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
	CInput::GetInst()->ClearCallback();
}

void CMugman::Start()
{
	CGameObject::Start();

	CInput::GetInst()->AddKeyCallback<CMugman>("AimUp", KT_Push, this, &CMugman::AimUp);
	CInput::GetInst()->AddKeyCallback<CMugman>("Duck", KT_Push, this, &CMugman::Duck);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Push, this, &CMugman::MoveRight);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Push, this, &CMugman::MoveLeft);
	CInput::GetInst()->AddKeyCallback<CMugman>("Aim", KT_Push, this, &CMugman::Aim);
	CInput::GetInst()->AddKeyCallback<CMugman>("Jump", KT_Down, this, &CMugman::Jump);
	CInput::GetInst()->AddKeyCallback<CMugman>("Dash", KT_Down, this, &CMugman::Dash);


	// End CallBack Func
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Up, this, &CMugman::MoveEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Up, this, &CMugman::MoveEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("Aim", KT_Up, this, &CMugman::AimEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("AimUp", KT_Up, this, &CMugman::AimEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("Duck", KT_Up, this, &CMugman::DuckEnd);

	// ���� ��Ȳ�� ��� XŰ�� �������� ���
	if (m_bIsFightScene)
	{
		CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Push, this, &CMugman::Shoot);
		CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Up, this, &CMugman::ShootEnd);
	}

	else
	{

	}
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
	m_Sprite->SetRelativePos(150.f, 265.f, 0.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Muzzle);
	//m_Sprite->SetRelativeRotationZ(30.f);
	//m_Sprite->SetPivot(0.5f, 0.f, 0.f);

	m_Collider->SetExtent(45.f, 70.f);
	m_Collider->SetCollisionProfile("Player");
	m_Collider->SetColliderType(Collider_Type::Character);

	
	m_Muzzle->SetInheritRotZ(true);
	m_Muzzle->SetRelativePos(Vector3(10.f, 40.f, 0.f));
	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	//m_Arm->SetOffset(0.f, 0.f, 0.f);
	//m_Arm->SetInheritPosZ(false);

	//m_Sprite->AddChild(m_Arm);
	//m_Arm->AddChild(m_Camera);

	//CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	m_Sprite->CreateAnimation2D<CMugmanAnimation2D>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CMugman>(this, &CMugman::AnimationFrameEnd);
	m_Animation->ChangeAnimation("Mugman_Idle_R");

	//m_Sprite->AddChild(m_Rotation);
	//m_Sprite->AddChild(m_Muzzle);
	
	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	SetPhysicsSimulate(true);
	SetUseBlockMovement(true);
	SetPrevDirection(Direction::RIGHT);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);

	//SetDefaultZ(0.3f);

	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::Begin, this, &CMugman::CollisionBegin);
	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::Overlap, this, &CMugman::CollisionOverlap);
	m_Collider->AddCollisionCallbackFunction<CMugman>(Collision_State::End, this, &CMugman::CollisionEnd);

	return true;
}

// �̵�, ����, �ִϸ��̼� ����, �ð� �� �ǽð����� ����ؾ� �� �͵��� Update���� ó��
void CMugman::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	// Idle check
	AnimCheck(DeltaTime);

	// ����
	JumpCheck(DeltaTime);

	if (m_bCanParry)
	{
		ParryCheck(DeltaTime);
	}

	// ���� �ƴ� ��� �������� �ִ��� üũ
	if (!m_bIsGround)
	{
		FallCheck(DeltaTime);
	}


	// �뽬
	DashCheck(DeltaTime);

	// �ð� üũ
	TimeCheck(DeltaTime);

	// �ѱ� ����
	MuzzleLoopCheck(DeltaTime);
	
	// �÷��̾� ��ġ ����
	SavePlayerPos();

}

void CMugman::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	if (!bUseCamera || CMugman::PlayerPos.x < 640.f || CMugman::PlayerPos.x >= 6090.f || GetWorldPos() == GetPrevWorldPos())
	{
		return;
	}

	m_pScene->GetCameraManager()->GetCurrentCamera()->SetRelativePos(GetRelativePos().x - 640.f, 0.f, 0.f);
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

void CMugman::AimUp(float DeltaTime)
{
	if (!m_bCanAim || m_bIsDash || m_bIsJump || !m_bIsGround)
	{
		return;
	}

	m_bCanMove = false;
	m_bIsAiming = true;

	SetRelativeScale(200.f, 200.f, 0.f);

	// ������ Ȱ��ȭ �Ǿ� ���� ��� �밢�� �Է±��� üũ�غ��ƾ� �Ѵ�
	if (GetAsyncKeyState('C') & 0x8000)
	{
		// Digonal UP
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_Animation->ChangeAnimation("Mugman_AimUp_Digonal_R");
			return;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_Animation->ChangeAnimation("Mugman_AimUp_Digonal_L");
			return;
		}
	}

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_AimUp_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_AimUp_L");
	}
	
}

void CMugman::Duck(float DeltaTime)
{
	if (m_bIsAiming)
	{
		AimDown();
	}

	// ���� �� ���� ���
	if (!m_bCanDuck)
	{
		return;
	}

	// �������̸� �����ϴ� �ִ�����
	m_bIsDuck = true;
	m_bCanMove = false;
	m_Collider->SetExtent(45.f, 20.f);

	if (m_PrevDirection == Direction::RIGHT)
	{
		if (!m_bIsDuckLoop)
		{
			m_Animation->ChangeAnimation("Mugman_Duck_R");
		}

		else
		{
			m_Animation->ChangeAnimation("Mugman_Duck_Loop_R");
		}
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		if (!m_bIsDuckLoop)
		{
			m_Animation->ChangeAnimation("Mugman_Duck_L");
		}

		else
		{
			m_Animation->ChangeAnimation("Mugman_Duck_Loop_L");
		}
	}

	// ������ �Ʒ��� ���������� �ϴ� ���
	if (m_bIsGround && (GetAsyncKeyState('Z') & 0x8000))
	{
		InAir();
		return;
	}
}

void CMugman::MoveRight(float DeltaTime)
{
	// Aiming ���̶�� �̵��� ���� �ʰ� ���� ���⸸ �ٲ���
	if (m_bIsDuck)
	{
		m_PrevDirection = Direction::RIGHT;
	}

	if (m_bIsAiming)
	{
		m_PrevDirection = Direction::RIGHT;

		// ��, �Ʒ� ���� �Է��� �ƴ� ��쿡�� �ִϸ��̼��� �������ش�.
		if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			m_Sprite->SetRelativeScale(140.f, 170.f, 0.f);
			m_Animation->ChangeAnimation("Mugman_Aim_R");
		}
	}

	// �밢�� �Է��� ���� ��� �ִϸ��̼Ǹ� ��ü���փm

	// ������̶�� Ű �Է��� ���� �ʴ´�.
	if (!m_bCanMove)
	{
		return;
	}

	// �̵��� ���ÿ� �ִϸ��̼��� �ٲ�� �� ���(�ٸ� ���°� �ƴ� ���)
	// ���� ���̰ų�, �������� �ְų� �̹� �޸��� ���̿��� ��� �ִϸ��̼��� ��ü���� �ʴ´�
	if (!m_bIsJump && !m_bIsFall && m_bIsMove &&!m_bParrySuccess)
	{
		// �������̸� �����ϴ� �ִ�����
		if (m_bIsAttack)
		{
			m_Animation->ChangeAnimation("Mugman_Run_Shoot_R");
		}

		else
		{
			m_Animation->ChangeAnimation("Mugman_Run_Normal_R");
		}

	}

	AddRelativePos(GetAxis(AXIS_X)* m_Speed* DeltaTime);
	m_bIsMove = true;
}

void CMugman::MoveLeft(float DeltaTime)
{
	if (m_bIsDuck)
	{
		m_PrevDirection = Direction::LEFT;
	}

	// Aiming ���̶�� �̵��� ���� �ʰ� ���� ���⸸ �ٲ��ش�.
	if (m_bIsAiming)
	{
		m_PrevDirection = Direction::LEFT;

		// ��, �Ʒ� ���� �Է��� �ƴ� ��쿡�� �ִϸ��̼��� �������ش�.
		if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			m_Sprite->SetRelativeScale(140.f, 170.f, 0.f);
			m_Animation->ChangeAnimation("Mugman_Aim_L");
		}
	}

	if (!m_bCanMove)
	{
		return;
	}

	if (!m_bIsJump && !m_bIsFall && m_bIsMove && !m_bParrySuccess)
	{
		if (m_bIsAttack)
		{
			m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
		}

		else
		{
			m_Animation->ChangeAnimation("Mugman_Run_Normal_L");
		}
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
	m_bCanJump = false;
	m_bCanAim = false;
	m_bCanDuck = false;

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

void CMugman::Parry()
{
	if (m_bIsJump)
	{
		JumpEnd();
	}

	m_bCanAttack = false;
	m_bCanJump = false;
	m_bCanAim = false;
	m_bCanDash = true;
	m_bCanDamaged = false;

	m_bIsFall = false;
	m_bIsGround = false;
	m_bParrySuccess = true;

	ResetPhysicsSimulate();
	SetPhysicsSimulate(true);

	m_StartY = GetRelativePos().y;
	m_Sprite->SetRelativeScale(150.f, 150.f, 1.f);

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Parry_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Parry_L");
	}
}

void CMugman::Shoot(float DeltaTime)
{
	if (!m_bCanAttack || m_bIsDash )
	{
		return;
	}

	if (m_BulletCount > 0)
	{
		--m_BulletCount;
		CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");


		// �밢�������� �켱 üũ�Ѵ�.
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			// �밢���� ��� ���� ���ÿ� �����ִ����� ���� �����ؾ� �Ѵ�.
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				pBullet->SetBulletDirection(Direction::RIGHT);
				m_Muzzle->SetWorldRotationZ(45.f);
				m_Muzzle->SetRelativePos(MuzzlePosition::Up_Digonal_R);
			}

			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				pBullet->SetBulletDirection(Direction::LEFT);
				m_Muzzle->SetWorldRotationZ(-45.f);
				m_Muzzle->SetRelativePos(MuzzlePosition::Up_Digonal_L);
			}

			else
			{
				// �׳� ���� ����ϴ� ���
				pBullet->SetBulletDirection(Direction::RIGHT);
				m_Muzzle->SetRelativePos(MuzzlePosition::Up);
				m_Muzzle->SetWorldRotationZ(90.f);
			}
		}

		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			// ���� ���� �ƴ� ���(Duck) �ѱ� ��ġ�� �������ش�
			if (!m_bIsAiming)
			{
				if (m_PrevDirection == Direction::RIGHT)
				{
					pBullet->SetBulletDirection(Direction::RIGHT);
					m_Muzzle->SetRelativePos(MuzzlePosition::Down_Duck_R);
				}

				if(m_PrevDirection == Direction::LEFT)
				{
					pBullet->SetBulletDirection(Direction::LEFT);
					m_Muzzle->SetRelativePos(MuzzlePosition::Down_Duck_L);
				}
			}

			// ���� ���� �� �� ���
			else
			{
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				{
					pBullet->SetBulletDirection(Direction::RIGHT);
					m_Muzzle->SetWorldRotationZ(-45.f);
					m_Muzzle->SetRelativePos(MuzzlePosition::Down_Digonal_R);
				}

				else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				{
					pBullet->SetBulletDirection(Direction::LEFT);
					m_Muzzle->SetWorldRotationZ(45.f);
					m_Muzzle->SetRelativePos(MuzzlePosition::Down_Digonal_L);
				}

				else
				{
					// �׳� �Ʒ��� ����ϴ� ���
					pBullet->SetBulletDirection(Direction::RIGHT);
					m_Muzzle->SetRelativePos(MuzzlePosition::Down);
					m_Muzzle->SetWorldRotationZ(-90.f);
				}
			}
		}

		// �� �Ʒ��� ���� Ű �Է��� ���� ���
		else
		{
			if (m_PrevDirection == Direction::RIGHT)
			{
				pBullet->SetBulletDirection(Direction::RIGHT);

				// ���� ����� ��츸 �ִϸ��̼��� �ٲ��ش�.
				if (!m_bIsMove && !m_bIsJump)
				{
					m_Animation->ChangeAnimation("Mugman_Shoot_R");
				}
			}

			if (m_PrevDirection == Direction::LEFT)
			{
				pBullet->SetBulletDirection(Direction::LEFT);
				Vector3 CurrentMuzzlePos = m_Muzzle->GetRelativePos();
				m_Muzzle->SetRelativePos(-CurrentMuzzlePos.x, CurrentMuzzlePos.y, CurrentMuzzlePos.z);

				if (!m_bIsMove && !m_bIsJump)
				{
					m_Animation->ChangeAnimation("Mugman_Shoot_L");
				}
			}
		}

		pBullet->SetWorldRotationZ(m_Muzzle->GetWorldRotation().z);
		pBullet->SetRelativePos(m_Muzzle->GetWorldPos());

		m_bCanAttack = false;
		m_bIsAttack = true;
	}
}

void CMugman::Aim(float DeltaTime)
{
	// ��, �쿡 ���õ� ������ �ش� �κп��� ó���Ѵ�.
	if (!m_bCanAim)
	{
		return;
	}

	m_bCanDuck = false;
	m_bCanMove = false;
	m_bIsAiming = true;
}

void CMugman::AimDown()
{
	m_bCanDuck = false;
	m_bCanMove = false;
	m_bIsAiming = true;

	SetRelativeScale(200.f, 200.f, 0.f);

	// ������ Ȱ��ȭ �Ǿ� ���� ��� �밢�� �Է±��� üũ�غ��ƾ� �Ѵ�
	if (GetAsyncKeyState('C') & 0x8000)
	{
		// Digonal Down
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			float   Angle = GetWorldRotation().z - 30.f;
			m_Animation->ChangeAnimation("Mugman_AimDown_Digonal_R");
			return;

		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_Animation->ChangeAnimation("Mugman_AimDown_Digonal_L");
			return;
		}
	}


	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_AimDown_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_AimDown_L");
	}
	
}

void CMugman::Dash(float DeltaTime)
{
	// ��ð� ������ ��Ȳ���� �Ǵ�
	if (!m_bCanDash && !m_bIsDamaged && !m_bParrySuccess)
	{
		return;
	}

	// �����ϴٸ� �������̰ų� �������� �ִ��� �Ǵ�
	if (m_bIsJump)
	{
		JumpEnd();
	}

	m_bCanMove = false;
	m_bCanAttack = false;
	m_bCanDash = false;
	m_bCanJump = false;
	m_bCanAim = false;
	m_bCanDuck = false;

	m_bIsDash = true;
	
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

void CMugman::Hit()
{
	// �������� ���� �� ���� ��Ȳ�̶��
	if (!m_bCanDamaged)
	{
		return;
	}

	if (m_bIsDash)
	{
		DashEnd();
	}

	if (m_bIsJump)
	{
		JumpEnd();
	}

	if (m_bIsFall)
	{
		FallEnd();
	}

	if (m_bIsAiming)
	{
		m_bCanMove = true;
		m_bIsAiming = false;
	}

	// �� �� �ִ� �ൿ ���� ���� ��� ���¸� ��� ������
	m_bCanAim = false;
	m_bCanAttack = false;
	m_bCanDash = false;
	m_bCanMove = false;
	m_bCanDamaged = false;
	m_bCanJump = false;

	m_bIsDamaged = true;

	m_Sprite->SetRelativeScale(200.f, 230.f, 1.f);

	if (m_PrevDirection == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Hit_R");
	}

	if (m_PrevDirection == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Hit_L");
	}

	++m_HitCount;
}

void CMugman::ShootEnd(float DeltaTime)
{
	m_bIsAttack = false;
	m_ShootCool = 0.2f;
	// Z���� �׻� �ʱ�ȭ ���ش�.
	m_Muzzle->SetWorldRotationZ(0.f);
	
}

void CMugman::MoveEnd(float DeltaTime)
{
	m_bIsMove = false;
	m_DustTime = 0.f;
}

void CMugman::DuckEnd(float DeltaTime)
{
	m_bCanMove = true;

	if (m_bIsAiming)
	{
		AimEnd(DeltaTime);
	}

	if (m_bIsDuck)
	{
		m_Collider->SetExtent(45.f, 70.f);
		m_bIsDuck = false;
		m_bIsDuckLoop = false;
	}
}

void CMugman::AimEnd(float DeltaTime)
{
	m_bCanMove = true;
	m_bCanDuck = true;
	m_bIsAiming = false;

	SetRelativeScale(200.f, 200.f, 1.f);

	if (GetPrevDirection() == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_R");

	}

	if (GetPrevDirection() == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Idle_L");
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
	if (Name == "Mugman_Hit_R" || Name == "Mugman_Hit_L")
	{
		HitEnd();
	}

	// �ִϸ��̼��� ����Ǹ� ������ ���� ���·� �ǵ��ư���. (������ ����� �ƴ� )
	if (Name == "Mugman_Parry_R" || Name == "Mugman_Parry_L")
	{
		m_bCanAttack = false;
		m_bCanJump = false;
		m_bCanAim = false;
		m_bCanDash = true;
		m_bCanDamaged = true;

		m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

		if (GetPrevDirection() == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_R");

		}

		if (GetPrevDirection() == Direction::LEFT)
		{
			m_Animation->ChangeAnimation("Mugman_Jump_L");
		}
	}

	if ((Name == "Mugman_Duck_R" || Name == "Mugman_Duck_L" ) && m_bIsDuck)
	{
		m_bIsDuckLoop = true;
	}
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

void CMugman::ParryCheck(float DeltaTime)
{
	// �и� �ð��� �и��� �������� ���
	if (m_bIsParry && m_bParrySuccess)
	{
		if (m_bIsJump)
		{
			JumpEnd();
		}

		m_ParryTime += GetGravityAccel() * DeltaTime;

		// ó�� �� ��� ���� ���ϰ� ������.
	/*	if (m_ParryAccel == 70.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}*/

		float ParryHeight = (m_ParryTime * m_ParryTime * GetGravity() * -0.5f) + (m_ParryTime * m_ParryVelocity) + (m_ParryAccel * m_ParryTime);
		AddRelativePos(GetAxis(AXIS_Y) * (ParryHeight)*DeltaTime);

		m_ParryAccel -= GetGravityAccel() * DeltaTime;

		// ó�� ��ġ���� ���������� �� ��� �и��� �����ϰ� Fall ���·� ��ȯ��
	/*	if (m_StartY > GetRelativePos().y)
		{
			ParryEnd();
		}*/
	}
}

void CMugman::FallCheck(float DeltaTime)
{
	if (m_bIsDash)
	{
		return;
	}

	// ���� �������� �ִ� ���̶�� (�����ʹ� �ٸ� ������)
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

void CMugman::ParryEnd()
{
	// ���� ����� �� �и� ����
	m_bIsParry = false;
	m_bCanParry = false;
	m_bParrySuccess = false;

	m_ParryVelocity = 70.f;
	m_ParryTime = 0.f;
	m_ParryAccel = 70.f;
	m_ParryCheckTime = 0.f;

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

	// ���� ���
	else
	{
		m_bCanDuck = true;

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


void CMugman::DashEnd()
{
	m_DashSpeed = 70.f;
	m_DashTime = 0.f;

	m_bIsDash = false;

	m_bCanJump = true;
	m_bCanMove = true;
	m_bCanAttack = true;
	m_bCanAim = true;


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

	// ���� ���
	else
	{
		m_bCanDuck = true;

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

void CMugman::HitEnd()
{
	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

	m_bCanAttack = true;
	m_bCanDash = true;
	m_bCanMove = true;
	m_bCanJump = true;
	m_bCanDamaged = true;
	m_bCanAim = true;

	m_bIsDamaged = false;

	Invincible();

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

	if (m_bIsParry)
	{
		ParryEnd();
	}
	//m_bIsAttack = false;

	m_bCanJump = true;
	m_bCanAttack = true;
	m_bCanDash = true;
	m_bCanAim = true;
	m_bCanDuck = true;

	
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
	// ������ ���� �������� �ʾҴٸ� �ð��ʸ� ���� �ʰ� �� �����ϱ�..
	if (!m_bGameStart)
	{
		m_IntroTime -= DeltaTime;

		if (m_IntroTime < 0.f)
		{
			m_IntroTime = 0.f;
			m_bGameStart = true;
			CStepCloud::m_bIsStageStart = true;
		}
	}

	// Add Time
	m_TimeToFrame += DeltaTime;
	m_ShootCool -= DeltaTime;
	m_DashCool -= DeltaTime;

	if (m_bIsMove && m_bIsGround)
	{
		m_DustTime += DeltaTime;
	}

	if (m_bIsInvincible)
	{
		m_InvincibleTime += DeltaTime;
	}

	// �и� ���� �ð��� �и��� �������� �ʾ��� ���� ���� �ð��� ���.
	if (m_bIsParry && !m_bParrySuccess)
	{
		m_ParryCheckTime += DeltaTime;
	}

	// Check Time Condition
	// 60������ ����
	if (m_TimeToFrame >= 0.1f)
	{
		++m_Frame;
		m_TimeToFrame = 0.f;
	}

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

	if (m_DustTime >= 0.3f)
	{
		m_DustTime = 0.f;
		CDust* pDust = m_pScene->SpawnObject<CDust>("Dust");
		pDust->SetRelativePos(GetPrevWorldPos());
	}

	if (m_InvincibleTime >= 0.5f)
	{
		InvincibleEnd();
		m_InvincibleTime = 0.f;
	}

	// �и��� �ڵ�����
	if (m_ParryCheckTime >= 0.3f)
	{
		m_bCanParry = false;
		m_bIsParry = false;
		m_bParrySuccess = false;
	}

}

void CMugman::AnimCheck(float DeltaTime)
{
	Vector2 PrevWorldPos = { GetPrevWorldPos().x , GetPrevWorldPos().y };
	Vector2 WorldPos = { GetWorldPos().x , GetWorldPos().y };

	if (!m_bIsAttack && !m_bIsDash && !m_bIsFall && !m_bIsJump && !m_bIsAiming && 
		!m_bIsMove && !m_bIsDamaged && !m_bIsDuck && (!m_bIsParry && !m_bParrySuccess))
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

void CMugman::DeathCheck(float DeltaTime)
{
	if (m_HitCount >= 3)
	{
		m_Animation->ChangeAnimation("Mugman_Death");
	}
}


void CMugman::MuzzleLoopCheck(float DeltaTime)
{
	// �ڻ��� �Լ��� �ݺ�
	// Move Y
	float MoveY = sin(PI * 2 / 30.f * m_Frame) * m_MuzzleMaxY;
	m_Muzzle->AddRelativePos(GetAxis(AXIS_Y) * MoveY * DeltaTime);

	// ȸ�� ���� ��쵵 �����غ���.
	/*if (m_Muzzle->GetRelativeRotation().z != 0.f)
	{
		m_Muzzle->AddRelativePos(GetAxis(AXIS_X) * MoveY * DeltaTime);
	}*/
}

void CMugman::SavePlayerPos()
{
	PlayerPos = GetWorldPos();
	PlayerPrevPos = GetPrevWorldPos();
}

void CMugman::OnStepCloud(float MoveZ, float CloudY)
{
	// �������϶��� ������ Ÿ������
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
	if (m_bIsGround)
	{
		return;
	}

	// �������� �����Ҷ�
	m_bIsFall = true;
	m_bIsJump = false;
	m_bIsGround = false;
	m_bIsAttack = false;
	m_bIsAiming = false;

	m_bCanJump = false;
	m_bCanAim = false;
	m_bCanDuck = false;


	if (!m_bIsDash && !m_bParrySuccess)
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

void CMugman::FallEnd()
{
	m_FallTime = 0.f;
	m_bIsFall = false;
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

		// �������� �� ��ġ�� �� �������� ������ ���������� �Ǵ�(�����̱� ����).
		if (pStepCloud->GetWorldPos().y < GetWorldPos().y)
		{
			SetWorldPos(GetWorldPos().x, result.DestCollider->GetMax().y, GetWorldPos().z);
			OnStepCloud(pStepCloud->GetMoveDistance(), pStepCloud->GetWorldPos().y);
			OnGround();
		}
	}

	if (result.DestCollider->GetProfile()->Name == "Static" && result.DestCollider->GetName() != "GroundCollider")
	{
		// �ö󰡰� �ִ� ���̶�� �浹���� ����
		if (m_bIsJump && GetWorldPos().y > GetPrevWorldPos().y)
		{
			SetUseBlockMovement(false);
			return;
		}

		else
		{
			if (!m_bIsFall)
			{
				OnGround();
			}

			if (GetWorldPos().y > result.DestCollider->GetOwner()->GetWorldPos().y &&
				(GetWorldPos().x > result.DestCollider->GetMin().x && GetWorldPos().x < result.DestCollider->GetMax().x))
			{
				SetWorldPos(GetWorldPos().x, result.DestCollider->GetMax().y, GetWorldPos().z);
				// ��ġ�� �� �������� ���� ������ ���� (y����)
			}
		}
	}

	if (result.DestCollider->GetName() == "GroundCollider")
	{
		OnGround();
	}


	// �� �浹 ����..
	if (result.DestCollider->GetName() == "DragonCollider")
	{
		/*Vector3 CurrentWorldPos = GetWorldPos();
		SetWorldPos(GetPrevWorldPos().x, CurrentWorldPos.y, CurrentWorldPos.z);*/

		if (!m_bIsGround)
		{
			InAir();
		}
	}

	// �浹ü ������ ��ų�̰� ������ �ƴ� ���
	if (result.DestCollider->GetProfile()->Name == "Skill" && m_bCanDamaged)
	{
		//Hit();
	}

	// �浹ü ������ ��ų�̰� ������ �ƴ� ���
	if (result.DestCollider->GetProfile()->Name == "Parry")
	{
		m_bCanParry = true;
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
		m_bIsGround = true;
	}

	// �浹 �߿��� �и��� �����Ѵ�
	if (result.DestCollider->GetProfile()->Name == "Parry")
	{
		// �̹� �и��� �ߴٸ� 
		if (m_bParrySuccess)
		{
			return;
		}

		if (m_bCanParry)
		{
			m_bCanDamaged = false;
			m_bIsParry = true;

			// ���� ������ ���� ���¶�� �и��� �����Ѵ�
			if (GetAsyncKeyState('Z') & 0x8000)
			{
				Parry();
			}
		}

		// �浹 ���̳� �и� ���� �ð��� ���� ���� ��� �ǰ� üũ
		if (!m_bCanParry && !m_bIsParry && !m_bParrySuccess)
		{
			m_bCanDamaged = true;
			ParryEnd();
			Hit();
		}
	}
}

void CMugman::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	// �������� �ƴ϶�� �������� ������ ����.
	if (result.DestCollider->GetName() == "StepCloudCollider" ||
		(result.DestCollider->GetProfile()->Name == "Static" && result.DestCollider->GetName() != "GroundCollider"))
	{
		if (!m_bIsJump && GetWorldPos().y >= result.DestCollider->GetMax().y)
		{
			m_bIsGround = false;
			InAir();
		}
	}

	if (result.DestCollider->GetName() == "GroundCollider")
	{
		m_bIsGround = false;
	}


	// ��Ҵ� ������ ��� �и� �Ұ� ���·� �����ϰ� ���õ� ���� �ʱ�ȭ
	if (!m_bParrySuccess && result.DestCollider->GetProfile()->Name == "Parry")
	{
		//ResetParry();
	}
}



