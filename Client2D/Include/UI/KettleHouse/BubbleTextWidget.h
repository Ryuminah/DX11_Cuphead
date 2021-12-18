#pragma once
#include "UI/WidgetWindow.h"
#include "UI/Text.h"

class CBubbleTextWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CBubbleTextWidget();
    CBubbleTextWidget(const CBubbleTextWidget& widget);
    virtual ~CBubbleTextWidget();

private:
    CSharedPtr<CText>   m_Text;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CBubbleTextWidget* Clone();


public:
    void SetTextWidget(const TCHAR* text, Vector2 BoxSize = { 500.f, 130.f });
};

