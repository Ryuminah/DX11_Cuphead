#include "Meteor.h"
#include "../Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Dragon.h"

Vector3	CMeteor::StartPosition = Vector3(0.f, 0.f, 0.f);

CMeteor::CMeteor() : m_WaitTime(2.f),
		m_TimeToFrame(0.f),
	m_MinY(0.f), m_MaxY(720.f), m_Frame(0.f)
{

}

CMeteor::CMeteor(const CMeteor& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Rotation = FindSceneComponent("Rotation");
}

CMeteor ::~CMeteor()
{

}

void CMeteor::Start()
{
	CSkill::Start();
}

bool CMeteor::Init()
{
	CSkill::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Meteor");
	m_Collider = CreateSceneComponent<CColliderBox2D>("MeteorCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(240.f, 240.f, 1.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);

	m_Collider->SetExtent(30.f, 30.f);
	m_Collider->SetCollisionProfile("Skill");
	m_Collider->SetColliderType(Collider_Type::Static);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_Meteor");

	//m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimationFrameEnd);

	SetUseBlockMovement(false);
	SetDefaultZ(0.1f);

	return true;
}

void CMeteor::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);
}

void CMeteor::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CMeteor::Collision(float DeltaTime)
{
	CSkill::Collision(DeltaTime);
}

void CMeteor::Render(float DeltaTime)
{
	CSkill::Render(DeltaTime);
}

CMeteor* CMeteor::Clone()
{
	return new CMeteor(*this);
}


void CMeteor::SkillStart(float DeltaTime)
{
	// 시작할때 필요한 설정
	++RepeatCount;
	m_bIsStarted = true;
}

void CMeteor::SkillActive(float DeltaTime)
{
	Vector3 MoveDistance = Vector3(0.f, 0.f, 0.f);		

	// Move Y
	if (m_TimeToFrame >= 0.1f)
	{
		++m_Frame;
		m_TimeToFrame = 0.f;
	}

	// 삼각함수로 반복
	m_TimeToFrame += DeltaTime;
	m_MoveY = cos(PI * 2 /30.f *m_Frame) * 720;

	AddRelativePos(GetAxis(AXIS_Y) * m_MoveY * DeltaTime);
	
	// MoveX
	Vector3 LastPosition = { -100.f ,0.f,0.f };
	Vector3 StartPosition = { CMeteor::StartPosition.x  , 0.f, 0.f };
	Vector3 MoveX = Lerp2D(LastPosition, StartPosition, m_MoveTime * DeltaTime * 0.35f);
	MoveX.x = MoveX.x * DeltaTime * -0.35f;
	AddRelativePos(GetAxis(AXIS_X) * MoveX);
	
	m_MoveTime += DeltaTime;

	// Rotation 이건 나중에 ,,
	/*Vector3 vStart = (GetPrevWorldPos() * GetAxis(AXIS_X)) * -1.f;
	Vector3 vTarget = GetRelativePos() - GetPrevWorldPos();

	float Angle = vStart.Angle(vTarget);
	AddRelativeRotationZ(Angle* DeltaTime);*/
	//m_Sprite->GetMaterial(0)->SetOpacity(1.f);
	
}

void CMeteor::SkillEnd(float DeltaTime)
{
	// 반복횟수가 남았다면
	if (RepeatCount != RepeatNumber)
	{
		CDragon* pDragon = (CDragon*)m_pSkillOwner;
		pDragon->ChangeAnimation("Dragon_Meteor_Start");
	}

	// 반복횟수가 남지 않았을때만 완전종료함수를 호출한다.
	else if (RepeatCount == RepeatNumber)
	{
		m_pSkillOwner->SkillEnd(GetName());
		m_bIsEnd = false;
	}

}


