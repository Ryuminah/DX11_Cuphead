#include "BackGround.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround_CloudAnim.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const CBackGround& obj) :
	CGameObject(obj)
{
	//m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBackGround::~CBackGround()
{
}

void CBackGround::Start()
{
	CGameObject::Start();
}

bool CBackGround::Init()
{
	CGameObject::Init();


	return true;
}

void CBackGround::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBackGround::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBackGround::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBackGround::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBackGround* CBackGround::Clone()
{
	return new CBackGround(*this);
}
