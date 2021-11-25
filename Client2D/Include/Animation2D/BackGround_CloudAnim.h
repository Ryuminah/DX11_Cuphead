#pragma once
#include "Resource\Animation2D.h"

// 배경 리소스는 전부 해당 클래스를 사용하여 애니메이션을 출력한다.
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

