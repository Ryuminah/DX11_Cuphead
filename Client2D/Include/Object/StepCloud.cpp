#include "StepCloud.h"
#include "../Animation2D/StepCloudAnimation.h"


CStepCloud::CStepCloud() 
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

void CStepCloud::Start()
{
	CGameObject::Start();
}

bool CStepCloud::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("StepCloud");
	m_Collider = CreateSceneComponent<CColliderBox2D>("StepCloudCollider");
	m_TestCollider = CreateSceneComponent<CColliderBox2D>("StepCloudCollider");
	
	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(250.f, 250.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);
	m_Sprite->SetRelativePos(800.f, 400.f, 0.f);
	
	m_Collider->SetExtent(100.f, 20.f);
	m_Collider->SetPivot(0.5f, 0.5f, 0.f);
	m_Collider->SetCollisionProfile("Static");
	m_Collider->SetColliderType(Collider_Type::Static);


	m_TestCollider->SetExtent(640.f, 20.f);
	m_TestCollider->SetPivot(0.0f, 0.0f, 0.f);
	m_TestCollider->SetRelativePos(-800.f,-400.f,0.f);
	m_TestCollider->SetCollisionProfile("Static");
	m_TestCollider->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_TestCollider);
	


	m_Sprite->CreateAnimation2D<CStepCloudAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	//m_Animation->SetFrameEndFunction<CStepCloud>(this, &CStepCloud::AnimationFrameEnd);


	m_Collider->AddCollisionCallbackFunction<CStepCloud>(Collision_State::Begin, this, &CStepCloud::CollisionBegin);


	return true;
}

void CStepCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
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

}

void CStepCloud::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	m_Animation->ChangeAnimation("Cloud_Down_Idle");
}
