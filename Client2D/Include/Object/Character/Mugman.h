#pragma once
#include "Character.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"

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
	CSharedPtr<CSpriteComponent> m_GunEffect;

private:
	// basic Movement
	bool m_bGameStart;
	float m_IntroTime;		// 나중에 intro Animation 종료시로 조건을 변경한다.

	bool m_bCanJump;
	bool m_bIsJump;
	float m_JumpTime;
	float m_JumpVelocity;
	float m_JumpAccel;
	float m_PosY;

	bool m_bIsGround;
	bool m_bIsFall;
	float m_FallTime;

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

	bool m_bIsDamaged;

private:
	// Shooting
	float	m_ShootCool;
	float	m_DashCool;
	float	m_InvincibleTime;


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
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void Jump(float DeltaTime);
	void Shoot(float DeltaTime);
	void Aim(float DeltaTime);
	void Dash(float DeltaTime);
	virtual void Hit();

public:
	void ShootEnd(float DeltaTime);
	void MoveEnd(float DeltaTime);
	void AimEnd(float DeltaTime);

public:
	void AnimationFrameEnd(const std::string& Name);

public: //Get Set
	bool GetIsGround()
	{
		return m_bIsGround;
	}

	
public: //Check Logic
	void FallCheck(float DeltaTime);
	void JumpCheck(float DeltaTime);
	void DashCheck(float DeltaTime);
	void TimeCheck(float DeltaTime);
	void AnimCheck(float DeltaTime);
	void DeathCheck(float DeltaTime);
	void MuzzleLoopCheck(float DeltaTime);
	void SavePlayerPos();


	
public: // Move 관련
	void JumpEnd();
	void DashEnd();
	virtual void HitEnd();
	void OnGround();
	void OnStepCloud(float MoveZ, float CloudY);
	void InAir();

	// Shoot 관련
public:


public:
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionOverlap(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);


};
