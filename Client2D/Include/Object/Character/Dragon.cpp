#include <iostream>
#include <time.h>
#include "Dragon.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Mugman.h"
#include "Engine.h"
#include "../../Animation2D/DragonAnimation.h"
#include "../Skill/Peashot.h"
#include "../Skill/Tail.h"
#include "../Skill/Meteor.h"
#include "../Skill/FireBoy.h"

#include "../Collision/DragonCollider.h"


CDragon::CDragon() : m_CurrentPhase(Phase::Phase1), m_NextAttackTime(5.f),
		m_LastPattern("Meteor"), m_NextPattern(0), m_TailTime(3.f), m_IsAnimEnd(false),
	m_bIsPhaseStart(false), m_GunPointAnim(nullptr), m_AttackFireBoyTime(0.f)
{
	
}

CDragon::CDragon(const CDragon& obj) : CCharacter(obj)
{

	m_Sprite = (CSpriteComponent*)FindSceneComponent("Dragon");
	m_GunPoint = (CSpriteComponent*)FindSceneComponent("GunPoint");
	m_Rotation = FindSceneComponent("Rotation");
	//m_Muzzle = FindSceneComponent("Muzzle");
}

CDragon::~CDragon()
{
}

void CDragon::Start()
{
	CGameObject::Start();
	
	m_bCanAttack = false;
	m_Speed = 300.f;

	//PhaseOne();
}

bool CDragon::Init()
{
	// Dragon의 충돌용 Collider는 따로 제작해서 사용한다.
	CCharacter::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Dragon");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_GunPoint = CreateSceneComponent<CSpriteComponent>("GunPoint");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(870.f, 870.f, 1.f);
	m_Sprite->SetRelativePos(1150.f, -120.f, 0.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);


	//m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_GunPoint);

	m_GunPoint->SetInheritRotZ(true);
	m_GunPoint->SetRelativePos(Vector3(0.f, 630.f, 0.f));
	m_GunPoint->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimFrameEnd);

	m_GunPoint->CreateAnimation2D<CDragonAnimation>();
	m_GunPoint->SetAnimation2DEnable(false);
	m_GunPoint->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_GunPoint->SetDefaultZ(0.7f);
	m_GunPointAnim = m_GunPoint->GetAnimation2D();
	m_GunPointAnim->SetFrameEndFunction<CDragon>(this, &CDragon::GunPointAnimEnd);


	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	CreateDragonCollider();
	SetPhysicsSimulate(false);
	SetUseBlockMovement(false);
	SetPrevDirection(Direction::LEFT);

	//m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::Begin, this, &CDragon::CollisionBegin);
	//m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::Overlap, this, &CDragon::CollisionOverlap);
	//m_Collider->AddCollisionCallbackFunction<CDragon>(Collision_State::End, this, &CDragon::CollisionEnd);

	return true;
}

void CDragon::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	ChangeSkill();
	TimeCheck(DeltaTime);
	PhaseEndCheck(DeltaTime);
}

void CDragon::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	// 다음 어떤 스킬을 사용할지 선택
	SelectNextSkill();
}

void CDragon::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CDragon::Render(float DeltaTime)
{
	CCharacter::Render(DeltaTime);
}

CDragon* CDragon::Clone()
{
	return new CDragon(*this);
}

void CDragon::Animation2DNotify(const std::string& Name)
{
	CCharacter::Animation2DNotify(Name);
}

void CDragon::AnimFrameEnd(const std::string& Name)
{
	// 페이즈 전환중에는 모든 애니메이션조건을 무시한다.
	if (!m_bIsPhaseStart)
	{
		return;
	}

	if (Name == "Dragon_Peashot_Start")
	{
		Peashot();
		return;
	}

	if (Name == "Dragon_Peashot_End")
	{
		AttackEnd();
		return;
	}

	if (Name == "Dragon_Meteor_Start")
	{
		Meteor();
		return;
	}

	if (Name == "Dragon_Meteor_Attack")
	{
		m_CurrentSkill->SetbIsEnd(true);
		return;
	}

	if (Name == "Dragon_Meteor_End")
	{
		AttackEnd();
		return;
	}


}

void CDragon::GunPointAnimEnd(const std::string& Name)
{
	if (Name == "Dragon_Tounge_Start")
	{
		m_GunPointAnim->ChangeAnimation("Dragon_Tounge_Loop");
	}
}

void CDragon::ChangeAnimation(const std::string& Name)
{
	m_Animation->ChangeAnimation(Name);
}

std::string CDragon::GetCurrentSequenceName()
{
	return 	m_Animation->GetCurrentSequenceName();
}

bool CDragon::GetIsFrameEnd()
{
	return m_Animation->GetIsFrameEnd();
}

void CDragon::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetName() == "BulletCollider")
	{
		++m_HitCount;
		m_Sprite->GetMaterial(0)->SetMaterialTimerBaseColor(1.f, 0.f, 0.f, 0.5f);
		m_Sprite->GetMaterial(0)->UseMaterialTimer(0.01f);
	}
}

void CDragon::CollisionOverlap(const HitResult& result, CCollider* Collider)
{
}

void CDragon::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CDragon::CreateDragonCollider()
{
	CDragonCollider* pDragonCollider= m_pScene->SpawnObject<CDragonCollider>("DragonCollider");
	m_pDragonCollider = pDragonCollider;
	m_pDragonCollider->m_pDragon = this;
}

int CDragon::MakeRandomNumber()
{
	srand((unsigned int)time(NULL));

	// 모든 스킬은 최소 2~4사이로 반복한다.
	int RandomRepeat = rand() % 3 + 2;
	return RandomRepeat;
}

void CDragon::PhaseOne()
{
	m_vecSkill.push_back(SkillData("Peashot"));
	m_vecSkill.push_back(SkillData("Meteor"));
	m_vecSkill.push_back(SkillData("Tail"));

	m_bIsPhaseStart = true;
}

void CDragon::PhaseEnd()
{
	m_bIsPhaseStart = false;
}

void CDragon::SetPhaseTwoOpening()
{
	m_Animation->ChangeAnimation("Dragon_Dash");
	// 충돌체 비활성화
	m_pDragonCollider->Enable(false);
	SetRelativeScale(480.f, 130.f, 0.f);
	SetWorldPos(1600.f, 295.f, 0.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);
	m_NextAttackTime = 3.0f;
}

void CDragon::PhaseTwo(float DeltaTime)
{
	// Dash
	// 화면 밖으로 나갔다면 
	if (GetWorldPos().x >= -400.f && m_Animation->GetCurrentSequenceName() == "Dragon_Dash")
	{
		AddRelativePos(GetAxis(AXIS_X) * -1200.f * DeltaTime);
		return;
	}

	else
	{
		// 아직 애니메이션이 바뀌지 않았을 경우 애니메이션을 바꾼다.
		if (m_Animation->GetCurrentSequenceName() != "Dragon_Idle2")
		{
			m_Animation->ChangeAnimation("Dragon_Idle2");
			SetWorldPos(-400.f, 10.f, 0.f);
			SetRelativeScale(670.f,600.f,0.f);
			m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);
		}

	}

	// 정상적인 위치까지 도달했을 시 Phase를 시작한다.
	if (GetRelativePos().x >= 80.f)
	{
		m_pDragonCollider->Enable(true);
		m_pDragonCollider->SetWorldPos(200.f, 0.f, 0.f);
		// 총구 위치
		m_GunPoint->AddRelativePos(760.f, -610.f,0.5f);
		m_GunPoint->SetRelativeScale(1180.f, 150.f, 0.f);
		m_GunPoint->SetAnimation2DEnable(true);
		m_GunPointAnim->ChangeAnimation("Dragon_Tounge_Start");
		m_bIsPhaseStart = true;

		// test용 치트키
		m_NextAttackTime = 0.f;


		// 공격 유닛 생성
		int NextAttackTime = rand() % 4 + 2;
		m_AttackFireBoyTime = (float)NextAttackTime;
	}
	
	AddRelativePos(GetAxis(AXIS_X) * m_Speed * DeltaTime);

}

void CDragon::Peashot()
{
	m_LastPattern = PEASHOT;
	m_bCanAttack = false;
	m_bIsAttack = true;
	m_CurrentSkillName = "Peashot";
	m_Animation->ChangeAnimation("Dragon_Peashot_Attack");


	m_vecSkill[PEASHOT].IsActive = true;
	m_LastPattern = m_vecSkill[PEASHOT].SkillName;

	CPeashot* pPeashot = m_pScene->SpawnObject<CPeashot>("Peashot");
	m_CurrentSkill = pPeashot;
	pPeashot->SetRelativePos(m_GunPoint->GetWorldPos());
	pPeashot->SetIsHead(true);
	pPeashot->SetIsActive(true);
	pPeashot->SetSkillOwner(this);
	pPeashot->SetAllRingCount(3);
	pPeashot->SetTotalRepeatNumber(MakeRandomNumber());
}

void CDragon::AttackEnd()
{
	m_Animation->ChangeAnimation("Dragon_Idle");
	m_bIsAttack = false;
}

void CDragon::Meteor()
{
	m_LastPattern = METEOR;
	// 총구 위치를 바꿔준다.
	m_bCanAttack = false;
	m_bIsAttack = true;
	m_CurrentSkillName = "Meteor";

	m_Animation->ChangeAnimation("Dragon_Meteor_Attack");

	m_vecSkill[METEOR].IsActive = true;
	m_LastPattern = m_vecSkill[METEOR].SkillName;

	CMeteor* pMeteor= m_pScene->SpawnObject<CMeteor>("Meteor");
	m_CurrentSkill = pMeteor;
	pMeteor->SetRelativePos(m_GunPoint->GetWorldPos().x - 150.f, 270.f, 0.f);
	pMeteor->SetIsActive(true);
	pMeteor->SetSkillOwner(this);
	pMeteor->SetTotalRepeatNumber(MakeRandomNumber());
}

void CDragon::Tail()
{
	CMeteor* pTail= m_pScene->SpawnObject<CMeteor>("Tail");
	pTail->SetIsActive(true);
	pTail->SetSkillOwner(this);
}

void CDragon::FireBoy()
{
	CFireboy* pFireBoy = m_pScene->SpawnObject<CFireboy>("FireBoy");
	m_CurrentSkill = pFireBoy;
	m_CurrentSkillName = "FireBoy";
	pFireBoy->SetRelativePos(m_GunPoint->GetWorldPos());
	pFireBoy->AddRelativePos(-500.f, 0.f, 0.f);
	pFireBoy->SetIsActive(true);
	pFireBoy->SetSkillOwner(this);

	if (m_AttackFireBoyTime <= 0.f)
	{
		pFireBoy->SetAttackUnit(true);
		int NextAttackTime = rand() % 4 + 1;
		m_AttackFireBoyTime = (float)NextAttackTime;
	}
}

void CDragon::ChangeSkill()
{
	if (m_bCanAttack)
	{
		if (m_CurrentPhase == Phase::Phase1)
		{
			if (m_NextPattern == PEASHOT)
			{
				m_Animation->ChangeAnimation("Dragon_Peashot_Start");
			}

			if (m_NextPattern == METEOR)
			{
				m_Animation->ChangeAnimation("Dragon_Meteor_Start");
			}
		}

		else if (m_CurrentPhase == Phase::Phase2)
		{
			// 알낳기
			FireBoy();
		}
	}

	m_bCanAttack = false;
}

void CDragon::SelectNextSkill()
{
	if (m_bCanAttack)
	{
		// 랜덤으로 정한다.
		if (m_CurrentPhase == Phase::Phase1)
		{
			if (m_LastPattern == "Peashot")
			{
				m_NextPattern = METEOR;
			}

			else
			{
				m_NextPattern = PEASHOT;
			}
		}

		else if (m_CurrentPhase == Phase::Phase2)
		{
			// phase2에 필요한 것들...
			CFireboy* pFireBoy = m_pScene->SpawnObject<CFireboy>("FireBoy");
			m_CurrentSkill = pFireBoy;
			m_CurrentSkillName = "FireBoy";
			pFireBoy->SetRelativePos(m_GunPoint->GetWorldPos());
			pFireBoy->AddRelativePos(-500.f,0.f,0.f);
			pFireBoy->SetIsActive(true);
			pFireBoy->SetSkillOwner(this);
		}
	
	}

	
}

void CDragon::SkillEnd(std::string SkillName)
{
	// 패턴의 완전한 종료일때 호출
	// Phase1
	if (SkillName == "Peashot")
	{
		m_vecSkill[PEASHOT].IsActive = false;
		m_Animation->ChangeAnimation("Dragon_Peashot_End");
	}

	if (SkillName == "Meteor")
	{
		m_vecSkill[METEOR].IsActive = false;
		m_Animation->ChangeAnimation("Dragon_Meteor_End");
	}

	// 반복이 정말 끝났을 때만 초기화 시켜준다
	if (CSkill::IsRepeatEnd())
	{
		CSkill::ResetRepeatInfo();
	}

}

void CDragon::TimeCheck(float DeltaTime)
{
	if (m_CurrentPhase == Phase::Phase1)
	{
		if (m_TailTime < 0.f)
		{
			//Tail();
			//Meteor();
			m_TailTime = 100.f;	// 랜덤으로 바꾸기
		}

		else
		{
			m_TailTime -= DeltaTime;
		}
	}

	if (m_AttackFireBoyTime > 0.f && m_CurrentPhase == Phase::Phase2)
	{
		m_AttackFireBoyTime -= DeltaTime;
	}

	if (m_bIsAttack)
	{
		return;
	}

	if (m_NextAttackTime < 0.f && m_bIsPhaseStart)
	{
		switch (m_CurrentPhase)
		{
		case Phase::Phase1:
			m_NextAttackTime = 3.0f;
			break;
		case Phase::Phase2:
			m_NextAttackTime = 1.0f;
			break;
		case Phase::Phase3:
			break;
		default:
			break;
		}

		m_bCanAttack = true;
		return;
	}

	m_NextAttackTime -= DeltaTime;
}

void CDragon::PhaseEndCheck(float DeltaTime)
{
	// Phase1 End 조건을 달성했다면
	if (m_HitCount >= 5 && m_CurrentPhase == Phase::Phase1)
	{
		if (m_CurrentSkill)
		{
			SkillEnd(m_CurrentSkillName);
			m_CurrentSkill->SetbIsEnd(true);
			m_bIsAttack = false;
		}

		m_bCanAttack = false;
		m_bIsPhaseStart = false;
		AddRelativePos(GetAxis(AXIS_X) * m_Speed * DeltaTime);
		m_pDragonCollider->AddRelativePos(GetAxis(AXIS_X) * m_Speed * DeltaTime);

		if (GetRelativePos().x >= 1600.f)
		{
			m_CurrentPhase = Phase::Phase2;
			SetPhaseTwoOpening();
		}
	}

	// 현재 Phase2로 바뀌었다면
	if (m_CurrentPhase == Phase::Phase2 && m_bIsPhaseStart == false)
	{
		PhaseTwo(DeltaTime);
	}
}







