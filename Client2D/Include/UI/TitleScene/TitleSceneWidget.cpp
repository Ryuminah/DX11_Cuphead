#include "TitleSceneWidget.h"

CTitleSceneWidget::CTitleSceneWidget()
{
}

CTitleSceneWidget::CTitleSceneWidget(const CTitleSceneWidget& widget) :
	CWidgetWindow(widget)
{
}

CTitleSceneWidget::~CTitleSceneWidget()
{
}

bool CTitleSceneWidget::Init()
{
	CWidgetWindow::Init();

	m_OutlineText = CreateWidget<CText>("PressAnyButton");
	m_OutlineText->SetFont("Tutorial_ExtraBold");
	m_OutlineText->SetText(TEXT("Press Enter Key"));
	m_OutlineText->SetColor(0.f, 0.f, 0.f);
	m_OutlineText->SetPos(440.f, 50.f);
	m_OutlineText->SetSize(400.f, 50.f);
	m_OutlineText->SetFontSize(41.f);
	m_OutlineText->SetShadowEnable(false);

	// 적을 text를 이름으로 등록한다.
	m_Text = CreateWidget<CText>("PressEnterKey");
	m_Text->SetFont("Tutorial_ExtraBold");
	m_Text->SetText(TEXT("Press Enter Key"));
	m_Text->SetColor(1.f, 0.79f, 0.39f);
	m_Text->SetPos(440.f, 50.f);
	m_Text->SetSize(400.f, 50.f);
	m_Text->SetFontSize(40.f);
	m_Text->SetShadowEnable(false);
	
	/*m_Text->SetShadowColor(1.f, 1.f, 0.f);
	m_Text->SetShadowAlphaEnable(true);
	m_Text->SetShadowOpacity(0.5f);*/

	return true;
}

void CTitleSceneWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTitleSceneWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTitleSceneWidget::Render()
{
	CWidgetWindow::Render();
}

CTitleSceneWidget* CTitleSceneWidget::Clone()
{
	return new CTitleSceneWidget(*this);
}


