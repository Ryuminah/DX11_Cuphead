#include "BG_DragonMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround_CloudAnim.h"

bool BG_CDragonMap::bIsNight = false;

BG_CDragonMap::BG_CDragonMap()
{

}

BG_CDragonMap::BG_CDragonMap(const BG_CDragonMap& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_DragonMap");
}

BG_CDragonMap::~BG_CDragonMap()
{
}

void BG_CDragonMap::Start()
{
	CBackGround::Start();

	//UV Flow
	// FG : Direction(true)	BG : Direction (false)
	m_Sprite->SetAnimation2DEnable(false);
	m_Sprite->SetUVFlow2DEnable(true);
	m_Sprite->SetUVFlow2DSpeed(0.05f);
	m_Sprite->SetUVFlow2DDirection(false);
}

bool BG_CDragonMap::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_DragonMap");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.0f, 0.0f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 720.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
	
	m_Sprite->CreateAnimation2D<CBackGround_CloudAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("BG_Normal_DragonMap");

	return true;
}

void BG_CDragonMap::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void BG_CDragonMap::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void BG_CDragonMap::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_CDragonMap::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_CDragonMap* BG_CDragonMap::Clone()
{
	return new BG_CDragonMap(*this);
}
