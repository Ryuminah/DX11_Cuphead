#pragma once
#include "FightObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"

enum class Mugman_State
{
	Idle, Run, Dash, Jump, Attack
};

class CMugman :
	public CFightObject
{
	friend class CScene;

protected:
	CMugman();
	CMugman(const CMugman& obj);
	virtual ~CMugman();

private:
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_Muzzle;
	/*CSharedPtr<CSpringArm2D> m_Arm;
	CSharedPtr<CCamera> m_Camera;*/

private:
	Mugman_State	m_State;

private:
	// basic Movement
	bool m_bCanJump;
	bool m_bIsJump;
	bool m_bIsGround;

	bool m_bIsFall;
	float m_FallTime;

	bool m_bIsDash;
	bool m_bCanDash;

	float m_JumpTime;
	float m_JumpVelocity;
	float m_JumpAccel;
	float m_PosY;

	float m_DashTime;
	float m_DashSpeed;

	// Attack
	int	m_BulletCount;



private:
	// Shooting
	float	m_ShootCool;
	float	m_DashCool;


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
	void Dash(float DeltaTime);


public:
	void AnimationFrameEnd(const std::string& Name);

public: //Get Set
	bool GetIsGround()
	{
		return m_bIsGround;
	}

	//Check Logic
public:
	void FallCheck(float DeltaTime);
	void JumpCheck(float DeltaTime);
	void DashCheck(float DeltaTime);
	void TimeCheck(float DeltaTime);

	// Move 관련
public:
	void JumpEnd();
	void DashEnd();

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
