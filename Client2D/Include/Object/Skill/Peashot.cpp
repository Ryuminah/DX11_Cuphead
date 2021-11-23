#include "Peashot.h"
#include "../Mugman.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Dragon.h"

float CPeashot::RingAngle = 0.f;
int	CPeashot::AllRingCount = 0;


CPeashot::CPeashot() : m_Animation(nullptr),
	m_RingSpeed(700.f), m_bIsHead(false), m_TimeInterval(0.f),
	m_Number(1)
{

}

CPeashot::CPeashot(const CPeashot& obj) : CSkill(obj)
{
	m_Collider = (CColliderBox2D*)FindSceneComponent("ColliderBox");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Rotation = FindSceneComponent("Rotation");
}

CPeashot ::~CPeashot()
{

}

void CPeashot::Start()
{
	CSkill::Start();
}

bool CPeashot::Init()
{
	CSkill::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Peashot");
	m_Collider = CreateSceneComponent<CColliderBox2D>("PeashotCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(100.f, 140.f, 1.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);


	m_Collider->SetExtent(50.f, 70.f);
	m_Collider->SetCollisionProfile("Enemy");
	m_Collider->SetColliderType(Collider_Type::Trigger);
	//m_Collider->SetPivot(0.5f, 0.f, 0.f);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Sprite->GetMaterial(0)->SetOpacity(0.1f);
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->ChangeAnimation("Dragon_Peashot_Ring");

	//m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimationFrameEnd);

	SetUseBlockMovement(false);
	SetDefaultZ(0.1f);
	return true;
}

void CPeashot::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	// 화면 밖을 나갔다면 스킬 종료
	Vector2 Out = { -100.f, -200.f };
	if (GetRelativePos().x < Out.x || GetRelativePos().y < Out.y)
	{
		SkillEnd(DeltaTime);
		Active(false);

	}
}

void CPeashot::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CPeashot::Collision(float DeltaTime)
{
	CSkill::Collision(DeltaTime);
}

void CPeashot::Render(float DeltaTime)
{
	CSkill::Render(DeltaTime);
}

CPeashot* CPeashot::Clone()
{
	return new CPeashot(*this);
}


void CPeashot::SkillStart(float DeltaTime)
{
	// 가장 앞에 있는 링이라면 플레이어의 위치를 가져와 각도를 계산한다.
	if (m_bIsHead)
	{
		Vector3 vGunPoint = (GetRelativePos() * GetAxis(AXIS_X)) * -1.f;
		Vector3 vGunPointToPlayer = CMugman::PlayerPos - GetRelativePos();
		vGunPointToPlayer.y += 35.f;
		
		float Angle = vGunPoint.Angle(vGunPointToPlayer);
		AddRelativeRotationZ(Angle);
		m_Sprite->GetMaterial(0)->SetOpacity(1.f);
		RingAngle = Angle;

		CreateChildRing();
	}

	else
	{
		// 아니라면 Head의 각도를 기준으로 생성된다.
		AddRelativeRotationZ(RingAngle);

		if (m_Number == AllRingCount)
		{
			m_Animation->ChangeAnimation("Dragon_Peashot_Ring_Pink");
		}
	}
	
	m_bIsStarted = true;
}

void CPeashot::SkillActive(float DeltaTime)
{
	// 아직 활성화 되지 않았다면 시간을 깎는다
	if (m_TimeInterval > 0.f)
	{
		m_TimeInterval -= DeltaTime;

		if (m_TimeInterval < 0.f)
		{
			// 활성화 해줌
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			m_TimeInterval = 0.f;
		}

		return;
	}

	AddRelativePos(GetAxis(AXIS_X) * -m_RingSpeed * DeltaTime);
	
}

void CPeashot::SkillEnd(float DeltaTime)
{
	if (m_bIsHead)
	{
		// 반복횟수가 남았다면
		if (RepeatCount > 0)
		{
			CDragon* pDragon = (CDragon*)m_pSkillOwner;
			pDragon->Peashot();
		}

		// 반복횟수가 남지 않았을때만 완전종료함수를 호출한다.
		else if (RepeatCount == 0 )
		{
			m_pSkillOwner->SkillEnd(GetName());

		}

		--RepeatCount;
	}

}

void CPeashot::SetIsHead(bool IsHead)
{
	m_bIsHead = IsHead;
}

void CPeashot::CreateChildRing()
{
	float interval = 0.2f;
	for (int i = 1; i < AllRingCount; ++i)
	{
		CPeashot* pPeashot = m_pScene->SpawnObject<CPeashot>("Peashot");
		pPeashot->SetRelativePos(GetRelativePos());
		pPeashot->SetIsActive(true);
		pPeashot->m_Number = i + 1;
		pPeashot->m_TimeInterval = interval;
		interval += 0.2f;
	}
}

void CPeashot::SetAllRingCount(int _allRingCount)
{
	AllRingCount = _allRingCount;
}
