#include <iostream>
#include "Dragon.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/DragonAnimation.h"
#include "Engine.h"
#include "Mugman.h"
#include "Skill/Peashot.h"
#include "Skill/Tail.h"
#include "Skill/Meteor.h"
#include "DragonCollider.h"


CDragon::CDragon() : m_CurrentPhase(Phase::Phase1), m_NextAttackTime(5.f),
		m_LastPattern("Meteor"), m_NextPattern(0), m_TailTime(3.f), m_IsAnimEnd(false)
{
	
}

CDragon::CDragon(const CDragon& obj) : CCharacter(obj)
{

	m_Sprite = (CSpriteComponent*)FindSceneComponent("Dragon");
	//m_Collider = (CColliderBox2D*)FindSceneComponent("DragonCollider");
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


	PhaseOne();
}

bool CDragon::Init()
{
	CCharacter::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Dragon");
	//m_Collider = CreateSceneComponent<CColliderBox2D>("DragonCollider");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_GunPoint = CreateSceneComponent<CSceneComponent>("GunPoint");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(870.f, 870.f, 1.f);
	m_Sprite->SetRelativePos(1150.f, -120.f, 0.f);

	//m_Sprite->AddChild(m_Collider);
	m_Sprite->AddChild(m_GunPoint);


	//m_Collider->SetWorldPos(1150.f, 0.f, 0.f);
	/*m_Collider->SetRelativePos(0.f, 120.f, 0.f);
	m_Collider->SetExtent(50.f, 360.f);
	m_Collider->SetCollisionProfile("Enemy");
	m_Collider->SetColliderType(Collider_Type::Character);*/

	m_GunPoint->SetInheritRotZ(true);
	m_GunPoint->SetRelativePos(Vector3(0.f, 630.f, 0.f));
	m_GunPoint->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimation2D<CDragonAnimation>();
	m_Animation = m_Sprite->GetAnimation2D();
	m_Animation->SetFrameEndFunction<CDragon>(this, &CDragon::AnimFrameEnd);

	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);

	CreateDragonCollider();
	SetDefaultZ(0.5f);
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
	if (Name == "Dragon_Peashot_Start")
	{
		Peashot();
	}

	if (Name == "Dragon_Peashot_End")
	{
		AttackEnd();
	}

	if (Name == "Dragon_Meteor_Start")
	{
		Meteor();
	}

	if (Name == "Dragon_Meteor_Attack")
	{
		m_CurrentSkill->SetbIsEnd(true);
	}

	if (Name == "Dragon_Meteor_End")
	{
		AttackEnd();
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
		HitCheck();
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

void CDragon::PhaseOne()
{
	m_vecSkill.push_back(SkillData("Peashot"));
	m_vecSkill.push_back(SkillData("Meteor"));
	m_vecSkill.push_back(SkillData("Tail"));
}

void CDragon::Peashot()
{
	m_LastPattern = PEASHOT;
	m_bCanAttack = false;
	m_bIsAttack = true;
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
	pPeashot->SetRepeatNumber(2);
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
	m_Animation->ChangeAnimation("Dragon_Meteor_Attack");

	m_vecSkill[METEOR].IsActive = true;
	m_LastPattern = m_vecSkill[METEOR].SkillName;

	CMeteor* pMeteor= m_pScene->SpawnObject<CMeteor>("Meteor");
	m_CurrentSkill = pMeteor;
	pMeteor->StartPosition.x = m_GunPoint->GetWorldPos().x -150.f;
	pMeteor->SetRelativePos(m_GunPoint->GetWorldPos().x - 150.f, 270.f, 0.f);
	pMeteor->SetIsActive(true);
	pMeteor->SetSkillOwner(this);
	pMeteor->SetRepeatNumber(2);
}

void CDragon::Tail()
{
	CMeteor* pTail= m_pScene->SpawnObject<CMeteor>("Tail");
	pTail->SetIsActive(true);
	pTail->SetSkillOwner(this);
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
	}

	m_bCanAttack = false;
}

void CDragon::SelectNextSkill()
{
	if (m_bCanAttack)
	{
		// 랜덤으로 정한다.
	}

	if (m_LastPattern == "Peashot")
	{
		m_NextPattern = METEOR;
	}

	else
	{
		m_NextPattern = PEASHOT;
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

	if (m_bIsAttack)
	{
		return;
	}

	if (m_NextAttackTime < 0.f)
	{
		m_NextAttackTime = 3.0f;
		m_bCanAttack = true;
	}

	m_NextAttackTime -= DeltaTime;
}






