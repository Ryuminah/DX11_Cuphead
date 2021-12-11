#pragma once
#include "Resource/Animation2D.h"

class FG_LoadingAnim :
    public CAnimation2D
{
public:
	FG_LoadingAnim();
	FG_LoadingAnim(const FG_LoadingAnim& anim);
	virtual ~FG_LoadingAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual FG_LoadingAnim* Clone();
};

