#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/BG_KettleHouseAnim.h"
#include "BG_KettleHouse.h"

BG_KettleHouse::BG_KettleHouse()
{

}

BG_KettleHouse::BG_KettleHouse(const BG_KettleHouse& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_KettleHouse");
	m_FG_KettleHouse = (CSpriteComponent*)FindSceneComponent("FG_KettleHouse");

}

BG_KettleHouse::~BG_KettleHouse()
{
}

void BG_KettleHouse::Start()
{
	CBackGround::Start();
}

bool BG_KettleHouse::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_KettleHouse");
	m_FG_KettleHouse = CreateSceneComponent<CSpriteComponent>("FG_KettleHouse");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_FG_KettleHouse);

	m_Sprite->SetRelativePos(640.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 629.f, 1.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Sprite->CreateAnimation2D<BG_KettleHouseAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("BG_KettleHouse");

	// FG_KettleHouse Sprite
	m_FG_KettleHouse->SetRelativePos(0.f, 0.f, 0.f);
	m_FG_KettleHouse->SetRelativeScale(1280.f, 629.f, 1.f);
	m_FG_KettleHouse->SetRender2DType(Render_Type_2D::RT2D_Particle);

	m_FG_KettleHouse->CreateAnimation2D<BG_KettleHouseAnim>();
	m_FG_KettleHouseImage = m_FG_KettleHouse->GetAnimation2D();
	m_FG_KettleHouseImage->ChangeAnimation("FG_KettleHouse");

	return true;
}

void BG_KettleHouse::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void BG_KettleHouse::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void BG_KettleHouse::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_KettleHouse::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_KettleHouse* BG_KettleHouse::Clone()
{
	return new BG_KettleHouse(*this);
}
