#include "Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround_CloudAnim.h"

CEffect::CEffect()
{

}

CEffect::CEffect(const CEffect& obj) :
	CGameObject(obj)
{
	//m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CEffect::~CEffect()
{
}

void CEffect::Start()
{
	CGameObject::Start();
}

bool CEffect::Init()
{
	CGameObject::Init();


	return true;
}

void CEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEffect* CEffect::Clone()
{
	return new CEffect(*this);
}
