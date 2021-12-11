#include "Mugman.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/MugmanAnimation2D.h"
#include "Engine.h"
#include "Bullet.h"
#include "../Static/StepCloud.h"
#include  "../Effect/Dust.h"

Vector3 CMugman::PlayerPos = {0.f,0.f,0.f};
Vector3 CMugman::PlayerPrevPos = { 0.f, 0.f, 0.f };

CMugman::CMugman() :
	m_bIsGround(true),
	m_bIsJump(false),
	m_bIsFall(false),
	m_bIsDash(false),
	m_bIsDamaged(false),
	m_bIsParry(false),
	m_bIsAiming(false),
	m_bGameStart(false),
	m_ParryTime(0.f),m_ParryAccel(50.f), m_ParryVelocity(70.f), m_StartY(0.f),
	m_JumpTime(0.f),m_JumpVelocity(50.f),m_JumpAccel(90.f),
	m_FallTime(0.f),
	m_DashSpeed(100.f),m_DashTime(0.0f),
	m_ShootCool(0.2f),
	m_DashCool(0.5f),
	m_IntroTime(5.f),
	m_ParryCheckTime(0.f),
	m_InvincibleTime(0.f),
	m_TimeToFrame(0.f),
	m_Frame(0),
	m_MuzzleMaxY(50.f), m_DustTime(0.f)
{
	m_BulletCount = 1;
	m_bCanAim = true;
	m_bCanJump = true;
	m_bCanAttack = true;
	m_bCanMove = true;
	m_bCanDash = true;
	m_bCanParry = false;
	m_bParrySuccess = false;
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
	m_Muzzle->SetRelativePos(Vector3(10.f, -15.f, 0.f));
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

	CInput::GetInst()->AddKeyCallback<CMugman>("MoveUp", KT_Push, this, &CMugman::MoveUp);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveDown", KT_Push, this, &CMugman::MoveDown);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Push, this, &CMugman::MoveRight);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Push, this, &CMugman::MoveLeft);
	CInput::GetInst()->AddKeyCallback<CMugman>("Aim", KT_Push, this, &CMugman::Aim);
	CInput::GetInst()->AddKeyCallback<CMugman>("Jump", KT_Down, this, &CMugman::Jump);
	CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Push, this, &CMugman::Shoot);
	CInput::GetInst()->AddKeyCallback<CMugman>("Dash", KT_Down, this, &CMugman::Dash);


	// End CallBack Func
	CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Up, this, &CMugman::ShootEnd); 
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Up, this, &CMugman::MoveEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Up, this, &CMugman::MoveEnd);
	CInput::GetInst()->AddKeyCallback<CMugman>("Aim", KT_Up, this, &CMugman::AimEnd);
	//CInput::GetInst()->AddKeyCallback<CMugman>("MoveUp", KT_Up, this, &CMugman::MoveEnd);
	//CInput::GetInst()->AddKeyCallback<CMugman>("MoveDown", KT_Up, this, &CMugman::MoveEnd);


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

// 이동, 상태, 애니메이션 변경, 시간 등 실시간으로 계산해야 할 것들을 Update에서 처리
void CMugman::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	// Idle check
	AnimCheck(DeltaTime);

	// 점프
	JumpCheck(DeltaTime);

	if (m_bCanParry)
	{
		ParryCheck(DeltaTime);
	}

	// 땅이 아닐 경우 떨어지고 있는지 체크
	if (!m_bIsGround)
	{
		FallCheck(DeltaTime);
	}


	// 대쉬
	DashCheck(DeltaTime);

	// 시간 체크
	TimeCheck(DeltaTime);

	// 총구 루핑
	MuzzleLoopCheck(DeltaTime);
	
	// 플레이어 위치 저장
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

	//AddRelativePos(GetAxis(AXIS_Y) * m_Speed * DeltaTime);
}

void CMugman::MoveDown(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump || !m_bIsGround ||!m_bParrySuccess)
	{
		return;
	}

	//AddRelativePos(GetAxis(AXIS_Y) * -m_Speed * DeltaTime);
}

void CMugman::MoveRight(float DeltaTime)
{
	// 대시중이라면 키 입력을 받지 않는다.
	if (m_bIsDash || !m_bCanMove)
	{
		return;
	}

	// 이동과 동시에 애니메이션을 바꿔야 할 경우(다른 상태가 아닐 경우)
	// 점프 중이거나, 떨어지고 있거나 이미 달리던 중이였을 경우 애니메이션을 교체하지 않는다
	if (!m_bIsJump && !m_bIsFall && m_bIsMove &&!m_bParrySuccess)
	{
		// 공격중이면 공격하는 애님으로
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
	if (m_bIsDash || !m_bCanMove)
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
	// 점프 할 수 없는 상태라면 반환
	if (!m_bCanJump)
	{
		return;
	}

	// 땅에서 아래로 내려가려고 하는 경우
	if (m_bIsGround && (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		InAir();
		return;
	}

	// 점프가 가능한 경우
	m_bCanAttack = false;
	m_bCanJump = false;
	m_bCanAim = false;

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
	if (!m_bCanAttack || m_bIsDash || m_bIsFall || m_bIsJump)
	{
		return;
	}

	if (m_BulletCount > 0 )
	{
		--m_BulletCount;

		CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");

		// 공격중이였다면 Animation을 다시 바꾸지 않음.

		if (m_PrevDirection == Direction::RIGHT)
		{
			// 정지 사격일 경우
			if (!m_bIsMove)
			{
				m_Animation->ChangeAnimation("Mugman_Shoot_R");
			}

			pBullet->SetBulletDirection(Direction::RIGHT);
		}

		if (m_PrevDirection == Direction::LEFT)
		{
			Vector3 CurrentMuzzlePos = m_Muzzle->GetRelativePos();
			m_Muzzle->SetRelativePos(-CurrentMuzzlePos.x, CurrentMuzzlePos.y, CurrentMuzzlePos.z);

			if (!m_bIsMove)
			{
				m_Animation->ChangeAnimation("Mugman_Shoot_L");
			}

			pBullet->SetBulletDirection(Direction::LEFT);
		}

		pBullet->SetRelativePos(m_Muzzle->GetWorldPos());

		m_bCanAttack = false;
		m_bIsAttack = true;
	}

	
	//pBullet->SetRelativeRotation(GetWorldRotation());

}

void CMugman::Aim(float DeltaTime)
{
	if (!m_bCanAim)
	{
		return;
	}

	if (!m_bIsAiming)
	{
		if (m_PrevDirection == Direction::RIGHT)
		{
			m_Animation->ChangeAnimation("Mugman_Aim_R");
		}

		if (m_PrevDirection == Direction::LEFT)
		{
			m_Animation->ChangeAnimation("Mugman_Aim_L");
		}
	}
	
	m_bIsAiming = true;
}

void CMugman::Dash(float DeltaTime)
{
	// 대시가 가능한 상황인지 판단
	if (!m_bCanDash && !m_bIsDamaged && !m_bParrySuccess)
	{
		return;
	}

	// 가능하다면 점프중이거나 떨어지고 있는지 판단
	if (m_bIsJump)
	{
		JumpEnd();
	}

	m_bIsDash = true;
	m_bCanMove = false;
	m_bCanAttack = false;
	m_bCanDash = false;
	m_bCanJump = false;
	m_bCanAim = false;
	
	ResetPhysicsSimulate();
	SetPhysicsSimulate(true);

	// 원래 스프라이트 크기로 맞춰줌
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
	// 데미지를 입을 수 없는 상황이라면
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

	// 할 수 있는 행동 전부 막고 모든 상태를 즉시 종료함
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
}

void CMugman::MoveEnd(float DeltaTime)
{
	m_bIsMove = false;
	m_DustTime = 0.f;
}

void CMugman::AimEnd(float DeltaTime)
{
	m_bIsAiming = false;
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

	// 애니메이션이 종료되면 점프와 같은 상태로 되돌아간다. (완전한 종료는 아님 )
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
}

void CMugman::JumpCheck(float DeltaTime)
{
	if (m_bIsJump)
	{
		//m_bCanAttack = false;
		//y=-GA*V+b에서 (a: 중력가속도, b: 초기 점프속도)
		//적분 : y = (-GA/2)*t*t + (V*t) 공식을 얻는다.(t: 점프시간, y: 오브젝트의 높이)
		//변화된 높이 height를 기존 높이 m_posY에 더한다.

		m_JumpTime += GetGravityAccel() * DeltaTime;

		// 처음 뛸 경우 힘을 강하게 적용함.
		if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpVelocity) + (m_JumpAccel * m_JumpTime);
		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)*DeltaTime);

		m_JumpAccel -= GetGravityAccel() * DeltaTime;
	}

	// 점프 중이 아닐 경우
	else
	{
		JumpEnd();
	}
}

void CMugman::ParryCheck(float DeltaTime)
{
	// 패링 시간에 패링에 성공했을 경우
	if (m_bIsParry && m_bParrySuccess)
	{
		if (m_bIsJump)
		{
			JumpEnd();
		}

		m_ParryTime += GetGravityAccel() * DeltaTime;

		// 처음 뛸 경우 힘을 강하게 적용함.
	/*	if (m_ParryAccel == 70.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100.f);
		}*/

		float ParryHeight = (m_ParryTime * m_ParryTime * GetGravity() * -0.5f) + (m_ParryTime * m_ParryVelocity) + (m_ParryAccel * m_ParryTime);
		AddRelativePos(GetAxis(AXIS_Y) * (ParryHeight)*DeltaTime);

		m_ParryAccel -= GetGravityAccel() * DeltaTime;

		// 처음 위치보다 낮아지려고 할 경우 패링을 종료하고 Fall 상태로 전환함
	/*	if (m_StartY > GetRelativePos().y)
		{
			ParryEnd();
		}*/
	}
}

void CMugman::FallCheck(float DeltaTime)
{
	if (m_bIsDash || m_bIsDamaged)
	{
		return;
	}

	// 현재 떨어지고 있는 중이라면 (점프와는 다른 상태임)
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

		// 대시가 끝났다면 종료
		if (DashVelocity <= 0.f)
		{
			DashEnd();
		}
	}

}


void CMugman::JumpEnd()
{
	// 땅에 닿았을 시 점프 종료
	m_bIsJump = false;
	m_JumpVelocity = 50.f;
	m_JumpTime = 0.0f;
	m_JumpAccel = 90.f;
}

void CMugman::ParryEnd()
{
	// 땅에 닿았을 시 패링 종료.
	ResetParry();
}

void CMugman::ResetParry()
{
	m_bIsParry = false;
	m_bCanParry = false;
	m_bParrySuccess = false;

	m_ParryVelocity = 50.f;
	m_ParryTime = 0.f;
	m_ParryAccel = 70.f;
	m_ParryCheckTime = 0.f;
}

void CMugman::DashEnd()
{
	m_DashSpeed = 100.f;
	m_DashTime = 0.f;

	m_bIsDash = false;
	m_bCanJump = true;
	m_bCanMove = true;
	m_bCanAttack = true;
	m_bCanAim = true;


	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

	// 대시의 끝이 공중인지 체크
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

void CMugman::HitEnd()
{
	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

	m_bCanAim = true;
	m_bCanAttack = true;
	m_bCanDash = true;
	m_bCanMove = true;
	m_bCanJump = true;
	m_bCanDamaged = true;

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
	// 땅에 닿았을때 정지하거나 수행 가능한 모든 행동을 처리
	m_FallTime = 0.f;

	m_bIsFall = false;
	m_bIsJump = false;
	m_bIsGround = true;

	if (m_bIsParry)
	{
		ResetParry();
	}
	//m_bIsAttack = false;

	m_bCanJump = true;
	m_bCanAttack = true;
	m_bCanDash = true;
	m_bCanAim = true;
	
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
	// 게임이 아직 시작하지 않았다면 시간초를 재지 않게 끔 변경하기..
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

	// 패링 가능 시간중 패링에 성공하지 않았을 때만 남은 시간을 잰다.
	if (m_bIsParry && !m_bParrySuccess)
	{
		m_ParryCheckTime += DeltaTime;
	}

	// Check Time Condition
	// 60프레임 기준
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

	if (m_InvincibleTime >= 1.f)
	{
		InvincibleEnd();
		m_InvincibleTime = 0.f;
	}

	// 패링의 자동종료
	if (m_ParryCheckTime >= 1.0f)
	{
		m_bCanParry = false;
		m_bIsParry = false;
		m_bParrySuccess = false;
	}

}

void CMugman::AnimCheck(float DeltaTime)
{
	// 조금이라도 이동했다면 종료
	Vector2 PrevWorldPos = { GetPrevWorldPos().x , GetPrevWorldPos().y };
	Vector2 WorldPos = { GetWorldPos().x , GetWorldPos().y };

	if (!m_bIsAttack && !m_bIsDash && !m_bIsFall && !m_bIsJump && !m_bIsMove && !m_bIsDamaged && (!m_bIsParry && !m_bParrySuccess))
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
	// 코사인 함수로 반복
	// Move Y
	float MoveY = sin(PI * 2 / 30.f * m_Frame) * m_MuzzleMaxY;
	m_Muzzle->AddRelativePos(GetAxis(AXIS_Y) * MoveY * DeltaTime);
}

void CMugman::SavePlayerPos()
{
	PlayerPos = GetWorldPos();
	PlayerPrevPos = GetPrevWorldPos();

}

void CMugman::OnStepCloud(float MoveZ, float CloudY)
{
	// 점프중일때는 구름에 타지않음
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
	// 떨어지기 시작할때
	m_bIsFall = true;
	m_bIsJump = false;
	m_bIsGround = false;
	m_bIsAttack = false;
	m_bIsAiming = false;

	m_bCanAttack = false;
	m_bCanJump = false;
	m_bCanAim = false;

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



void CMugman::CollisionBegin(const HitResult& result, CCollider* Collider)
{	
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		CStepCloud* pStepCloud = (CStepCloud*)result.DestCollider->GetOwner();

		// 올라가고 있는 중이라면 충돌하지 않음
		if (m_bIsJump && GetWorldPos().y > GetPrevWorldPos().y)
		{
			SetUseBlockMovement(false);
			return;
		}

		// 구름보다 내 위치가 더 높을때만 움직임 닿은것으로 판단.
		if (pStepCloud->GetWorldPos().y < GetWorldPos().y)
		{
			OnStepCloud(pStepCloud->GetMoveDistance(), pStepCloud->GetWorldPos().y);
			OnGround();
		}
	}

	// 낙사 방지용 콜리전
	if (result.DestCollider->GetName() == "GroundCollider")
	{
		OnGround();
	}

	// 용 충돌 버그..
	if (result.DestCollider->GetName() == "DragonCollider")
	{
		/*Vector3 CurrentWorldPos = GetWorldPos();
		SetWorldPos(GetPrevWorldPos().x, CurrentWorldPos.y, CurrentWorldPos.z);*/

		if (!m_bIsGround)
		{
			InAir();
		}
	}

	// 충돌체 종류가 스킬이고 무적이 아닐 경우
	if (result.DestCollider->GetProfile()->Name == "Skill" && m_bCanDamaged)
	{
		//Hit();
	}

	// 충돌체 종류가 스킬이고 무적이 아닐 경우
	if (result.DestCollider->GetProfile()->Name == "Parry")
	{
		m_bCanParry = true;
	}
}

void CMugman::CollisionOverlap(const HitResult& result, CCollider* Collider)
{
	// 구름 콜리전과 닿았을때 캐릭터 콜리전을 이동시킴
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		CStepCloud* pStepCloud = (CStepCloud*)result.DestCollider->GetOwner();
		OnStepCloud(pStepCloud->GetMoveDistance(), pStepCloud->GetWorldPos().y);
	}

	if (result.DestCollider->GetName() == "GroundCollider")
	{
		//m_bIsGround = true;
	}

	// 충돌 중에만 패링을 감지한다
	if (result.DestCollider->GetProfile()->Name == "Parry")
	{
		// 이미 패링을 했다면 
		if (m_bParrySuccess)
		{
			return;
		}

		if (m_bCanParry)
		{
			m_bIsParry = true;

			// 만약 점프가 눌린 상태라면 패링을 실행한다
			if (GetAsyncKeyState('Z') & 0x8000)
			{
				Parry();
			}
		}

		// 충돌 중이나 패링 가능 시간이 종료 됐을 경우 피격 체크
		if (!m_bCanParry && !m_bIsParry && !m_bParrySuccess)
		{
			ParryEnd();
			Hit();
		}
	}
}

void CMugman::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	// 점프중이 아니라면 떨어지는 것으로 간주.
	if (result.DestCollider->GetName() == "StepCloudCollider")
	{
		if (!m_bIsJump && GetWorldPos().y  > result.DestCollider->GetWorldPos().y)
		{
			InAir();
		}
	}

	// 닿았다 떨어질 경우 패링 불가 상태로 간주하고 관련된 값을 초기화
	if (!m_bParrySuccess && result.DestCollider->GetProfile()->Name == "Parry")
	{
		//ResetParry();
	}
}



