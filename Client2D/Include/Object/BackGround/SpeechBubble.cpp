#include "SpeechBubble.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/BG_KettleHouseAnim.h"
#include "../../UI/KettleHouse/BubbleTextWidget.h"
#include "Scene/Viewport.h"

int CSpeechBubble::DialogNumber = 0;
int CSpeechBubble::DialogMax= 0;


CSpeechBubble::CSpeechBubble() 
{

}

CSpeechBubble::CSpeechBubble(const CSpeechBubble& obj) :
	CBackGround(obj)
{
	//m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CSpeechBubble::~CSpeechBubble()
{
}

void CSpeechBubble::Start()
{
	CBackGround::Start();
}

bool CSpeechBubble::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("SpeechBubble");
	m_BubbleTail = CreateSceneComponent<CSpriteComponent>("BubbleTail");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(480.f, 140.f, 1.f);
	m_Sprite->SetRelativePos(880.f, 360.f, 0.f);

	m_Sprite->AddChild(m_BubbleTail);
	m_BubbleTail->SetRelativeScale(29.f, 59.f, 1.f);
	m_BubbleTail->SetRelativePos(170.f, -57.f, 0.f);
	m_BubbleTail->CreateAnimation2D<BG_KettleHouseAnim>();
	m_BubbleTailAnim = m_BubbleTail->GetAnimation2D();
	m_BubbleTail->SetRender2DType(Render_Type_2D::RT2D_Back);

	m_Sprite->CreateAnimation2D<BG_KettleHouseAnim>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_Sprite->SetDefaultZ(0.1f);
	m_BackGroundImage = m_Sprite->GetAnimation2D();

	m_BackGroundImage->ChangeAnimation("SpeechBubble");
	m_BubbleTailAnim->ChangeAnimation("BubbleTail");

	m_WidgetComponent = CreateSceneComponent<CWidgetComponent>("BubbleTextWidget");
	m_Sprite->AddChild(m_WidgetComponent);

	m_WidgetComponent->CreateWidget<CBubbleTextWidget>("BubbleTextWidget");
	m_WidgetComponent->SetRelativeScale(450.f, 140.f, 1.f);
	m_WidgetComponent->SetRelativePos(-880.f, -360.f, 1.f);

	m_BubbleText = (CBubbleTextWidget*)m_WidgetComponent->GetWidget();

	CreateDialogInfo();
	SetTextWidget();

	return true;
}

void CSpeechBubble::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);
}

void CSpeechBubble::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void CSpeechBubble::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void CSpeechBubble::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

CSpeechBubble* CSpeechBubble::Clone()
{
	return new CSpeechBubble(*this);
}

void CSpeechBubble::SetTextWidget()
{
	DialogInfo Info = m_vecDialogInfo[DialogNumber];
	m_BubbleText->SetTextWidget(Info.Text);
}

void CSpeechBubble::SetDialogNumber(int dialogNumber)
{
	DialogNumber = dialogNumber;

	if (DialogNumber >= m_vecDialogInfo.size())
	{
		return;
	}

	DialogInfo Info = m_vecDialogInfo[DialogNumber];
	m_BubbleText->SetTextWidget(Info.Text);
}


void CSpeechBubble::CreateDialogInfo()
{
	DialogInfo info;
	info.Text = TEXT("WHAT A FINE PICKLE YOU BOYS HAVE GOTTEN YOURSELVES INTO!");
	m_vecDialogInfo.push_back(info);

	info.Text = TEXT("I KNOW YOU DON'T WANT TO BE PAWNS OF THE DEVIL!");
	m_vecDialogInfo.push_back(info);

	info.Text = TEXT("BUT IF YOU REFUSE... I CAN'T BEAR TO IMAGINE YOUR FATES!");
	m_vecDialogInfo.push_back(info);

	info.Text = TEXT("I WILL GIVE YOU THE MOST REMARKABLE MAGICAL ABILITES!");
	m_vecDialogInfo.push_back(info);

	info.Text = TEXT("NOW GO TO MY WRITING DESK AND USE THE MYSTICAL INKELL THERE.");
	m_vecDialogInfo.push_back(info);

	DialogMax = m_vecDialogInfo.size();
}


void CSpeechBubble::CreateSpeechBubble(Vector3 size, Vector3 Pos)
{
	m_Sprite->SetRelativeScale(size);
	m_Sprite->SetRelativePos(size);
}
