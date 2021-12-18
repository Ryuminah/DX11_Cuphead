#pragma once
#include "BackGround.h"
#include "Component/WidgetComponent.h"

struct DialogInfo
{
	const TCHAR* Text;
	Vector2 Size;
};

class CSpeechBubble :
    public CBackGround
{
	friend class CScene;

private:
	static int DialogNumber;
	static int DialogMax;


private:
	CSharedPtr<CSpriteComponent> m_BubbleTail;
	class CAnimation2D* m_BubbleTailAnim;
	CSharedPtr<CWidgetComponent> m_WidgetComponent;
	class CBubbleTextWidget* m_BubbleText;
	std::vector<DialogInfo> m_vecDialogInfo;

protected:
	CSpeechBubble();
	CSpeechBubble(const CSpeechBubble& obj);
	virtual ~CSpeechBubble();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSpeechBubble* Clone();

public:
	void CreateSpeechBubble(Vector3 size, Vector3 Pos);
	void CreateDialogInfo();
	void SetTextWidget();

public:
	void SetDialogNumber(int dialogNumber);


	int GetDialogNubmer()
	{
		return DialogNumber;
	}

	int GetDialogMax()
	{
		return DialogMax;
	}
};

