#include "BubbleTextWidget.h"

CBubbleTextWidget::CBubbleTextWidget()
{
}

CBubbleTextWidget::CBubbleTextWidget(const CBubbleTextWidget& widget) :
	CWidgetWindow(widget)
{
}

CBubbleTextWidget::~CBubbleTextWidget()
{

}

bool CBubbleTextWidget::Init()
{
	CWidgetWindow::Init();

	m_Text = CreateWidget<CText>("BubbleText");
	m_Text->SetFont("KettleHouse");
	m_Text->SetText(TEXT("Press Enter Key"));
	m_Text->SetColor(0.f, 0.f, 0.f);
	m_Text->SetPos(660.f, 350.f);
	m_Text->SetSize(500.f, 130.f);
	m_Text->SetFontSize(28.f);
	m_Text->SetShadowEnable(false);
	m_Text->SetAlignH(TEXT_ALIGN_H::Left);
	m_Text->SetAlignV(TEXT_ALIGN_V::Top);


	return true;
}

void CBubbleTextWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CBubbleTextWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBubbleTextWidget::Render()
{
	CWidgetWindow::Render();
}

CBubbleTextWidget* CBubbleTextWidget::Clone()
{
	return new CBubbleTextWidget(*this);
}

void CBubbleTextWidget::SetTextWidget(const TCHAR* text, Vector2 BoxSize)
{
	m_Text->SetText(text);
	m_Text->SetSize(BoxSize);
	//m_Text->SetFontSize(FontSize);
	//m_Text->SetPos(Pos);
}


