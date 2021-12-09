#pragma once
#include "UI/WidgetWindow.h"
#include "UI/Text.h"

class CTitleSceneWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CTitleSceneWidget();
    CTitleSceneWidget(const CTitleSceneWidget& widget);
    virtual ~CTitleSceneWidget();

private:
    CSharedPtr<CText>   m_Text;
    CSharedPtr<CText>   m_OutlineText;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CTitleSceneWidget* Clone();

private:
};

