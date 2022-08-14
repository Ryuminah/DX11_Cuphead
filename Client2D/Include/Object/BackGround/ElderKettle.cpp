#include "ElderKettle.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../../Animation2D/BackGround/BG_KettleHouseAnim.h"
#include "../BackGround/SpeechBubble.h"
#include "Input.h"
#include "../../SceneMode/KettleHouseScene.h"
#include "Scene/SceneResource.h"


bool CElderKettle::IsTutorialOpen = false;

CElderKettle::CElderKettle() : m_bCanDialogStart(false), m_bCanTutorialStart(false),
m_bIsDialog(false), m_DialogCount(0), m_bIsTutorial(false)
{

}

CElderKettle::CElderKettle(const CElderKettle& obj) :
	CBackGround(obj)
{
	//m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CElderKettle::~CElderKettle()
{
	CInput::GetInst()->ClearCallback();
}

void CElderKettle::Start()
{
	CBackGround::Start();
	m_FadeIn->SetRelativePos(-1100.f, -90.f, 0.f);
	m_FadeAnim->ChangeAnimation("FadeIn");
	m_FadeIn->Enable(true);
	m_pScene->GetResource()->SoundPlay("MUS_ElderKettle");
}

bool CElderKettle::Init()
{
	CBackGround::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("ElderKettle");
	m_Sign= CreateSceneComponent<CSpriteComponent>("Sign");

	m_DialogCollider = CreateSceneComponent<CColliderBox2D>("DialogCollider");
	m_TutorialCollider = CreateSceneComponent<CColliderBox2D>("TutorialCollider");
	m_DialogCollider->SetCollisionProfile("Event");
	m_TutorialCollider->SetCollisionProfile("Event");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(280.f, 280.f, 1.f);
	m_Sprite->SetRelativePos(1100.f, 90.f, 0.f);
	m_Sprite->AddChild(m_DialogCollider);
	m_Sprite->AddChild(m_TutorialCollider);
	m_Sprite->AddChild(m_Sign);

	m_Sprite->SetDefaultZ(0.8f);
	m_Sprite->AddChild(m_FadeIn);

	m_Sprite->CreateAnimation2D<BG_KettleHouseAnim>();
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_BackGroundImage= m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("ElderKettle_Idle");

	m_Sign->CreateAnimation2D<BG_KettleHouseAnim>();
	m_Sign->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_SignAnim = m_Sign->GetAnimation2D();
	m_SignAnim->ChangeAnimation("Z");
	m_Sign->SetRelativeScale(65.f, 65.f, 1.f);
	m_Sign->SetRelativePos(0.f, 260.f, 0.f);
	m_Sign->Enable(false);

	m_DialogCollider->SetExtent(150.f, 150.f);
	m_DialogCollider->SetRelativePos(0.f, 0.f, 0.f);
	m_TutorialCollider->SetExtent(50.f, 15.f);
	m_TutorialCollider->SetRelativePos(-450.f, 100.f,0.f);

	CInput::GetInst()->AddKeyCallback<CElderKettle>("Jump", KT_Down, this, &CElderKettle::Interaction);


	m_DialogCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::Begin, this, &CElderKettle::EventCollisionBegin);
	m_DialogCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::Overlap, this, &CElderKettle::EventCollisionOverlap);
	m_DialogCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::End, this, &CElderKettle::EventCollisionEnd);

	m_TutorialCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::Begin, this, &CElderKettle::EventCollisionBegin);
	m_TutorialCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::Overlap, this, &CElderKettle::EventCollisionOverlap);
	m_TutorialCollider->AddCollisionCallbackFunction<CElderKettle>(Collision_State::End, this, &CElderKettle::EventCollisionEnd);

	m_FadeAnim->SetFrameEndFunction<CElderKettle>(this, &CElderKettle::AnimEnd);

	return true;
}

void CElderKettle::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);

	DialogCheck();
}

void CElderKettle::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);
}

void CElderKettle::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void CElderKettle::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

CElderKettle* CElderKettle::Clone()
{
	return new CElderKettle(*this);
}

void CElderKettle::EventCollisionBegin(const HitResult& result, CCollider* Collider)
{

	if (Collider->GetName() == "DialogCollider")
	{
		if (!m_bCanDialogStart)
		{
			m_Sign->Enable(true);
			m_pScene->GetResource()->SoundPlay("Menu_Move");
		}

		else
		{
			m_SpeechBubble->Enable(true);
		}

		m_bIsDialog = true;
	}

	if (Collider->GetName() == "TutorialCollider")
	{
		if (m_bCanTutorialStart)
		{
			m_Sign->Enable(true);
			m_pScene->GetResource()->SoundPlay("Menu_Move");
		}

		/*m_Sprite->Enable(true);
		m_SpeechBubble->Enable(true);*/
		m_bIsTutorial= true;

	}
}

void CElderKettle::EventCollisionOverlap(const HitResult& result, CCollider* Collider)
{
	if (Collider->GetName() == "DialogCollider")
	{
		m_bIsDialog = true;

	}

	if (Collider->GetName() == "TutorialCollider")
	{
		m_bIsTutorial = true;
	}
}

void CElderKettle::EventCollisionEnd(const HitResult& result, CCollider* Collider)
{

	if (Collider->GetName() == "DialogCollider")
	{
		m_Sign->Enable(false);
		m_SpeechBubble->Enable(false);
		m_bIsDialog = false;
	}

	if (Collider->GetName() == "TutorialCollider")
	{
		if (m_bCanTutorialStart)
		{
			m_Sign->Enable(false);
		}
	/*	m_Sprite->Enable(false);
		m_SpeechBubble->Enable(false);*/
		m_bIsTutorial = false;

	}
}

void CElderKettle::AnimEnd(const std::string& Name)
{
	if (Name == "FadeIn")
	{
		m_FadeIn->Enable(false);
	}

	if (Name == "FadeOut")
	{
		IsTutorialOpen = true;
	}
}

void CElderKettle::CreateSpeechBubble()
{
	// 말풍선 제작...
	CSpeechBubble* pSpeechBubble = m_pScene->SpawnObject<CSpeechBubble>("SpeechBubble");
	m_SpeechBubble = pSpeechBubble;
	m_SpeechBubble->SetDialogNumber(m_DialogCount);
	m_SpeechBubble->Enable(false);
	//pSpeechBubble->SetRelativePos(GetWorldPos());

}

void CElderKettle::Interaction(float DeltaTime)
{
	if (!m_bIsDialog && !m_bIsTutorial)
	{
		return;
	}

	if (m_bIsDialog)
	{
		// 아직 활성화 되지 않은 상태라면 안냇말을 띄운다.
		if (!m_bCanDialogStart)
		{
			// 말풍선 띄우기
			m_bCanDialogStart = true;
			m_Sign->Enable(false);
			m_SpeechBubble->Enable(true);

			// 다음 위치를 미리 설정
			m_SignAnim->ChangeAnimation("TutorialZ");
			m_Sign->SetRelativePos(m_TutorialCollider->GetRelativePos().x-20.f, m_TutorialCollider->GetRelativePos().y + 60.f, 0.f);
			m_Sign->SetRelativeScale(240.f, 60.f, 0.5f);
			return;
		}

		// 현재 대화중이라면 대화 수를 증가시킨다.
		else if (m_bCanDialogStart && (m_DialogCount < m_SpeechBubble->GetDialogMax()))
		{
			++m_DialogCount;
			m_pScene->GetResource()->SoundPlay("Menu_CardUp");

			// 이떄 대화가 종료되었을때 입력이 또 들어오면 튜토리얼을 활성화 시켜준다.
			if (m_DialogCount == m_SpeechBubble->GetDialogMax() && !m_bCanTutorialStart)
			{
				m_bCanTutorialStart = true;
			}
		}
	}

	// 튜토리얼
	if (m_bIsTutorial)
	{
		if (m_bCanTutorialStart)
		{
			// 페이드아웃 애니메이션 띄우고 애니메이션 종료시 화면 전환.
			m_FadeIn->Enable(true);
			m_FadeAnim->ChangeAnimation("FadeOut");
		}
	}
}

void CElderKettle::DialogCheck()
{
	// 둘이 다르다면 다음 대화로 넘어가야 하는 것으로 간주하고 말풍선을 바꾼다.
	if (m_DialogCount == m_SpeechBubble->GetDialogMax())
	{
		return;
	}

	if (m_DialogCount != m_SpeechBubble->GetDialogNubmer())
	{
		m_SpeechBubble->SetDialogNumber(m_DialogCount);
	}
}


