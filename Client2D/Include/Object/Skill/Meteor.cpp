#include "Meteor.h"
#include <time.h>
#include "../Character/Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Character/Dragon.h"
#include "../Effect/MeteorSmoke.h"
#include "Scene/SceneResource.h"

Vector3	CMeteor::StartPosition = Vector3(0.f, 0.f, 0.f);
Direction CMeteor::LastDirection = Direction::DOWN;
bool	CMeteor::bIsDouble = true;

CMeteor::CMeteor() : m_SmokeTime(0.1f),
		m_TimeToFrame(0.f),
	m_MinY(0.f), m_MaxY(720.f), m_Frame(0.f),
	m_CurrentDirection(LastDirection)
{

}

CMeteor::CMeteor(const CMeteor& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("Meteor");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("MeteorCollider");
	m_Rotation = FindSceneComponent("Rotation");
}

CMeteor ::~CMeteor()
{
	m_pScene->GetResource()->SoundStop("sfx_dragon_meteor_loop");
}

void CMeteor::Start()
{
	CSkill::Start();
	StartPosition = GetWorldPos();
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

	m_Collider->SetExtent(80.f, 80.f);
	m_Collider->SetCollisionProfile("Skill");
	m_Collider->SetColliderType(Collider_Type::Static);

	//m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_Meteor");
	m_pScene->GetResource()->SoundPlay("sfx_dragon_meteor_attack");

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
	srand((unsigned int)time(NULL));

	// Set Y Direction Random
	// ���� ó�� ����� ������ ������ ������, �ƴ� ��쿡�� ������ �ݴ� �������� ������ �Ѵ�.
	if (RepeatCount == 0)
	{
		int YDirection = rand() % 2;
		LastDirection = YDirection == 0 ? Direction::UP : Direction::DOWN;
	}

	else
	{
		if (LastDirection == Direction::UP) { LastDirection = Direction::DOWN; }
		else { LastDirection = Direction::UP; }
	}

	//�ݺ�Ƚ���� 2���� ũ��, ¦����� Double��
	if (TotalRepeatNumber >= 2 && (TotalRepeatNumber - RepeatCount) % 2 == 0 )
	{
		int IsDouble = rand() % 2;
		bIsDouble = IsDouble;
	}

	// ���׿� �ϳ��� �ݺ�Ƚ���� ����
	++RepeatCount;
	m_bIsStarted = true;
	m_CurrentDirection = LastDirection;

	m_pScene->GetResource()->SoundPlay("sfx_dragon_meteor_loop");

}

void CMeteor::SkillActive(float DeltaTime)
{
	Vector3 MoveDistance = Vector3(0.f, 0.f, 0.f);		

	// �ð� �� �������� ���
	if (m_TimeToFrame >= 0.1f)
	{
		++m_Frame;
		m_TimeToFrame = 0.f;
	}

	if (m_SmokeTime  <= 0.0f)
	{
		m_SmokeTime = 0.1f;
		CMeteorSmoke* pMeteorSmoke = m_pScene->SpawnObject<CMeteorSmoke>("MeteorSmoke");
		pMeteorSmoke->SetRelativePos(GetPrevWorldPos());
	}

	if (bIsDouble)
	{
		// ������ ������ �ϴ� ��� ���׿��� �ϳ� �� ����
		bIsDouble = false;
		CMeteor* pMeteor = m_pScene->SpawnObject<CMeteor>("Meteor");
		pMeteor->SetRelativePos(StartPosition);
		pMeteor->SetIsActive(true);
		pMeteor->SetSkillOwner(m_pSkillOwner);
	}

	// �ڻ��� �Լ��� �ݺ�
	// Move Y
	m_TimeToFrame += DeltaTime;
	float MoveY = cos(PI * 2 / 30.f * m_Frame) * m_MaxY;
	MoveY = m_CurrentDirection == Direction::UP ? MoveY * 1.f : MoveY * -1.f;
	AddRelativePos(GetAxis(AXIS_Y) * MoveY * DeltaTime);
	
	// MoveX
	Vector3 LastPosition = { -100.f ,0.f,0.f };
	Vector3 StartPosition = { CMeteor::StartPosition.x  , 0.f, 0.f };
	Vector3 MoveX = Lerp2D(LastPosition, StartPosition, m_MoveTime * DeltaTime * 0.37f);
	MoveX.x = MoveX.x * DeltaTime * -0.37f;
	AddRelativePos(GetAxis(AXIS_X) * MoveX);
	
	m_SmokeTime -= DeltaTime;
	m_MoveTime += DeltaTime;

	// Rotation �̰� ���߿� ,,
	/*Vector3 vStart = (GetPrevWorldPos() * GetAxis(AXIS_X)) * -1.f;
	Vector3 vTarget = GetRelativePos() - GetPrevWorldPos();

	float Angle = vStart.Angle(vTarget);
	AddRelativeRotationZ(Angle* DeltaTime);*/
	//m_Sprite->GetMaterial(0)->SetOpacity(1.f);
	
}

void CMeteor::SkillEnd(float DeltaTime)
{
	// �ݺ�Ƚ���� ���Ҵٸ�
	if (RepeatCount != TotalRepeatNumber)
	{
		CDragon* pDragon = (CDragon*)m_pSkillOwner;
		pDragon->ChangeAnimation("Dragon_Meteor_Start");
	}

	// �ݺ�Ƚ���� ���� �ʾ������� ���������Լ��� ȣ���Ѵ�.
	else if (RepeatCount == TotalRepeatNumber)
	{
		m_pSkillOwner->SkillEnd(GetName());
		m_bIsEnd = false;
	}


}


