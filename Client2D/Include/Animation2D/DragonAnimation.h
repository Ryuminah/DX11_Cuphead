#pragma once
#include "Resource\Animation2D.h"

class CDragonAnimation :
    public CAnimation2D
{
public:
	CDragonAnimation();
	CDragonAnimation(const CDragonAnimation& anim);
	virtual ~CDragonAnimation();


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CDragonAnimation* Clone();

};

