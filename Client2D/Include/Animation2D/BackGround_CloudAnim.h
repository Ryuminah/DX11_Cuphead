#pragma once
#include "Resource\Animation2D.h"

// ��� ���ҽ��� ���� �ش� Ŭ������ ����Ͽ� �ִϸ��̼��� ����Ѵ�.
class CBackGround_CloudAnim :
    public CAnimation2D
{
public:
	CBackGround_CloudAnim();
	CBackGround_CloudAnim(const CBackGround_CloudAnim& anim);
	virtual ~CBackGround_CloudAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBackGround_CloudAnim* Clone();
};

