#include "ScreenFX.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Scene/SceneResource.h"
#include "../../Animation2D/BackGround/ScreenFXAnim.h"
#include "Scene/CameraManager.h"

ScreenFX::ScreenFX()
{

}

ScreenFX::ScreenFX(const ScreenFX& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("ScreenFX");
}

ScreenFX::~ScreenFX()
{
}

void ScreenFX::Start()
{
	CBackGround::Start();
}

bool ScreenFX::Init()
{
	CBackGround::Init();

	m_pScene->GetResource()->CreateAnimationSequence2D("Screenfx");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Screenfx",
		"Screenfx", TEXT("Screenfx.png"));
	for (int y = 0; y < 2; ++y)
	{
		for (int i = 0; i < 8; ++i)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Screenfx",
				Vector2(i * 1024.f, y * 512.f), Vector2((i + 1) * 1024.f, (y + 1) * 512.f));
		}
	}

	//m_pScene->GetResource()->CreateMaterial("Opacity");

	m_Sprite = CreateSceneComponent<CSpriteComponent>("ScreenFX");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.f, 0.f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(1280.f, 720.f, 1.f);


	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	//m_Sprite->SetDefaultZ(0.1f);

	m_Sprite->GetMaterial(0)->SetOpacity(0.3f);

	m_Sprite->CreateAnimation2D<CScreenFXAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();

	return true;
}

void ScreenFX::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
	SetRelativePos(m_pScene->GetCameraManager()->GetCurrentCamera()->GetWorldPos());
}

void ScreenFX::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void ScreenFX::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void ScreenFX::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

ScreenFX* ScreenFX::Clone()
{
	return new ScreenFX(*this);
}
