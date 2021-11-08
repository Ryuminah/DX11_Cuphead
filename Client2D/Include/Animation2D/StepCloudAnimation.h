#pragma once
#include "Resource\Animation2D.h"

class CStepCloudAnimation :
    public CAnimation2D
{
public:
	CStepCloudAnimation();
	CStepCloudAnimation(const CStepCloudAnimation& anim);
	virtual ~CStepCloudAnimation();


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CStepCloudAnimation* Clone();

};

