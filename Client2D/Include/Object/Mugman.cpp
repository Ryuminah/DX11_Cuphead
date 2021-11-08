#include "Mugman.h"
#include "../Animation2D/MugmanAnimation2D.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"

CMugman::CMugman() :
	m_ChildFire(false),
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
	m_State(Mugman_State::Idle)
	
{

}

CMugman::CMugman(const CMugman& obj) : CFightObject(obj)
{
	m_ChildFire = false;

	m_Sprite = (CSpriteComponent*)FindSceneComponent("Mugman");
	m_Collider = (CColliderBox2D*)FindSceneComponent("MugmanCollider");
	m_Rotation = FindSceneComponent("Rotation");
	m_Muzzle = FindSceneComponent("Muzzle");
	m_LeftMuzzle = FindSceneComponent("LeftMuzzle");
	m_RightMuzzle = FindSceneComponent("RightMuzzle");
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

	m_LeftMuzzle = CreateSceneComponent<CSceneComponent>("LeftMuzzle");
	m_RightMuzzle = CreateSceneComponent<CSceneComponent>("RightMuzzle");
	

	//m_Arm = CreateSceneComponent<CSpringArm2D>("Arm");
	//m_Camera = CreateSceneComponent<CCamera>("Camera");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);
	m_Sprite->SetRelativePos(640.f, 100.f, 0.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	//m_Sprite->SetPivot(0.5f, 0.f, 0.f);


	m_Collider->SetExtent(45.f, 70.f);
	m_Collider->SetCollisionProfile("Player");

	m_Sprite->AddChild(m_Collider);

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

	// 프레임 종료 콜백 설정

	m_Sprite->AddChild(m_Rotation);
	m_Sprite->AddChild(m_Muzzle);

	m_Muzzle->SetInheritRotZ(true);
	m_Muzzle->SetRelativePos(Vector3(0.f, 75.f, 0.f));
	m_Muzzle->SetPivot(0.5f, 0.f, 0.f);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);


	m_LeftMuzzle->SetInheritRotZ(true);
	m_LeftMuzzle->SetRelativePos(Vector3(0.f, 50.f, 0.f));
	m_LeftMuzzle->SetPivot(0.5f, 0.5f, 0.f);


	m_RightMuzzle->SetInheritRotZ(true);
	m_RightMuzzle->SetRelativePos(Vector3(0.f, 50.f, 0.f));
	m_RightMuzzle->SetPivot(0.0f, 0.0f, 0.f);

	CInput::GetInst()->AddKeyCallback<CMugman>("MoveUp", KT_Push, this, &CMugman::MoveUp);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveDown", KT_Push, this, &CMugman::MoveDown);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveRight", KT_Push, this, &CMugman::MoveRight);
	CInput::GetInst()->AddKeyCallback<CMugman>("MoveLeft", KT_Push, this, &CMugman::MoveLeft);
	CInput::GetInst()->AddKeyCallback<CMugman>("Jump", KT_Down, this, &CMugman::Jump);
	CInput::GetInst()->AddKeyCallback<CMugman>("Shoot", KT_Push, this, &CMugman::Shoot);
	CInput::GetInst()->AddKeyCallback<CMugman>("Dash", KT_Down, this, &CMugman::Dash);

	SetDefaultZ(0.1f);
	SetPhysicsSimulate(false);

	return true;
}

void CMugman::Update(float DeltaTime)
{
	CFightObject::Update(DeltaTime);


	// 점프 중일 경우
	if (m_bIsJump)
	{
		//y=-GA*V+b에서 (a: 중력가속도, b: 초기 점프속도)
		//적분 : y = (-GA/2)*t*t + (V*t) 공식을 얻는다.(t: 점프시간, y: 오브젝트의 높이)
		//변화된 높이 height를 기존 높이 m_posY에 더한다.
		
		m_JumpTime += GetGravityAccel() * DeltaTime;

			// 처음 뛸 경우 힘을 강하게 적용함.
		if (m_JumpAccel == 90.f)
		{
			AddRelativePos(GetAxis(AXIS_Y) * 100);
		}

		float jumpHeight = (m_JumpTime * m_JumpTime * GetGravity() * -0.5f) + (m_JumpTime * m_JumpVelocity) + (m_JumpAccel* m_JumpTime);
		AddRelativePos(GetAxis(AXIS_Y) * (jumpHeight)* DeltaTime);
		
		m_JumpAccel -= GetGravityAccel() * DeltaTime;

		// 점프가 끝났을 경우
		if (GetRelativePos().y <= m_PosY)
		{ 
			JumpEnd();
			SetPhysicsSimulate(false);

			// 높이 원래대로 되돌려줌
			SetRelativePos(GetRelativePos().x, m_PosY, GetRelativePos().z);
			if (m_Direction == Direction::RIGHT)
			{
				m_Animation->ChangeAnimation("Mugman_Idle_R");

			}

			if (m_Direction == Direction::LEFT)
			{
				m_Animation->ChangeAnimation("Mugman_Idle_L");
			}
		}
	}

	// 대쉬 중일 경우
	if (m_bIsDash)
	{
		m_DashTime += GetGravityAccel() * DeltaTime;

		float DashVelocity = (m_DashTime * m_DashTime * GetGravity() * -0.5) + (m_DashSpeed * m_DashTime);

		if (m_Direction == Direction::RIGHT)
		{
			AddRelativePos(GetAxis(AXIS_X) * (m_Speed + DashVelocity) * DeltaTime);
		}

		if (m_Direction == Direction::LEFT)
		{
			AddRelativePos(GetAxis(AXIS_X) * -(m_Speed + DashVelocity) * DeltaTime);
		}

		m_DashSpeed -= GetGravityAccel() * DeltaTime;

		if (DashVelocity <= 0.f)
		{
			DashEnd();
			SetPhysicsSimulate(false);

			m_Sprite->SetRelativeScale(200.f, 200.f, 1.f);

			if (m_Direction == Direction::RIGHT)
			{
				m_Animation->ChangeAnimation("Mugman_Idle_R");
			}

			if (m_Direction == Direction::LEFT)
			{
				m_Animation->ChangeAnimation("Mugman_Idle_L");
			}

			m_State = Mugman_State::Idle;
		}
	}


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
	AddRelativePos(GetAxis(AXIS_Y) * m_Speed * DeltaTime);
}

void CMugman::MoveDown(float DeltaTime)
{
	if (m_bIsDash || m_bIsJump)
	{
		return;
	}

	AddRelativePos(GetAxis(AXIS_Y) * -m_Speed * DeltaTime);
}

void CMugman::MoveRight(float DeltaTime)
{
	// 점프 중이라면 애니메이션을 교체하지 않는다.
	// 대시중이라면 키 입력을 받지 않는다.
	if (m_bIsDash)
	{
		return;
	}

	m_State = Mugman_State::Run;
	m_Direction = Direction::RIGHT;

	if (!m_bIsJump)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_R");
	}

	AddRelativePos(GetAxis(AXIS_X)* m_Speed* DeltaTime);

}

void CMugman::MoveLeft(float DeltaTime)
{
	if (m_bIsDash)
	{
		return;
	}

	m_State = Mugman_State::Run;
	m_Direction = Direction::LEFT;
	
	// 점프중이 아닐 때만
	if (!m_bIsJump)
	{
		m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
	}
	AddRelativePos(GetAxis(AXIS_X) * -m_Speed * DeltaTime);
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
	m_bCanJump = false;
	m_bIsJump = true;
	m_bIsGround = false;
	SetPhysicsSimulate(true);

	if (m_Direction == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Jump_R");

	}

	if (m_Direction == Direction::LEFT)
	{
		m_Animation->ChangeAnimation("Mugman_Jump_L");
	}

}

void CMugman::Shoot(float DeltaTime)
{
	bIsAttack = true;
	m_Animation->ChangeAnimation("Mugman_Shoot_R");
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
		// 점프중이라면 점프를 즉시 종료.
		JumpEnd();
	}

	m_State = Mugman_State::Dash;
	m_bIsDash = true;
	m_bCanDash = false;
	m_bCanJump = false;
	SetPhysicsSimulate(true);
	m_Sprite->SetRelativeScale(330.f, 330.f, 1.f);

	if (m_Direction == Direction::RIGHT)
	{
		m_Animation->ChangeAnimation("Mugman_Dash_R");
	}

	if (m_Direction == Direction::LEFT)
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
	// 현재 애니메이션이 Dash일 경우
}

void CMugman::CheckJump()
{
	// 땅일때만 점프 가능.
	/*if (!bIsGround)
	{
		m_Animation->ChangeAnimation("Mugman_Jump_R");
	}

	AddRelativePos(GetAxis(AXIS_Y) * 5 * 10);*/
}

void CMugman::JumpEnd()
{
	m_State = Mugman_State::Idle;
	m_bIsGround = true;
	m_bCanJump = true;
	m_bIsJump = false;
	m_JumpVelocity = 50.f;
	m_JumpTime = 0.0f;
	m_JumpAccel = 90.f;
}

void CMugman::DashEnd()
{
	m_State = Mugman_State::Idle;
	m_bIsDash = false;
	m_bCanDash = true;
	m_bCanJump = true;
	m_DashSpeed = 80.f;
	m_DashTime = 0.f;
}

void CMugman::ChangeAnimDirection()
{
	if (m_Direction == Direction::RIGHT)
	{
		switch (m_State)
		{
		case Mugman_State::Idle:
			m_Animation->ChangeAnimation("Mugman_Idle_R");
			break;

		case Mugman_State::Dash:
			m_Animation->ChangeAnimation("Mugman_Dash_R");
			break;

		case Mugman_State::Jump:
			m_Animation->ChangeAnimation("Mugman_Jump_R");
			break;

		case Mugman_State::Run:
			m_Animation->ChangeAnimation("Mugman_Run_Shoot_R");
			break;
		}
	}

	if (m_Direction == Direction::LEFT)
	{
		switch (m_State)
		{
		case Mugman_State::Idle:
			m_Animation->ChangeAnimation("Mugman_Idle_L");
			break;

		case Mugman_State::Dash:
			m_Animation->ChangeAnimation("Mugman_Dash_L");
			break;

		case Mugman_State::Jump:
			m_Animation->ChangeAnimation("Mugman_Jump_L");
			break;

		case Mugman_State::Run:
			m_Animation->ChangeAnimation("Mugman_Run_Shoot_L");
			break;
		}
	}
}



