#include "BG_DragonMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround_CloudAnim.h"
#include "Scene/SceneResource.h"

bool BG_DragonMap::bIsEnd= false;

BG_DragonMap::BG_DragonMap()
{

}

BG_DragonMap::BG_DragonMap(const BG_DragonMap& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_DragonMap");
}

BG_DragonMap::~BG_DragonMap()
{
	
}

void BG_DragonMap::Start()
{
	CBackGround::Start();

	//UV Flow
	// FG : Direction(true)	BG : Direction (false)
	m_Sprite->SetAnimation2DEnable(false);
	m_Sprite->SetUVFlow2DEnable(true);
	m_Sprite->SetUVFlow2DSpeed(0.05f);
	m_Sprite->SetUVFlow2DDirection(false);
}

bool BG_DragonMap::Init()
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
	m_Sprite->AddChild(m_FadeIn);

	m_FadeAnim->SetFrameEndFunction<BG_DragonMap>(this, &BG_DragonMap::AnimFrameEnd);
	m_FadeIn->Enable(false);

	return true;
}

void BG_DragonMap::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);

	if (bIsEnd)
	{
		if (!m_FadeIn->IsEnable())
		{
			m_FadeIn->Enable(true);
			m_FadeIn->SetDefaultZ(0.1f);
;			m_FadeAnim->ChangeAnimation("FadeOut");
		}

	}
}

void BG_DragonMap::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void BG_DragonMap::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_DragonMap::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_DragonMap* BG_DragonMap::Clone()
{
	return new BG_DragonMap(*this);
}

void BG_DragonMap::AnimFrameEnd(const std::string& Name)
{
	if (Name == "FadeOut")
	{
		m_pScene->GetResource()->SoundStop("MUS_FieryFrolic");
	}
}


