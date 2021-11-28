#include "StepCloud.h"
#include "../../Animation2D/StepCloudAnimation.h"
#include "../Character/Mugman.h"


CStepCloud::CStepCloud() :m_MoveTime(0.f), m_MoveDistance(0.f),
						m_bIsPlayerOn(false)
{

}

CStepCloud::CStepCloud(const CStepCloud& obj) : CGameObject(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("StepCloudCollider");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("StepCloud");

}

CStepCloud::~CStepCloud()
{
}

float CStepCloud::GetMoveDistance()
{
	return m_MoveDistance;
}

void CStepCloud::Start()
{
	CGameObject::Start();
	m_FirstPosition = GetRelativePos();

}

bool CStepCloud::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("StepCloud");
	m_Collider = CreateSceneComponent<CColliderBox2D>("StepCloudCollider");
	
	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(250.f, 75.f, 1.f);

	m_Collider->SetPivot(0.5f,0.f,0.f);
	m_Collider->SetRelativePos(0.f, 19.f, 0.f);

	m_Collider->SetExtent(90.f, 10.f);
	m_Collider->SetCollisionProfile("Static");
	m_Collider->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Collider);
	
	m_Sprite->CreateAnimation2D<CStepCloudAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CStepCloud>(this, &CStepCloud::AnimationFrameEnd);


	m_Collider->AddCollisionCallbackFunction<CStepCloud>(Collision_State::Begin, this, &CStepCloud::CollisionBegin);
	m_Collider->AddCollisionCallbackFunction<CStepCloud>(Collision_State::Overlap, this, &CStepCloud::CollisionOverlap);
	m_Collider->AddCollisionCallbackFunction<CStepCloud>(Collision_State::End, this, &CStepCloud::CollisionEnd);


	SetUseBlockMovement(false);
	SetDefaultZ(0.6f);

	return true;
}

void CStepCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	// 현재 위치
	Vector3 CurrentPos = GetRelativePos();
	Vector3 LastPosition = { -125.f, 0.f,0.f };

	// 현재 위치가 최종 위치까지 도달하지 않으면
	if (CurrentPos.x >= -125.f)
	{
		Vector3 MoveDistance = Lerp2D(LastPosition, { 1375.f,0.f,0.f }, m_MoveTime * DeltaTime * 0.1f);
		m_MoveDistance = MoveDistance.x * DeltaTime * 0.1f;
		AddRelativePos(-m_MoveDistance, 0.f, 0.f);
	}

	else
	{
		m_MoveTime = 0.f;
		SetRelativePos(1375.f, m_FirstPosition.y, CurrentPos.z);
	}

	m_MoveTime += DeltaTime * 0.1f;

}

void CStepCloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CStepCloud::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CStepCloud::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CStepCloud* CStepCloud::Clone()
{
	return new CStepCloud(*this);
}

void CStepCloud::Animation2DNotify(const std::string& Name)
{
	CGameObject::Animation2DNotify(Name);
}

void CStepCloud::AnimationFrameEnd(const std::string& Name)
{
	if (Name == "Cloud_Up" && !m_bIsPlayerOn)
	{
		m_Animation->ChangeAnimation("Cloud_Idle");

	}
}

void CStepCloud::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (GetWorldPos().y <= CMugman::PlayerPos.y)
	{
		m_Animation->ChangeAnimation("Cloud_Down_Idle");
		m_bIsPlayerOn = true;
	}
}

void CStepCloud::CollisionOverlap(const HitResult& result, CCollider* Collider)
{
	// 캐릭터 콜리전과 닿았을때 캐릭터 콜리전을 이동시키고, 키입력이 들어왔을 시 리턴.
	//if (result.DestCollider->GetName() == "MugmanCollider")
	//{
	//	CMugman* pMugman = (CMugman*)result.DestCollider->GetOwner();
	//	pMugman->OnStepCloud(m_MoveDistance, GetWorldPos().y);
	//}
}

void CStepCloud::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetName() == "MugmanCollider")
	{
		m_Animation->ChangeAnimation("Cloud_Up");
		m_bIsPlayerOn = false;
	}
}
