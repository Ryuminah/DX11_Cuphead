#pragma once
#include "BackGround.h"
#include "UI/WidgetWindow.h"


class FG_Tutorial :
    public CWidgetWindow
{
	friend class CViewport;

private:
	class CImage* m_Image;

protected:
	FG_Tutorial();
	FG_Tutorial(const FG_Tutorial& obj);
	virtual ~FG_Tutorial();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual FG_Tutorial* Clone();
};

