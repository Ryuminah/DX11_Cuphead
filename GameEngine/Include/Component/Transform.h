#pragma once

#include "../GameEngine.h"

class CTransform
{
	friend class CSceneComponent;

private:
	CTransform();
	CTransform(const CTransform& transform);
	~CTransform();

private:
	class CScene* m_pScene;
	class CGameObject* m_pOwnerObject;
	class CSceneComponent* m_pOwner;

private:
	CTransform* m_pParent;
	std::vector<CTransform*>    m_vecChild;
	class CTransformConstantBuffer* m_pCBuffer;
	float		m_DefaultZ;

private:
	bool    m_Animation2DEnable;
	bool	m_UVFlow2DEnable;
	bool	m_UVFlow2DDirection;				// 0은 음, 1은 양
	float	m_UVFlow2DSpeed;			

public:
	void SetDefaultZ(float Z)
	{
		m_DefaultZ = Z;
	}

	float GetDefaultZ()	const
	{
		return m_DefaultZ;
	}

	void SetAnimation2DEnable(bool Enable)
	{
		m_Animation2DEnable = Enable;
	}

	void SetUVFlow2DEnable(bool Enable)
	{
		m_UVFlow2DEnable = Enable;
	}

	void SetUVFlow2DDirection(bool UVFlowDirection)
	{
		m_UVFlow2DDirection = UVFlowDirection;
	}

	void SetUVFlow2DSpeed(float UVFlowSpeed)
	{
		m_UVFlow2DSpeed = UVFlowSpeed;
	}

private:
	Vector3 m_VelocityScale;
	Vector3 m_VelocityRot;
	Vector3 m_Velocity;
	Vector3 m_Axis[AXIS_END];
	bool    m_InheritScale;
	bool    m_InheritRotX;
	bool    m_InheritRotY;
	bool    m_InheritRotZ;
	bool    m_InheritPosZ;
	bool    m_UpdateScale;
	bool    m_UpdateRot;
	bool    m_UpdatePos;
	bool	m_UpdatePosZ;

	float	m_GravityAccel;
	float	m_Gravity;
	bool	m_PhysicsSimulate;			// 중력 적용할건지
	bool	m_bUseBlockMovement;		// 충돌을 잠깐 해제하고싶을때

public:
	float GetGravity() const
	{
		return m_Gravity;
	}

	float GetGravityAccel() const
	{
		return m_GravityAccel;
	}

	bool GetPhysicsSimulate()	const
	{
		return m_PhysicsSimulate;
	}

	Vector3 GetVelocityScale()  const
	{
		return m_VelocityScale;
	}

	Vector3 GetVelocityRot()    const
	{
		return m_VelocityRot;
	}

	Vector3 GetVelocity()   const
	{
		return m_Velocity;
	}

	Vector3 GetAxis(AXIS Axis)  const
	{
		return m_Axis[Axis];
	}

	bool GetUseBlockMovement() const
	{
		return m_bUseBlockMovement;
	}

public:
	void SetPhysicsSimulate(bool Simulate)
	{
		m_PhysicsSimulate = Simulate;
	}

	void SetInheritScale(bool Inherit)
	{
		m_InheritScale = Inherit;
	}

	void SetInheritRotX(bool Inherit)
	{
		m_InheritRotX = Inherit;
	}

	void SetInheritRotY(bool Inherit)
	{
		m_InheritRotY = Inherit;
	}

	void SetInheritRotZ(bool Inherit)
	{
		m_InheritRotZ = Inherit;
	}

	void SetInheritPosZ(bool Inherit)
	{
		m_InheritPosZ = Inherit;
	}

	void SetUpdatePosZ(bool UpdatePosZ)
	{
		m_UpdatePosZ = UpdatePosZ;
	}

	void SetUseBlockMovement(bool bUseBlockMovement)
	{
		m_bUseBlockMovement = bUseBlockMovement;
	}

	void InheritScale();
	void InheritRot();
	void InheritPos();
	void ResetPhysicsSimulate();

public:
	bool GetInheritPosZ()	const
	{
		return m_InheritPosZ;
	}

	bool GetUpdatePosZ()	const
	{
		return m_UpdatePosZ;
	}

private:    // Relative Data
	Vector3 m_RelativeScale;
	Vector3 m_RelativeRot;
	Vector3 m_RelativePos;

public:
	Vector3 GetRelativeScale()  const
	{
		return m_RelativeScale;
	}

	Vector3 GetRelativeRotation()    const
	{
		return m_RelativeRot;
	}

	Vector3 GetRelativePos()    const
	{
		return m_RelativePos;
	}

public:
	void SetRelativeScale(const Vector3& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeRotation(const Vector3& Rot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativePos(const Vector3& Pos);
	void SetRelativePos(float x, float y, float z);
	void AddRelativeScale(const Vector3& Scale);
	void AddRelativeScale(float x, float y, float z);
	void AddRelativeRotation(const Vector3& Rot);
	void AddRelativeRotation(float x, float y, float z);
	void AddRelativeRotationX(float x);
	void AddRelativeRotationY(float y);
	void AddRelativeRotationZ(float z);
	void AddRelativePos(const Vector3& Pos);
	void AddRelativePos(float x, float y, float z);

private:    // World Data
	Vector3 m_WorldScale;
	Vector3 m_WorldRot;
	Vector3 m_WorldPos;
	Vector3 m_PrevWorldPos;

	Vector3 m_Pivot;
	Vector3 m_MeshSize;

	Matrix  m_matScale;
	Matrix  m_matRot;
	Matrix  m_matPos;
	Matrix  m_matWorld;



public:
	Vector3 GetPrevWorldPos() const
	{
		return m_PrevWorldPos;
	}

	Vector3 GetWorldScale() const
	{
		return m_WorldScale;
	}

	Vector3 GetWorldRotation()  const
	{
		return m_WorldRot;
	}

	Vector3 GetWorldPos()   const
	{
		return m_WorldPos;
	}

	Vector3 GetPivot()  const
	{
		return m_Pivot;
	}

	Vector3 GetMeshSize()   const
	{
		return m_MeshSize;
	}

	Matrix GetScaleMatrix() const
	{
		return m_matScale;
	}

	Matrix GetRotatinMatrix()   const
	{
		return m_matRot;
	}

	Matrix GetTranslationMatrix()   const
	{
		return m_matPos;
	}

	Matrix GetWorldMatrix() const
	{
		return m_matWorld;
	}

public:
	void SetPivot(const Vector3& Pivot)
	{
		m_Pivot = Pivot;
	}

	void SetPivot(float x, float y, float z)
	{
		m_Pivot = Vector3(x, y, z);
	}

	void SetMeshSize(const Vector3& Size)
	{
		m_MeshSize = Size;
	}

	void SetMeshSize(float x, float y, float z)
	{
		m_MeshSize = Vector3(x, y, z);
	}

	void SetPrevWorldPos(const Vector3& PrevWorldPos)
	{
		m_PrevWorldPos = PrevWorldPos;
	}

public:
	void SetWorldScale(const Vector3& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldRotation(const Vector3& Rot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldPos(const Vector3& Pos);
	void SetWorldPos(float x, float y, float z);
	void AddWorldScale(const Vector3& Scale);
	void AddWorldScale(float x, float y, float z);
	void AddWorldRotation(const Vector3& Rot);
	void AddWorldRotation(float x, float y, float z);
	void AddWorldRotationX(float x);
	void AddWorldRotationY(float y);
	void AddWorldRotationZ(float z);
	void AddWorldPos(const Vector3& Pos);
	void AddWorldPos(float x, float y, float z);
	void CaculateMatWorld();

public:
	Vector3 Lerp2D(Vector3 LastTargetPosition, Vector3 StartTargetPosition, float Time);

public:
	void Start();
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void SetTransform();
	void ComputeWorld();
	CTransform* Clone();
	void ClearState();
};

