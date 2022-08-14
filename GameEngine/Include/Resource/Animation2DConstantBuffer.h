#pragma once
#include "ConstantBufferData.h"
class CAnimation2DConstantBuffer :
	public CConstantBufferData
{
public:
	CAnimation2DConstantBuffer();
	CAnimation2DConstantBuffer(const CAnimation2DConstantBuffer& buffer);
	virtual ~CAnimation2DConstantBuffer();

protected:
	Animation2DCBuffer    m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CAnimation2DConstantBuffer* Clone();

public:
	void SetAnimation2DType(Animation2D_Type Type)
	{
		m_BufferData.Animation2DType = (int)Type;
	}

	void SetStartUV(const Vector2& UV)
	{
		m_BufferData.StartUV = UV;
	}

	void SetEndUV(const Vector2& UV)
	{
		m_BufferData.EndUV = UV;
	}

	void SetAnimation2DEnable(bool Enable)
	{
		m_BufferData.Animation2DEnable = Enable ? 1 : 0;
	}

	void SetUVFlow2DEnable(bool Enable)
	{
		m_BufferData.UVFlow2DEnable = Enable ? 1 : 0;
	}

	void SetUVFlow2DDirection(bool UVFlowDirection)
	{
		m_BufferData.UVFlow2DDirection = UVFlowDirection ? 1 : 0;
	}

	void SetUVFlow2DSpeed(float UVFlowSpeed)
	{
		m_BufferData.UVFlow2DSpeed = UVFlowSpeed;
	}
};

