#include "BG_TutorialMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Character/Mugman.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"
#include "Scene/CameraManager.h"

BG_TutorialMap::BG_TutorialMap()
{

}

BG_TutorialMap::BG_TutorialMap(const BG_TutorialMap& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_TutorialMap");
}

BG_TutorialMap::~BG_TutorialMap()
{
}

void BG_TutorialMap::Start()
{
	CBackGround::Start();;
}

bool BG_TutorialMap::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_TutorialMap");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.0f, 0.0f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(6730.f, 720.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Sprite->CreateAnimation2D<CTutorialSceneAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("TutorialMap");

	//CreateCollision();
	SetUseBlockMovement(false);

	return true;
}

void BG_TutorialMap::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);

}

void BG_TutorialMap::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);

	//if (CMugman::PlayerPos.x < 640.f || CMugman::PlayerPos.x >= 6090.f)
	//{
	//	return;
	//}

	//float MoveDistanceX = (CMugman::PlayerPos.x - CMugman::PlayerPrevPos.x);
	//Vector3 CameraPos = m_pScene->GetCameraManager()->GetCurrentCamera()->GetWorldPos();
	//if (MoveDistanceX != 0.f)
	//{
	//	m_pScene->GetCameraManager()->GetCurrentCamera()->AddRelativePos(MoveDistanceX, 0.f, 0.f);

	//}
}

void BG_TutorialMap::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_TutorialMap::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_TutorialMap* BG_TutorialMap::Clone()
{
	return new BG_TutorialMap(*this);
}

void BG_TutorialMap::CreateCollision()
{
	m_Jump = CreateSceneComponent<CColliderBox2D>("Jump");
	m_Jump->SetExtent(45.f, 70.f);
	m_Jump->SetRelativePos(1580.f, 120.f, 0.f);
	m_Jump->SetCollisionProfile("Static");
	m_Jump->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Jump);


	m_Descend = CreateSceneComponent<CColliderBox2D>("Descend");
	m_Descend->SetExtent(45.f, 70.f);
	m_Descend->SetRelativePos(2300.f, 120.f, 0.f);
	m_Descend->SetCollisionProfile("Static");
	m_Descend->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Descend);

	m_ParryBox = CreateSceneComponent<CColliderBox2D>("ParryBox");
	m_ParryBox->SetExtent(45.f, 70.f);
	m_ParryBox->SetRelativePos(4860.f, 120.f, 0.f);
	m_ParryBox->SetCollisionProfile("Static");
	m_ParryBox->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_ParryBox);
}
