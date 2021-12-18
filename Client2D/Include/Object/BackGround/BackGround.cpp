#include "BackGround.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/BG_KettleHouseAnim.h"

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

	m_FadeIn= CreateSceneComponent<CSpriteComponent>("FadeIn");
	m_FadeIn->CreateAnimation2D<BG_KettleHouseAnim>();
	m_FadeAnim = m_FadeIn->GetAnimation2D();
	m_FadeIn->SetPivot(0.f, 0.f, 0.f);
	m_FadeIn->SetRelativeScale(1280.f, 720.f, 1.f);
	m_FadeIn->Enable(false);

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
