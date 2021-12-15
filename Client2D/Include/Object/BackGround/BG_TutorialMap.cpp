#include "BG_TutorialMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Character/Mugman.h"
#include "../../Animation2D/BackGround/TutorialSceneAnim.h"
#include "Scene/CameraManager.h"

BG_TutorialMap::BG_TutorialMap()
{
	m_PyramidHitCount = 0;
	m_ParryNumber = 1;
	m_ParrySuccessNumber = 0;
}

BG_TutorialMap::BG_TutorialMap(const BG_TutorialMap& obj) :
	CBackGround(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("BG_TutorialMap");
}

BG_TutorialMap::~BG_TutorialMap()
{
}

void BG_TutorialMap::Start()
{
	CBackGround::Start();;
}

bool BG_TutorialMap::Init()
{
	CBackGround::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("BG_TutorialMap");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.0f, 0.0f, 0.0f);
	m_Sprite->SetRelativePos(0.f, 0.0f, 0.f);
	m_Sprite->SetRelativeScale(6730.f, 720.f, 1.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Sprite->CreateAnimation2D<CTutorialSceneAnim>();
	m_BackGroundImage = m_Sprite->GetAnimation2D();
	m_BackGroundImage->ChangeAnimation("TutorialMap");

	CreateCollision();
	SetUseBlockMovement(false);

	m_Pyramid->AddCollisionCallbackFunction<BG_TutorialMap>(Collision_State::Begin, this, &BG_TutorialMap::Pyramid_CollisionBegin);
	m_ParryOne->AddCollisionCallbackFunction<BG_TutorialMap>(Collision_State::Overlap, this, &BG_TutorialMap::Parry_CollisionOverlap);
	m_ParryTwo->AddCollisionCallbackFunction<BG_TutorialMap>(Collision_State::Overlap, this, &BG_TutorialMap::Parry_CollisionOverlap);
	m_ParryThree->AddCollisionCallbackFunction<BG_TutorialMap>(Collision_State::Overlap, this, &BG_TutorialMap::Parry_CollisionOverlap);


	return true;
}

void BG_TutorialMap::Update(float DeltaTime)
{
	CBackGround::Update(DeltaTime);

	PyramidDestroyCheck();
	ParryCheck();
}

void BG_TutorialMap::PostUpdate(float DeltaTime)
{
	CBackGround::PostUpdate(DeltaTime);

	//if (CMugman::PlayerPos.x < 640.f || CMugman::PlayerPos.x >= 6090.f)
	//{
	//	return;
	//}

	//float MoveDistanceX = (CMugman::PlayerPos.x - CMugman::PlayerPrevPos.x);
	//Vector3 CameraPos = m_pScene->GetCameraManager()->GetCurrentCamera()->GetWorldPos();
	//if (MoveDistanceX != 0.f)
	//{
	//	m_pScene->GetCameraManager()->GetCurrentCamera()->AddRelativePos(MoveDistanceX, 0.f, 0.f);

	//}
}

void BG_TutorialMap::Collision(float DeltaTime)
{
	CBackGround::Collision(DeltaTime);
}

void BG_TutorialMap::Render(float DeltaTime)
{
	CBackGround::Render(DeltaTime);
}

BG_TutorialMap* BG_TutorialMap::Clone()
{
	return new BG_TutorialMap(*this);
}

void BG_TutorialMap::PyramidDestroyCheck()
{
	if (m_PyramidHitCount >= 15)
	{
		m_Lock->SetExtent(105.f, 120.f);

		// 그리고 이펙트출력하기
		m_spritePyramidHead->Active(false);
		m_Pyramid->Active(false);
	}
}

void BG_TutorialMap::ParryCheck()
{
	// 성공한 패링과 현재 활성화 된 패링이 같다면 다음으로 넘어가야 함
	if (m_ParrySuccessNumber == m_ParryNumber)
	{
		++m_ParryNumber;
		if (m_ParryNumber > 3)
		{
			m_ParryNumber = 1;
			m_ParrySuccessNumber = 0;
		}

		switch (m_ParryNumber)
		{
		case 1:
			ParryModeOn(m_ParryOne, m_spriteParryOne, m_ParryOneAnim);
			break;
		case 2:
			ParryModeOn(m_ParryTwo, m_spriteParryTwo, m_ParryTwoAnim);
			break;
		case 3:
			ParryModeOn(m_ParryThree, m_spriteParryThree, m_ParryThreeAnim);
			break;
		default:
			break;
		}
	}

	
}

void BG_TutorialMap::ParryModeOn(CColliderBox2D* parryCollision,
	CSpriteComponent* parrySprite ,CAnimation2D* parryAnim)
{
	// 다른 두개는 알아서 끈다.
	parryAnim->ChangeAnimation("Parry_On");
	parrySprite->SetRelativeScale(73.f, 71.f, 1.f);
	parryCollision->SetCollisionProfile("Parry");

	if (m_ParryNumber == 1)
	{
		m_ParryTwo->SetCollisionProfile("Bullet");
		m_ParryTwoAnim->ChangeAnimation("Parry_Off");
		m_spriteParryTwo->SetRelativeScale(45.f, 48.f, 1.f);

		m_ParryThree->SetCollisionProfile("Player");
		m_ParryThreeAnim->ChangeAnimation("Parry_Off");
		m_spriteParryThree->SetRelativeScale(45.f, 48.f, 1.f);

		return;

	}

	else if (m_ParryNumber == 2)
	{
		m_ParryOne->SetCollisionProfile("Bullet");
		m_ParryOneAnim->ChangeAnimation("Parry_Off");
		m_spriteParryOne->SetRelativeScale(45.f, 48.f, 1.f);

		m_ParryThree->SetCollisionProfile("Bullet");
		m_ParryThreeAnim->ChangeAnimation("Parry_Off");
		m_spriteParryThree->SetRelativeScale(45.f, 48.f, 1.f);
		return;

	}

	else
	{
		m_ParryOne->SetCollisionProfile("Bullet");
		m_ParryOneAnim->ChangeAnimation("Parry_Off");
		m_spriteParryOne->SetRelativeScale(45.f, 48.f, 1.f);

		m_ParryTwo->SetCollisionProfile("Bullet");
		m_ParryTwoAnim->ChangeAnimation("Parry_Off");
		m_spriteParryTwo->SetRelativeScale(45.f, 48.f, 1.f);
		return;

	}

}



void BG_TutorialMap::CreateCollision()
{
	m_Jump = CreateSceneComponent<CColliderBox2D>("Jump");
	m_Jump->SetExtent(95.f, 75.f);
	m_Jump->SetRelativePos(1580.f, 120.f, 0.f);
	m_Jump->SetCollisionProfile("Static");
	m_Jump->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Jump);

	m_Descend = CreateSceneComponent<CColliderBox2D>("Descend");
	m_Descend->SetExtent(100.f, 30.f);
	m_Descend->SetRelativePos(2300.f, 360.f, 0.f);
	m_Descend->SetCollisionProfile("FootStep");
	m_Descend->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Descend);

	m_Descend = CreateSceneComponent<CColliderBox2D>("DescendWall");
	m_Descend->SetExtent(45.f,180.f);
	m_Descend->SetRelativePos(2490.f, 360.f, 0.f);
	m_Descend->SetCollisionProfile("Static");
	m_Descend->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Descend);

	m_Descend = CreateSceneComponent<CColliderBox2D>("DescendCylinder");
	m_Descend->SetExtent(80.f, 150.f);
	m_Descend->SetRelativePos(2077.f, 120.f, 0.f);
	m_Descend->SetCollisionProfile("Static");
	m_Descend->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_Descend);

	m_ParryBox = CreateSceneComponent<CColliderBox2D>("ParryBox");
	m_ParryBox->SetExtent(45.f, 70.f);
	m_ParryBox->SetRelativePos(4860.f, 120.f, 0.f);
	m_ParryBox->SetCollisionProfile("Static");
	m_ParryBox->SetColliderType(Collider_Type::Static);

	m_ParryBox = CreateSceneComponent<CColliderBox2D>("ParryCylinder");
	m_ParryBox->SetExtent(45.f, 70.f);
	m_ParryBox->SetRelativePos(4860.f, 120.f, 0.f);
	m_ParryBox->SetCollisionProfile("Static");
	m_ParryBox->SetColliderType(Collider_Type::Static);

	m_Sprite->AddChild(m_ParryBox);

	// Pyramid
	m_Lock = CreateSceneComponent<CColliderBox2D>("Lock");
	m_Lock->SetExtent(105.f, 170.f);
	m_Lock->SetRelativePos(3830.f, 120.f, 0.f);
	m_Lock->SetCollisionProfile("Static");
	m_Lock->SetColliderType(Collider_Type::Static);
	m_Sprite->AddChild(m_Lock);

	m_Pyramid = CreateSceneComponent<CColliderBox2D>("PyramidHead");
	m_Pyramid->SetExtent(100.f, 100.f);
	m_Pyramid->SetRelativePos(3830.f, 320.f, 0.f);
	m_Pyramid->SetCollisionProfile("Enemy");
	m_Pyramid->SetColliderType(Collider_Type::Static);
	m_Sprite->AddChild(m_Pyramid);

	m_spritePyramidBody = CreateSceneComponent<CSpriteComponent>("PyramidBody");
	m_spritePyramidBody->SetRelativePos(3830.f, 102.0f, 0.f);
	m_spritePyramidBody->SetRelativeScale(282.f, 303.f,1.f);
	m_spritePyramidBody->CreateAnimation2D<CTutorialSceneAnim>();
	m_spritePyramidBody->SetDefaultZ(0.9f);
	m_PyramidBodyAnim = m_spritePyramidBody->GetAnimation2D();
	m_PyramidBodyAnim->ChangeAnimation("Pyramid_Body");
	m_Sprite->AddChild(m_spritePyramidBody);

	m_spritePyramidHead = CreateSceneComponent<CSpriteComponent>("PyramidHead");
	m_spritePyramidHead->SetRelativePos(3820.f, 325.0f, 0.f);
	m_spritePyramidHead->SetRelativeScale(222.f, 243.f, 1.f);
	m_spritePyramidHead->CreateAnimation2D<CTutorialSceneAnim>();
	m_PyramidHeadAnim = m_spritePyramidHead->GetAnimation2D();
	m_PyramidHeadAnim->ChangeAnimation("Pyramid_Head");
	m_Sprite->AddChild(m_spritePyramidHead);

	CreateParry();

	
}

void BG_TutorialMap::CreateParry()
{
	// Parry
	m_ParryOne = CreateSceneComponent<CColliderBox2D>("Parry");
	m_ParryOne->SetPivot(0.5f, 0.5, 0.f);
	m_ParryOne->SetExtent(20.f, 20.f);
	m_ParryOne->SetRelativePos(4195.f, 423.f, 0.f);
	m_ParryOne->SetCollisionProfile("Parry");
	m_ParryOne->SetColliderType(Collider_Type::Static);
	m_Sprite->AddChild(m_ParryOne);

	m_spriteParryOne = CreateSceneComponent<CSpriteComponent>("ParryOne");
	m_spriteParryOne->SetPivot(0.5f,0.5f,0.f);
	m_spriteParryOne->SetRelativePos(4195.f, 423.0f, 0.f);
	m_spriteParryOne->SetRelativeScale(73.f, 71.f, 1.f);
	m_spriteParryOne->CreateAnimation2D<CTutorialSceneAnim>();
	m_spriteParryOne->SetDefaultZ(0.9f);
	m_ParryOneAnim = m_spriteParryOne->GetAnimation2D();
	m_ParryOneAnim->ChangeAnimation("Parry_On");
	m_Sprite->AddChild(m_spriteParryOne);

	//2
	m_ParryTwo = CreateSceneComponent<CColliderBox2D>("Parry");
	m_ParryTwo->SetPivot(0.5f, 0.5, 0.f);
	m_ParryTwo->SetExtent(20.f, 20.f);
	m_ParryTwo->SetRelativePos(4393.f, 423.f, 1.f);
	m_ParryTwo->SetCollisionProfile("Bullet");
	m_ParryTwo->SetColliderType(Collider_Type::Static);
	m_Sprite->AddChild(m_ParryTwo);

	m_spriteParryTwo = CreateSceneComponent<CSpriteComponent>("ParryTwo");
	m_spriteParryTwo->SetPivot(0.5f, 0.5f, 0.f);
	m_spriteParryTwo->SetRelativePos(4393.f, 423.0f, 0.f);
	m_spriteParryTwo->SetRelativeScale(45.f, 48.f, 1.f);
	m_spriteParryTwo->CreateAnimation2D<CTutorialSceneAnim>();
	m_spriteParryTwo->SetDefaultZ(0.9f);
	m_ParryTwoAnim = m_spriteParryTwo->GetAnimation2D();
	m_ParryTwoAnim->ChangeAnimation("Parry_Off");
	m_Sprite->AddChild(m_spriteParryTwo);

	//3
	m_ParryThree = CreateSceneComponent<CColliderBox2D>("Parry");
	m_ParryThree->SetPivot(0.5f, 0.5, 0.f);
	m_ParryThree->SetExtent(20.f, 20.f);
	m_ParryThree->SetRelativePos(4572.f, 423.f, 1.f);
	m_ParryThree->SetCollisionProfile("Bullet");
	m_ParryThree->SetColliderType(Collider_Type::Static);
	m_Sprite->AddChild(m_ParryThree);

	m_spriteParryThree = CreateSceneComponent<CSpriteComponent>("ParryThree");
	m_spriteParryThree->SetPivot(0.5f, 0.5f, 0.f);
	m_spriteParryThree->SetRelativePos(4572.f, 423.0f, 0.f);
	m_spriteParryThree->SetRelativeScale(45.f, 48.f, 1.f);
	m_spriteParryThree->CreateAnimation2D<CTutorialSceneAnim>();
	m_spriteParryThree->SetDefaultZ(0.9f);
	m_ParryThreeAnim = m_spriteParryThree->GetAnimation2D();
	m_ParryThreeAnim->ChangeAnimation("Parry_Off");
	m_Sprite->AddChild(m_spriteParryThree);
}

void BG_TutorialMap::Pyramid_CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetName() == "BulletCollider")
	{
		++m_PyramidHitCount;
		m_spritePyramidHead->GetMaterial(0)->SetMaterialTimerBaseColor(0.46f, 0.98f, 1.0f, 0.3f);
		m_spritePyramidHead->GetMaterial(0)->UseMaterialTimer(0.05f);
	}
}

void BG_TutorialMap::Parry_CollisionOverlap(const HitResult& result, CCollider* Collider)
{
	if (result.DestObject->GetName() == "Mugman")
	{
		CMugman* pMugman = (CMugman*)result.DestObject;

		// 아직 패링에 성공하지 못했을 때만 성공 여부를 체크한다.
		if (pMugman->GetParrySuccess() && (m_ParrySuccessNumber != m_ParryNumber))
		{
			m_ParrySuccessNumber = m_ParryNumber;
		}
	}
}
