#include "BG_TutorialMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Character/Mugman.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"

BG_TutorialMap::BG_TutorialMap()
{
	m_Speed = 550.f;
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

	return true;
}

void BG_TutorialMap::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
	
	// 플레이어 위치가 화면 중앙이라면 움직일 필요가 없음
	if (CMugman::PlayerPos.x < 640.f)
	{
		
		return;
	}

	/*float MoveDistanceX = (CMugman::PlayerPrevPos.x - CMugman::PlayerPos.x);

	if (CMugman::PlayerPos.x - CMugman::PlayerPrevPos.x > 0.f)
	{
		AddWorldPos(MoveDistanceX + (640.f * DeltaTime), 0.f, 0.f);
	}

	if (CMugman::PlayerPos.x - CMugman::PlayerPrevPos.x < 0.f)
	{
		AddWorldPos(MoveDistanceX + (640.f * DeltaTime), 0.f, 0.f);
	}*/

}

void BG_TutorialMap::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
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
