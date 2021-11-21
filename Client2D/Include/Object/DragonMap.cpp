#include "DragonMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CDragonMap::CDragonMap()
{

}

CDragonMap::CDragonMap(const CDragonMap& obj) :
	CGameObject(obj)
{
	m_BackGround = (CSpriteComponent*)FindSceneComponent("DragonMap");
}

CDragonMap::~CDragonMap()
{
}

void CDragonMap::Start()
{
	CGameObject::Start();
}

bool CDragonMap::Init()
{
	CGameObject::Init();

	m_BackGround = CreateSceneComponent<CSpriteComponent>("DragonMap");

	SetRootComponent(m_BackGround);
	m_BackGround->SetPivot(0.0f, 0.0f, 0.0f);
	m_BackGround->SetRelativePos(0.f, 0.0f, 0.f);
	m_BackGround->SetRelativeScale(1280.f, 720.f, 1.f);
	m_BackGround->SetMaterial(0,"BG_Normal");

	//SetUpdatePosZ(false);
	SetDefaultZ(0.9f);

	return true;
}

void CDragonMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CDragonMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDragonMap::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDragonMap::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CDragonMap* CDragonMap::Clone()
{
	return new CDragonMap(*this);
}
