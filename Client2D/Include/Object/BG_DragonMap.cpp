#include "BG_DragonMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

BG_CDragonMap::BG_CDragonMap()
{

}

BG_CDragonMap::BG_CDragonMap(const BG_CDragonMap& obj) :
	CGameObject(obj)
{
	m_BackGround = (CSpriteComponent*)FindSceneComponent("DragonMap");
}

BG_CDragonMap::~BG_CDragonMap()
{
}

void BG_CDragonMap::Start()
{
	CGameObject::Start();
}

bool BG_CDragonMap::Init()
{
	CGameObject::Init();

	m_BackGround = CreateSceneComponent<CSpriteComponent>("DragonMap");

	SetRootComponent(m_BackGround);
	m_BackGround->SetPivot(0.0f, 0.0f, 0.0f);
	m_BackGround->SetRelativePos(0.f, 0.0f, 0.f);
	m_BackGround->SetRelativeScale(1280.f, 720.f, 1.f);
	m_BackGround->SetMaterial(0,"BG_Normal");

	//UV Flow
	m_BackGround->SetAnimation2DEnable(false);
	m_BackGround->SetUVFlow2DEnable(true);
	m_BackGround->SetUVFlow2DSpeed(0.05f);
	m_BackGround->SetUVFlow2DDirection(false);

	m_BackGround->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_BackGround->SetAnimation2DEnable(false);
	//m_BackGround->SetUVFlow2DEnable(true);

	//m_BackGround->SetUVFlow2DEnable(true);

	return true;
}

void BG_CDragonMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void BG_CDragonMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void BG_CDragonMap::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void BG_CDragonMap::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

BG_CDragonMap* BG_CDragonMap::Clone()
{
	return new BG_CDragonMap(*this);
}
