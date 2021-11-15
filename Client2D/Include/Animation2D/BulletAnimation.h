#pragma once
#include "Resource\Animation2D.h"

class CBulletAnimation :
    public CAnimation2D
{
public:
	CBulletAnimation();
	CBulletAnimation(const CBulletAnimation& anim);
	virtual ~CBulletAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletAnimation* Clone();
};

