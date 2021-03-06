#pragma once
#include "Character.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"

struct MuzzlePosition
{
	static Vector3 Up;
	static Vector3 Up_Digonal_R;
	static Vector3 Up_Digonal_L;

	static Vector3 Down;
	static Vector3 Down_Duck_R;
	static Vector3 Down_Duck_L;
	static Vector3 Down_Digonal_R;
	static Vector3 Down_Digonal_L;
};


// 씬마다 할 수 있는 행동 정리.
class CMugman :
	public CCharacter
{
	friend class CScene;

protected:
	CMugman();
	CMugman(const CMugman& obj);
	virtual ~CMugman();

public:
	static Vector3	PlayerPos;
	static Vector3	PlayerPrevPos;
	static bool	bUseCamera;


	static Vector3 GetPlayerPos()
	{
		return PlayerPos;
	}

	static Vector3 GetPlayerPrevPos()
	{
		return PlayerPrevPos;
	}

private:
	// Component
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_Muzzle;
	CSharedPtr<CSpringArm2D> m_Arm;
	CSharedPtr<CCamera> m_Camera;
	std::list<std::string> m_CurrentColliderName;			// 어떤 종류의 콜리전이 overlap되고 있는지 저장

private:
	// Game Start
	bool m_bGameStart;
	bool m_bUseGameStart;

	bool m_bIsFightScene;	// Scene마다 등록해야하는 콜백 함수를 변경해준다.
	float m_IntroTime;		// 나중에 intro Animation 종료시로 조건을 변경한다.

	// Basic Movement
	bool m_bCanDuck;
	bool m_bCanDuckFall;
	bool m_bIsDuck;
	bool m_bIsDuckLoop;

	// Jump
	bool m_bCanJump;
	bool m_bIsJump;
	float m_JumpTime;
	float m_JumpVelocity;
	float m_JumpAccel;
	float m_JumpInputTime;		// 낮은 점프 , 높은 점프

	// Parry
	bool m_bCanParry;
	bool m_bIsParry;
	bool m_bIsParryFall;
	bool m_bParrySuccess;		
	float m_ParryTime;
	float m_ParryVelocity;
	float m_ParryAccel;
	float m_StartY;			// 시작 위치로 돌아왔을 경우 패링 상태를 종료한다.

	// Ground or Air
	bool m_bIsGround;
	bool m_bIsFall;
	float m_FallTime;

	// Dash
	bool m_bIsDash;
	bool m_bCanDash;
	float m_DashTime;
	float m_DashSpeed;

	// Aim
	bool m_bCanAim;
	bool m_bIsAiming;

	// Attack
	int	m_BulletCount;

	// Muzzle
	float m_TimeToFrame;
	float m_MuzzleMaxY;
	int	  m_Frame;

	// Effect
	float m_DustTime;

	// Hit
	bool m_bIsDamaged;
	

private:
	// Shooting
	float	m_ShootCool;
	float	m_DashCool;
	float	m_InvincibleTime;
	float	m_ParryCheckTime;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMugman* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AimUp(float DeltaTime);
	void Aim(float DeltaTime);
	void AimDown();
	void Duck(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void Jump(float DeltaTime);
	void Parry();
	void Shoot(float DeltaTime);
	void Dash(float DeltaTime);
	void Enter(float DeltaTime);
	virtual void Hit();

public:
	void ShootEnd(float DeltaTime);
	void MoveEnd(float DeltaTime);
	void DuckEnd(float DeltaTime);
	void AimEnd(float DeltaTime);

public:
	void AnimationFrameEnd(const std::string& Name);

public: //Get Set
	bool GetIsGround()
	{
		return m_bIsGround;
	}

	bool GetParrySuccess()
	{
		return m_bParrySuccess;
	}

	bool GetIsParry()
	{
		return m_bIsParry;
	}

	void SetIsFightScene(bool IsFightScene)
	{
		m_bIsFightScene = IsFightScene;
	}

	void SetbCanJump(bool CanJump)
	{
		m_bCanJump = CanJump;
	}

	void SetbUseGameStart(bool bUseGameStart)
	{
		m_bUseGameStart = bUseGameStart;
	}

public: //Check Logic
	void AnimCheck(float DeltaTime);
	void FallCheck(float DeltaTime);
	void JumpCheck(float DeltaTime);
	void ParryCheck(float DeltaTime);
	void DashCheck(float DeltaTime);
	void TimeCheck(float DeltaTime);
	void DeathCheck(float DeltaTime);
	void MuzzleLoopCheck(float DeltaTime);
	void SavePlayerPos();

public: // Move 관련
	void JumpEnd();				
	void ParryEnd();			
	void DashEnd();
	void FallEnd();

	virtual void HitEnd();
	void OnGround();
	void OnStepCloud(float MoveZ, float CloudY);
	void InAir();

public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
	void AddColliderName(std::string colliderName);
	void DeleteCurrentCollider(std::string colliderName);
	void ClearColliderName();
};
