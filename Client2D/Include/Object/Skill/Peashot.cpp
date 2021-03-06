#include "Peashot.h"
#include "../Character/Mugman.h"
#include "../Character/Dragon.h"
#include "../../Animation2D/DragonAnimation.h"
#include <time.h>
#include "Scene/SceneResource.h"

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
	m_Collider = CreateSceneComponent<CColliderBox2D>("SkillCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(100.f, 140.f, 1.f);

	m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_Rotation);


	m_Collider->SetExtent(40.f, 70.f);
	m_Collider->SetCollisionProfile("Skill");
	m_Collider->SetColliderType(Collider_Type::Static);
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
	srand((unsigned int)time(NULL));


	// 가장 앞에 있는 링이라면 플레이어의 위치를 가져와 각도를 계산한다.
	if (m_bIsHead)
	{
		// Set Random AllRings
		AllRingCount = rand() % 2 + 3;

		// 캐릭터 중앙을 기준으로 벡터 길이 계산 (캐릭터 피봇이 현재 발 밑이여서 높이를 보정해줌)
		Vector3 vGunPoint = (GetRelativePos() * GetAxis(AXIS_X)) * -1.f;
		Vector3 vGunPointToPlayer = CMugman::PlayerPrevPos - GetRelativePos();

		// 시선 방향보다 아래에 있을 때 (y값이 음수일 때)만 위치를 보정해준다.
		// 안그러면 너무 높게 올라감 ㄱㅡ
		if (vGunPointToPlayer.y <= 0.f)
		{
			vGunPointToPlayer.y += 35.f;
		}
	
		float Angle = vGunPoint.Angle(vGunPointToPlayer);

		// 캐릭터가 몬스터의 시선 방향보다 높게 있을 경우 부호를 바꿔줌.
		Angle = vGunPointToPlayer.y > 0.f ? Angle * -1.f : Angle;
		AddRelativeRotationZ(Angle);
		m_Sprite->GetMaterial(0)->SetOpacity(1.f);
		RingAngle = Angle;

		// 뒤따라 오는 링들을 만든다.
		CreateChildRing();

		++RepeatCount;
	}

	else
	{
		// 아니라면 Head의 각도를 기준으로 생성된다.
		AddRelativeRotationZ(RingAngle);

		// 마지막 링은 무조건 패링이 가능하게끔.
		if (m_Number == AllRingCount)
		{
			// 패링이 가능한 콜리전으로 변경
			m_Collider->SetCollisionProfile("Parry");
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
	

	Vector2 DefaultOut = { -50.f, -50.f };

	if (GetRelativePos().x <= DefaultOut.x || GetRelativePos().y <= DefaultOut.y)
	{
		m_bIsEnd = true;
	}
}

void CPeashot::SkillEnd(float DeltaTime)
{
	// 머리가 끝났을 떄를 스킬 재사용의 기준으로 삼는다.
	if (m_bIsHead)
	{
		// 반복횟수가 남았다면
		if (RepeatCount != TotalRepeatNumber)
		{
			CDragon* pDragon = (CDragon*)m_pSkillOwner;
			pDragon->Peashot();
		}

		// 반복횟수가 남지 않았을때만 완전종료함수를 호출한다.
		else if (RepeatCount == TotalRepeatNumber)
		{
			m_pSkillOwner->SkillEnd(GetName());

		}
	}

	Active(false);
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
