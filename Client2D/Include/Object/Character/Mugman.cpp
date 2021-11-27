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

	// 땅이 아닐 경우 떨어지고 있는지 체크
	if (!m_bIsGround)
	{
		FallCheck(DeltaTime);
	}

	// 점프
	JumpCheck(DeltaTime);

	// 대쉬
	DashCheck(DeltaTime);

	// 시간 체크
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
	// 점프 중이라면 애니메이션을 교체하지 않는다.
	// 대시중이라면 키 입력을 받지 않는다.
	if (m_bIsDash || !m_bCanMove)
	{
		return;
	}

	m_State = Mugman_State::Run;

	// 이미 공격중일 때는 Anim이 다시 처음부터 재생하면 안되므로 예외 처리.
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
	
	// 점프중이 아닐 때만
	if (!m_bIsJump && m_bIsGround)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
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

	// 점프가 가능한 경우
	m_State = Mugman_State::Jump;
	m_PosY = GetRelativePos().y; // 처음 Y를 저장
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

		// 공격중이였다면 Animation을 다시 바꾸지 않음.

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
	// 대시가 가능한 상황인지 판단
	if (!m_bCanDash)
	{
		return;
	}

	// 가능하다면 점프중이거나 떨어지고 있는지 판단
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
	// 현재 애니메이션이 Dash일 경우
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

void CMugman::OnGround()
{
	// 땅에 닿았을때 정지하거나 수행 가능한 모든 행동을 처리
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

	// 조금이라도 이동했다면 종료
	Vector2 PrevWorldPos = { GetPrevWorldPos().x , GetPrevWorldPos().y };
	Vector2 WorldPos = { GetWorldPos().x , GetWorldPos().y };

	// 움직였다면
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
	// 점프중일때는 구zz름z에z z타zzzzz지않zz음
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
}



