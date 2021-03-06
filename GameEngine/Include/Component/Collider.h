#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/Mesh.h"
#include "../Resource/Shader.h"
#include "../Resource/ShaderManager.h"

class CCollider :
	public CPrimitiveComponent
{
	friend class CGameObject;

protected:
	CCollider();
	CCollider(const CCollider& com);
	virtual ~CCollider();

protected:
	CSharedPtr<CMesh>	m_DebugMesh;
	CSharedPtr<CShader>	m_DebugShader;
	class CColliderConstantBuffer* m_CBuffer;
	bool	m_DebugRender;

protected:
	Collider_Shape	m_ColliderShape;
	Collider_Space	m_ColliderSpace;
	Collider_Type	m_ColliderType;
	std::vector<int>	m_vecSectionIndex;
	Vector3		m_Min;
	Vector3		m_Max;
	std::list<CCollider*>	m_PrevCollisionList;
	std::list<CCollider*>	m_CurrentCollisionList;
	CollisionProfile* m_Profile;
	bool		m_CurrentSectionCheck;
	HitResult		m_HitResult;
	std::list<std::function<void(const HitResult&, CCollider*)>>	m_CollisionCallback[(int)Collision_State::Max];
	std::list<std::function<void(const Vector2&, CCollider*)>>		m_CollisionMouseCallback[(int)Collision_State::Max];
	bool		m_MouseCollision;


public:
	std::list<CCollider*>	GetCurrentCollisionList() const
	{
		return m_CurrentCollisionList;
	}

	std::list<CCollider*>	GetPrevCollisionList() const
	{
		return m_PrevCollisionList;
	}

	bool GetDebugRender()	const
	{
		return m_DebugRender;
	}

	HitResult GetHitResult()	const
	{
		return m_HitResult;
	}

	bool GetCurrentSectionCheck()	const
	{
		return m_CurrentSectionCheck;
	}

	CollisionProfile* GetProfile()	const
	{
		return m_Profile;
	}

	Collider_Space GetColliderSpace()	const
	{
		return m_ColliderSpace;
	}

	Collider_Type GetColliderType() const
	{
		return m_ColliderType;
	}

	Vector3 GetMin()	const
	{
		return m_Min;
	}

	Vector3 GetMax()	const
	{
		return m_Max;
	}

	Collider_Shape GetColliderShape()	const
	{
		return m_ColliderShape;
	}

	void AddSectionIndex(int Index)
	{
		m_vecSectionIndex.push_back(Index);
	}

	void SetHitResult(HitResult result)
	{
		m_HitResult = result;
	}

	void SetHitResult(CCollider* DestCollider, Vector3 HitPoint = { 0.f,0.f,0.f })
	{
		m_HitResult.DestCollider = DestCollider;
		m_HitResult.DestObject = DestCollider->GetOwner();
		m_HitResult.HitPoint = HitPoint;
	}

public:
	void SetColliderType(Collider_Type type)
	{
		m_ColliderType = type;
	}

public:
	void CurrentSectionCheck()
	{
		m_CurrentSectionCheck = true;
	}

	void SetCollisionProfile(const std::string& Name);
	void CheckPrevColliderSection();
	void AddPrevCollider(CCollider* Collider);
	void DeletePrevCollider(CCollider* Collider);
	bool EmptyPrevCollision();
	bool CheckPrevCollision(CCollider* Collider);
	bool CheckCurrentFrameCollision(CCollider* Collider);
	void AddCurrentFrameCollision(CCollider* Collider);

public:
	void CallCollisionCallback(Collision_State State);
	void CallCollisionMouseCallback(Collision_State State, const Vector2& MousePos);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCollider* Clone();

public:
	virtual bool Collision(CCollider* Dest) = 0;
	virtual bool CollisionMouse(const Vector2& MousePos) = 0;

public:
	void ClearFrame();

public:
	template <typename T>
	void AddCollisionCallbackFunction(Collision_State State, T* Obj,
		void(T::* pFunc)(const HitResult&, CCollider*))
	{
		m_CollisionCallback[(int)State].push_back(std::bind(pFunc, Obj, std::placeholders::_1, std::placeholders::_2));
	}

	template <typename T>
	void AddCollisionMouseCallbackFunction(Collision_State State, T* Obj,
		void(T::* pFunc)(const Vector2&, CCollider*))
	{
		m_CollisionMouseCallback[(int)State].push_back(std::bind(pFunc, Obj, std::placeholders::_1, std::placeholders::_2));
	}
};

