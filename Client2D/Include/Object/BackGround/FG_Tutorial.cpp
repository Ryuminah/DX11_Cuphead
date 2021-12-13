#include "FG_Tutorial.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"
#include "Scene/CameraManager.h"
#include "UI/Image.h"



FG_Tutorial::FG_Tutorial()
{

}

FG_Tutorial::FG_Tutorial(const FG_Tutorial& obj) :
	CWidgetWindow(obj)
{
}

FG_Tutorial::~FG_Tutorial()
{
}

void FG_Tutorial::Start()
{
	CWidgetWindow::Start();;
}

bool FG_Tutorial::Init()
{
	CWidgetWindow::Init();

	m_Image = CreateWidget<CImage>("FG_Tutorial");

	m_Image->SetPos(0.0f, 0.0f);
	m_Image->SetSize(1280.f, 720.f);
	m_Image->SetTexture("TestImage", TEXT("BackGround/Tutorial/FG_Tutorial.png"));
	m_Image->SetZOrder(1);

	return true;
}

void FG_Tutorial::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void FG_Tutorial::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void FG_Tutorial::Render()
{
	CWidgetWindow::Render();
}

FG_Tutorial* FG_Tutorial::Clone()
{
	return new FG_Tutorial(*this);
}
