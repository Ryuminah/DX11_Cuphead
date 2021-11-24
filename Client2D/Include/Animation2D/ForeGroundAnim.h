#pragma once
#include "Resource\Animation2D.h"

class CForeGroundAnim :
    public CAnimation2D
{
public:
	CForeGroundAnim();
	CForeGroundAnim(const CForeGroundAnim& anim);
	virtual ~CForeGroundAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CForeGroundAnim* Clone();
};

